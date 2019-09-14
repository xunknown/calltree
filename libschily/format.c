/* @(#)format.c	1.38 03/10/18 Copyright 1985-2003 J. Schilling */
/*
 *	format
 *	common code for printf fprintf & sprintf
 *
 *	allows recursive printf with "%r", used in:
 *	error, comerr, comerrno, errmsg, errmsgno and the like
 *
 *	Copyright (c) 1985-2003 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <mconfig.h>
#include <vadefs.h>
#include <strdefs.h>
#include <stdxlib.h>
#ifdef	DEBUG
#include <unixstd.h>
#endif
#if	!defined(HAVE_STDLIB_H) || !defined(HAVE_GCVT)
extern	char	*gcvt __PR((double, int, char *));
#endif
#include <standard.h>
#include <utypes.h>
#include <schily.h>

/*
 * As Llong is currently a 'best effort' long long, we usually need to
 * include long long print formats.
 * This may go away, if we implement maxint_t formats.
 */
#define	USE_LONGLONG

#ifdef	NO_LONGLONG
#undef	USE_LONGLONG
#endif

/*
 * Some CPU's (e.g. PDP-11) cannot do logical shifts.
 * They use rotate instead. Masking the low bits before,
 * makes rotate work too.
 */
#define	allmask(t)	((unsigned t)~((unsigned t)0))
#define	lowmask(t, x)	((unsigned t)~((unsigned t)((1 << (x))-1)))
#define	rshiftmask(t, s)((allmask(t) & lowmask(t, s)) >> (s))

#define	CHARMASK	makemask(char)
#define	SHORTMASK	makemask(short)
#define	INTMASK		makemask(int)
#define	LONGMASK	makemask(long)

#ifdef	DIVLBYS
extern	long	divlbys();
extern	long	modlbys();
#else
#define	divlbys(val, base)	((val)/(base))
#define	modlbys(val, base)	((val)%(base))
#endif

/*
 *	We use macros here to avoid the need to link to the international
 *	character routines.
 *	We don't need internationalization for our purpose.
 */
#define	is_dig(c)	(((c) >= '0') && ((c) <= '9'))
#define	is_cap(c)	((c) >= 'A' && (c) <= 'Z')
#define	to_cap(c)	(is_cap(c) ? c : c - 'a' + 'A')
#define	cap_ty(c)	(is_cap(c) ? 'L' : 'I')

#ifdef	HAVE_LONGLONG
typedef union {
	Ullong	ll;
	Ulong	l[2];
	char	c[8];
} quad_u;
#endif

typedef struct f_args {
	void  (*outf)__PR((char, long)); /* Func from format(fun, arg)	*/
	long	farg;			/* Arg from format (fun, arg)	*/
	int	minusflag;		/* Fieldwidth is negative	*/
	int	flags;			/* General flags (+-#)		*/
	int	fldwidth;		/* Field width as in %3d	*/
	int	signific;		/* Significant chars as in %.4d	*/
	int	lzero;			/* Left '0' pad flag		*/
	char	*buf;			/* Out print buffer		*/
	char	*bufp;			/* Write ptr into buffer	*/
	char	fillc;			/* Left fill char (' ' or '0')	*/
	char	*prefix;		/* Prefix to print before buf	*/
	int	prefixlen;		/* Len of prefix ('+','-','0x')	*/
} f_args;

#define	MINUSFLG	1	/* '-' flag */
#define	PLUSFLG		2	/* '+' flag */
#define	SPACEFLG	4	/* ' ' flag */
#define	HASHFLG		8	/* '#' flag */

LOCAL	void	prnum  __PR((Ulong, unsigned, f_args *));
LOCAL	void	prdnum __PR((Ulong, f_args *));
LOCAL	void	pronum __PR((Ulong, f_args *));
LOCAL	void	prxnum __PR((Ulong, f_args *));
LOCAL	void	prXnum __PR((Ulong, f_args *));
#ifdef	USE_LONGLONG
LOCAL	void	prlnum  __PR((Ullong, unsigned, f_args *));
LOCAL	void	prldnum __PR((Ullong, f_args *));
LOCAL	void	prlonum __PR((Ullong, f_args *));
LOCAL	void	prlxnum __PR((Ullong, f_args *));
LOCAL	void	prlXnum __PR((Ullong, f_args *));
#endif
LOCAL	int	prbuf  __PR((const char *, f_args *));
LOCAL	int	prc    __PR((char, f_args *));
LOCAL	int	prstring __PR((const char *, f_args *));
#ifdef	DEBUG
LOCAL	void	dbg_print __PR((char *fmt, int a, int b, int c, int d, int e, int f, int g, int h, int i));
#endif


#ifdef	PROTOTYPES
EXPORT int
format(void (*fun)(char, long),
			long farg,
			const char *fmt,
			va_list args)
#else
EXPORT int
format(fun, farg, fmt, args)
	register void	(*fun)();
	register long	farg;
	register char	*fmt;
	va_list		args;
#endif
{
#ifdef	FORMAT_LOW_MEM
	char buf[512];
#else
	char buf[8192];
#endif
	const char *sfmt;
	register int unsflag;
	register long val;
	register char type;
	register char mode;
	register char c;
	int count;
	int i;
	short sh;
	const char *str;
	double dval;
#ifdef	USE_LONGLONG
	Llong llval = 0;
#endif
	Ulong res;
	char *rfmt;
	f_args	fa;

	fa.outf = fun;
	fa.farg = farg;
	count = 0;
	/*
	 * Main loop over the format string.
	 * Increment and check for end of string is made here.
	 */
	for (; *fmt != '\0'; fmt++) {
		c = *fmt;
		while (c != '%') {
			if (c == '\0')
				return (count);
			(*fun)(c, farg);
			c = *(++fmt);
			count++;
		}

		/*
		 * We reached a '%' sign.
		 */
		buf[0] = '\0';
		fa.buf = fa.bufp = buf;
		fa.minusflag = 0;
		fa.flags = 0;
		fa.fldwidth = 0;
		fa.signific = -1;
		fa.lzero = 0;
		fa.fillc = ' ';
		fa.prefixlen = 0;
		sfmt = fmt;
		unsflag = FALSE;
		type = '\0';
		mode = '\0';
	newflag:
		switch (*(++fmt)) {

		case '+':
			fa.flags |= PLUSFLG;
			goto newflag;

		case '-':
			fa.minusflag++;
			goto newflag;

		case ' ':
			/*
			 * If the space and the + flag are present,
			 * the space flag will be ignored.
			 */
			fa.flags |= SPACEFLG;
			goto newflag;

		case '#':
			fa.flags |= HASHFLG;
			goto newflag;

		case '0':
			/*
			 * '0' is a flag.
			 */
			fa.fillc = '0';
			goto newflag;
		}
		if (*fmt == '*') {
			fmt++;
			fa.fldwidth = va_arg(args, int);
			/*
			 * A negative fieldwith is a minus flag with a
			 * positive fieldwidth.
			 */
			if (fa.fldwidth < 0) {
				fa.fldwidth = -fa.fldwidth;
/*				fa.minusflag ^= 1;*/
				fa.minusflag = 1;
			}
		} else while (c = *fmt, is_dig(c)) {
			fa.fldwidth *= 10;
			fa.fldwidth += c - '0';
			fmt++;
		}
		if (*fmt == '.') {
			fmt++;
			fa.signific = 0;
			if (*fmt == '*') {
				fmt++;
				fa.signific = va_arg(args, int);
				if (fa.signific < 0)
					fa.signific = 0;
			} else while (c = *fmt, is_dig(c)) {
				fa.signific *= 10;
				fa.signific += c - '0';
				fmt++;
			}
		}
		if (strchr("UCSIL", *fmt)) {
			/*
			 * Enhancements to K&R and ANSI:
			 *
			 * got a type specifyer
			 *
			 * XXX 'S' in C99 is %ls, 'S' should become 'H'
			 */
			if (*fmt == 'U') {
				fmt++;
				unsflag = TRUE;
			}
			if (!strchr("CSILZODX", *fmt)) {
				/*
				 * Got only 'U'nsigned specifyer,
				 * use default type and mode.
				 */
				type = 'I';
				mode = 'D';
				fmt--;
			} else if (!strchr("CSIL", *fmt)) {
				/*
				 * no type, use default
				 */
				type = 'I';
				mode = *fmt;
			} else {
				/*
				 * got CSIL
				 */
				type = *fmt++;
				if (!strchr("ZODX", mode = *fmt)) {
					fmt--;
					mode = 'D'; /* default mode */
				}
			}
		} else switch (*fmt) {

		case 'h':
			if (!type)
				type = 'H';	/* convert to short type */
			goto getmode;

		case 'l':
			if (!type)
				type = 'L';	/* convert to long type */
			goto getmode;

		case 'j':
			if (!type)
				type = 'J';	/* convert to intmax_t type */
		/*
		 * XXX Future length modifiers:
		 * XXX	'z' size_t
		 * XXX	't' ptrdiff_t
		 * XXX	'L' with double: long double
		 */

		getmode:
			if (!strchr("udioxX", *(++fmt))) {
				if (type == 'H' && *fmt == 'h') {
					type = 'C';
					goto getmode;
				}
#ifdef	USE_LONGLONG
				if (type == 'L' && *fmt == 'l') {
					type = 'Q';
					goto getmode;
				}
#endif
				fmt--;
				mode = 'D';
			} else {
				mode = *fmt;
				if (mode != 'x')
					mode = to_cap(mode);
				if (mode == 'U')
					unsflag = TRUE;
				else if (mode == 'I')	/*XXX */
					mode = 'D';
			}
			break;
		case 'x':
			mode = 'x';
			goto havemode;
		case 'X':
			mode = 'X';
			type = 'I';
			goto havemode;
		case 'u':
			unsflag = TRUE;
		/*
		 * XXX Need to remove uppercase letters for 'long'
		 * XXX in future for POSIX/C99 compliance.
		 */
		case 'o': case 'O':
		case 'd': case 'D':
		case 'i': case 'I':
		case 'z': case 'Z':
			mode = to_cap(*fmt);
		havemode:
			if (!type)
				type = cap_ty(*fmt);
#ifdef	DEBUG
/*dbg_print("*fmt: '%c' mode: '%c' type: '%c'\n", *fmt, mode, type);*/
#endif
			if (mode == 'I')	/*XXX kann entfallen*/
				mode = 'D';	/*wenn besseres uflg*/
			break;
		case 'p':
			mode = 'P';
			type = 'L';
			break;

		case '%':
			count += prc('%', &fa);
			continue;
		case ' ':
			count += prbuf("", &fa);
			continue;
		case 'c':
			c = va_arg(args, int);
			count += prc(c, &fa);
			continue;
		case 's':
			str = va_arg(args, char *);
			count += prstring(str, &fa);
			continue;
		case 'b':
			str = va_arg(args, char *);
			fa.signific = va_arg(args, int);
			count += prstring(str, &fa);
			continue;

#ifndef	NO_FLOATINGPOINT
		case 'e':
			if (fa.signific == -1)
				fa.signific = 6;
			dval = va_arg(args, double);
			ftoes(buf, dval, 0, fa.signific);
			count += prbuf(buf, &fa);
			continue;
		case 'f':
			if (fa.signific == -1)
				fa.signific = 6;
			dval = va_arg(args, double);
			ftofs(buf, dval, 0, fa.signific);
			count += prbuf(buf, &fa);
			continue;
		case 'g':
			if (fa.signific == -1)
				fa.signific = 6;
			if (fa.signific == 0)
				fa.signific = 1;
			dval = va_arg(args, double);
			gcvt(dval, fa.signific, buf);
			count += prbuf(buf, &fa);
			continue;
#else
#	ifdef	USE_FLOATINGARGS
		case 'e':
		case 'f':
		case 'g':
			dval = va_arg(args, double);
			continue;
#	endif
#endif

		case 'r':			/* recursive printf */
		case 'R':			/* recursive printf */
			rfmt  = va_arg(args, char *);
			/*
			 * I don't know any portable way to get an arbitrary
			 * C object from a var arg list so I use a
			 * system-specific routine __va_arg_list() that knows
			 * if 'va_list' is an array. You will not be able to
			 * assign the value of __va_arg_list() but it works
			 * to be used as an argument of a function.
			 * It is a requirement for recursive printf to be able
			 * to use this function argument. If your system
			 * defines va_list to be an array you need to know this
			 * via autoconf or another mechanism.
			 * It would be nice to have something like
			 * __va_arg_list() in stdarg.h
			 */
			count += format(fun, farg, rfmt, __va_arg_list(args));
			continue;

		case 'n':
			{
				int	*ip = va_arg(args, int *);

				*ip = count;
			}
			continue;

		default:			/* Unknown '%' format */
			sfmt++;			/* Dont't print '%'   */
			count += fmt - sfmt;
			while (sfmt < fmt)
				(*fun)(*(sfmt++), farg);
			if (*fmt == '\0') {
				fmt--;
				continue;
			} else {
				(*fun)(*fmt, farg);
				count++;
				continue;
			}
		}
		/*
		 * print numbers:
		 * first prepare type 'C'har, s'H'ort, 'I'nt, or 'L'ong
		 * or 'Q'ad and 'J'==maxint_t
		 */
		switch (type) {

		case 'C':
			c = va_arg(args, int);
			val = c;		/* extend sign here */
			if (unsflag || mode != 'D')
#ifdef	DO_MASK
				val &= CHARMASK;
#else
				val = (unsigned char)val;
#endif
			break;
		case 'H':
		case 'S':			/* XXX remove 'S' in future */
			sh = va_arg(args, int);
			val = sh;		/* extend sign here */
			if (unsflag || mode != 'D')
#ifdef	DO_MASK
				val &= SHORTMASK;
#else
				val = (unsigned short)val;
#endif
			break;
		case 'I':
		default:
			i = va_arg(args, int);
			val = i;		/* extend sign here */
			if (unsflag || mode != 'D')
#ifdef	DO_MASK
				val &= INTMASK;
#else
				val = (unsigned int)val;
#endif
			break;
		case 'P':
		case 'L':
			val = va_arg(args, long);
			break;
#ifdef	USE_LONGLONG
		case 'J':			/* For now Intmax_t is Llong */
		case 'Q':
			llval = va_arg(args, Llong);
			val = llval != 0;
			break;
#endif
		}

		/*
		 * Final print out, take care of mode:
		 * mode is one of: 'O'ctal, 'D'ecimal, or he'X'
		 * oder 'Z'weierdarstellung.
		 */
		fa.bufp = &buf[sizeof (buf)-1];
		*--fa.bufp = '\0';

		if (val == 0 && mode != 'D') {
		printzero:
			/*
			 * Printing '0' with fieldwidth 0 results in no chars.
			 */
			fa.lzero = -1;
			if (fa.signific >= 0)
				fa.fillc = ' ';
			count += prstring("0", &fa);
			continue;
		} else switch (mode) {

		case 'D':
#ifdef	USE_LONGLONG
			if (type == 'Q') {
				if (!unsflag && llval < 0) {
					fa.prefix = "-";
					fa.prefixlen = 1;
					llval = -llval;
				} else if (fa.flags & PLUSFLG) {
					fa.prefix = "+";
					fa.prefixlen = 1;
				} else if (fa.flags & SPACEFLG) {
					fa.prefix = " ";
					fa.prefixlen = 1;
				}
				if (llval == 0)
					goto printzero;
				goto prunsigned;
			}
#endif
			if (!unsflag && val < 0) {
				fa.prefix = "-";
				fa.prefixlen = 1;
				val = -val;
			} else if (fa.flags & PLUSFLG) {
				fa.prefix = "+";
				fa.prefixlen = 1;
			} else if (fa.flags & SPACEFLG) {
				fa.prefix = " ";
				fa.prefixlen = 1;
			}
			if (val == 0)
				goto printzero;
		case 'U':
			/* output a long unsigned decimal number */
#ifdef	USE_LONGLONG
		prunsigned:
			if (type == 'Q')
				prldnum(llval, &fa);
			else
#endif
			prdnum(val, &fa);
			break;
		case 'O':
			/* output a long octal number */
			if (fa.flags & HASHFLG) {
				fa.prefix = "0";
				fa.prefixlen = 1;
			}
#ifdef	USE_LONGLONG
			if (type == 'Q') {
				prlonum(llval, &fa);
			} else
#endif
			{
				pronum(val & 07, &fa);
				if ((res = (val>>3) & rshiftmask(long, 3)) != 0)
					pronum(res, &fa);
			}
			break;
		case 'p':
		case 'x':
			/* output a hex long */
			if (fa.flags & HASHFLG) {
				fa.prefix = "0x";
				fa.prefixlen = 2;
			}
#ifdef	USE_LONGLONG
			if (type == 'Q')
				prlxnum(llval, &fa);
			else
#endif
			{
				prxnum(val & 0xF, &fa);
				if ((res = (val>>4) & rshiftmask(long, 4)) != 0)
					prxnum(res, &fa);
			}
			break;
		case 'P':
		case 'X':
			/* output a hex long */
			if (fa.flags & HASHFLG) {
				fa.prefix = "0X";
				fa.prefixlen = 2;
			}
#ifdef	USE_LONGLONG
			if (type == 'Q')
				prlXnum(llval, &fa);
			else
#endif
			{
				prXnum(val & 0xF, &fa);
				if ((res = (val>>4) & rshiftmask(long, 4)) != 0)
					prXnum(res, &fa);
			}
			break;
		case 'Z':
			/* output a binary long */
#ifdef	USE_LONGLONG
			if (type == 'Q')
				prlnum(llval, 2, &fa);
			else
#endif
			{
				prnum(val & 0x1, 2, &fa);
				if ((res = (val>>1) & rshiftmask(long, 1)) != 0)
					prnum(res, 2, &fa);
			}
		}
		fa.lzero = -1;
		/*
		 * If a precision (fielwidth) is specified
		 * on diouXx conversions, the '0' flag is ignored.
		 */
		if (fa.signific >= 0)
			fa.fillc = ' ';
		count += prbuf(fa.bufp, &fa);
	}
	return (count);
}

/*
 * Routines to print (not negative) numbers in an arbitrary base
 */
LOCAL	unsigned char	dtab[]  = "0123456789abcdef";
LOCAL	unsigned char	udtab[] = "0123456789ABCDEF";

LOCAL void
prnum(val, base, fa)
	register Ulong val;
	register unsigned base;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = dtab[modlbys(val, base)];
		val = divlbys(val, base);
	} while (val > 0);

	fa->bufp = p;
}

LOCAL void
prdnum(val, fa)
	register Ulong val;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = dtab[modlbys(val, (unsigned)10)];
		val = divlbys(val, (unsigned)10);
	} while (val > 0);

	fa->bufp = p;
}

/*
 * We may need to use division here too (PDP-11, non two's complement ...)
 */
LOCAL void
pronum(val, fa)
	register Ulong val;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = dtab[val & 7];
		val >>= 3;
	} while (val > 0);

	fa->bufp = p;
}

LOCAL void
prxnum(val, fa)
	register Ulong val;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = dtab[val & 15];
		val >>= 4;
	} while (val > 0);

	fa->bufp = p;
}

LOCAL void
prXnum(val, fa)
	register Ulong val;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = udtab[val & 15];
		val >>= 4;
	} while (val > 0);

	fa->bufp = p;
}

#ifdef	USE_LONGLONG
LOCAL void
prlnum(val, base, fa)
	register Ullong val;
	register unsigned base;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = dtab[modlbys(val, base)];
		val = divlbys(val, base);
	} while (val > 0);

	fa->bufp = p;
}

LOCAL void
prldnum(val, fa)
	register Ullong val;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = dtab[val % (unsigned)10];
		val = val / (unsigned)10;
	} while (val > 0);

	fa->bufp = p;
}

LOCAL void
prlonum(val, fa)
	register Ullong val;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = dtab[val & 7];
		val >>= 3;
	} while (val > 0);

	fa->bufp = p;
}

LOCAL void
prlxnum(val, fa)
	register Ullong val;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = dtab[val & 15];
		val >>= 4;
	} while (val > 0);

	fa->bufp = p;
}

LOCAL void
prlXnum(val, fa)
	register Ullong val;
	f_args *fa;
{
	register char *p = fa->bufp;

	do {
		*--p = udtab[val & 15];
		val >>= 4;
	} while (val > 0);

	fa->bufp = p;
}

#endif

/*
 * Final buffer print out routine.
 */
LOCAL int
prbuf(s, fa)
	register const char *s;
	f_args *fa;
{
	register int diff;
	register int rfillc;
	register long arg			= fa->farg;
	register void (*fun) __PR((char, long))	= fa->outf;
	register int count;
	register int lzero = 0;

	count = strlen(s);

	/*
	 * lzero becomes the number of left fill chars needed to reach signific
	 */
	if (fa->lzero < 0 && count < fa->signific)
		lzero = fa->signific - count;
	count += lzero + fa->prefixlen;
	diff = fa->fldwidth - count;
	if (diff > 0)
		count += diff;

	if (fa->prefixlen && fa->fillc != ' ') {
		while (*fa->prefix != '\0')
			(*fun)(*fa->prefix++, arg);
	}
	if (!fa->minusflag) {
		rfillc = fa->fillc;
		while (--diff >= 0)
			(*fun)(rfillc, arg);
	}
	if (fa->prefixlen && fa->fillc == ' ') {
		while (*fa->prefix != '\0')
			(*fun)(*fa->prefix++, arg);
	}
	if (lzero > 0) {
		rfillc = '0';
		while (--lzero >= 0)
			(*fun)(rfillc, arg);
	}
	while (*s != '\0')
		(*fun)(*s++, arg);
	if (fa->minusflag) {
		rfillc = ' ';
		while (--diff >= 0)
			(*fun)(rfillc, arg);
	}
	return (count);
}

/*
 * Print out one char, allowing prc('\0')
 * Similar to prbuf()
 */
#ifdef	PROTOTYPES

LOCAL int
prc(char c, f_args *fa)

#else

LOCAL int
prc(c, fa)
	char	c;
	f_args *fa;
#endif
{
	register int diff;
	register int rfillc;
	register long arg			= fa->farg;
	register void (*fun) __PR((char, long))	= fa->outf;
	register int count;

	count = 1;
	diff = fa->fldwidth - 1;
	if (diff > 0)
		count += diff;

	if (!fa->minusflag) {
		rfillc = fa->fillc;
		while (--diff >= 0)
			(*fun)(rfillc, arg);
	}
	(*fun)(c, arg);
	if (fa->minusflag) {
		rfillc = ' ';
		while (--diff >= 0)
			(*fun)(rfillc, arg);
	}
	return (count);
}

/*
 * String output routine.
 * If fa->signific is >= 0, it uses only fa->signific chars.
 * If fa->signific is 0, print no characters.
 */
LOCAL int
prstring(s, fa)
	register const char	*s;
	f_args *fa;
{
	register char	*bp;
	register int	signific;

	if (s == NULL)
		return (prbuf("(NULL POINTER)", fa));

	if (fa->signific < 0)
		return (prbuf(s, fa));

	bp = fa->buf;
	signific = fa->signific;

	while (--signific >= 0 && *s != '\0')
		*bp++ = *s++;
	*bp = '\0';

	return (prbuf(fa->buf, fa));
}

#ifdef	DEBUG
LOCAL void
dbg_print(fmt, a, b, c, d, e, f, g, h, i)
char *fmt;
{
	char	ff[1024];

	sprintf(ff, fmt, a, b, c, d, e, f, g, h, i);
	write(STDERR_FILENO, ff, strlen(ff));
}
#endif
