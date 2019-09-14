/* @(#)printf.c	1.14 03/06/15 Copyright 1985, 1989, 1995-2003 J. Schilling */
/*
 *	Copyright (c) 1985, 1989, 1995-2003 J. Schilling
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

#ifdef	printf
#	define	__no_undef__
#else
#	define	printf		__nothing__
#endif
#ifdef	fprintf
#	define	__no_undef2__
#else
#	define	fprintf		__nothing2__
#endif

#include <stdio.h>
#include <vadefs.h>
#include <standard.h>
#include <schily.h>

#ifndef	__no_undef__
#	undef	printf
#endif
#ifndef	__no_undef2__
#	undef	fprintf
#endif

#define	BFSIZ	256

typedef struct {
	short	cnt;
	char	*ptr;
	char	buf[BFSIZ];
	int	count;
	FILE	*f;
} *BUF, _BUF;

LOCAL	void	_bflush	__PR((BUF));
LOCAL	void	_bput	__PR((char, long));
EXPORT	int	fprintf	__PR((FILE *, const char *, ...))	__printflike__(2, 3);
EXPORT	int	printf	__PR((const char *, ...))		__printflike__(1, 2);

LOCAL void
_bflush(bp)
	register BUF	bp;
{
	bp->count += bp->ptr - bp->buf;
	if (filewrite(bp->f, bp->buf, bp->ptr - bp->buf) < 0)
		bp->count = EOF;
	bp->ptr = bp->buf;
	bp->cnt = BFSIZ;
}

#ifdef	PROTOTYPES
LOCAL void
_bput(char c, long l)
#else
LOCAL void
_bput(c, l)
		char	c;
		long	l;
#endif
{
	register BUF	bp = (BUF)l;

	*bp->ptr++ = c;
	if (--bp->cnt <= 0)
		_bflush(bp);
}

/* VARARGS2 */
#ifdef	PROTOTYPES
EXPORT int
printf(const char *form, ...)
#else
EXPORT int
printf(form, va_alist)
	char	*form;
	va_dcl
#endif
{
	va_list	args;
	_BUF	bb;

	bb.ptr = bb.buf;
	bb.cnt = BFSIZ;
	bb.count = 0;
	bb.f = stdout;
#ifdef	PROTOTYPES
	va_start(args, form);
#else
	va_start(args);
#endif
	format(_bput, (long)&bb, form, args);
	va_end(args);
	if (bb.cnt < BFSIZ)
		_bflush(&bb);
	return (bb.count);
}

/* VARARGS3 */
#ifdef	PROTOTYPES
EXPORT int
fprintf(FILE *file, const char *form, ...)
#else
EXPORT int
fprintf(file, form, va_alist)
	FILE	*file;
	char	*form;
	va_dcl
#endif
{
	va_list	args;
	_BUF	bb;

	bb.ptr = bb.buf;
	bb.cnt = BFSIZ;
	bb.count = 0;
	bb.f = file;
#ifdef	PROTOTYPES
	va_start(args, form);
#else
	va_start(args);
#endif
	format(_bput, (long)&bb, form, args);
	va_end(args);
	if (bb.cnt < BFSIZ)
		_bflush(&bb);
	return (bb.count);
}
