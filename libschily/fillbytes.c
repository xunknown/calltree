/* @(#)fillbytes.c	1.13 03/06/15 Copyright 1987, 1995-2003 J. Schilling */
/*
 *	fill memory with data
 *
 *	Copyright (c) 1987, 1995-2003 J. Schilling
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

#include <standard.h>
#include <align.h>
#include <schily.h>

#define	DO8(a)	a; a; a; a; a; a; a; a;

#define	cval	((char) lval)

#ifdef	PROTOTYPES
EXPORT char *
fillbytes(void *tov, int cnt, char val)
#else
EXPORT char *
fillbytes(tov, cnt, val)
	void	*tov;
	int	cnt;
	char	val;
#endif
{
	register char	*to = (char *)tov;
	register int	n;
	register long	lval;

	/*
	 * If we change cnt to be unsigned, check for == instead of <=
	 */
	if ((n = cnt) <= 0)
		return (to);

	lval = val & 0xFF;

	/*
	 * Assign byte-wise until properly aligned for a long pointer.
	 */
	while (--n >= 0 && !laligned(to)) {
		*to++ = cval;
	}
	n++;

	if (n >= (int)(8 * sizeof (long))) {
		register int rem = n % (8 * sizeof (long));

		lval |= (lval<<8);
		lval |= (lval<<16);
#if SIZE_LONG > SIZE_INT
		lval |= (lval<<32);
#endif

		n /= (8 * sizeof (long));
		{
			register long *tol = (long *)to;

			do {
				DO8 (*tol++ = lval);
			} while (--n > 0);

			to = (char *)tol;
		}
		n = rem;

		if (n >= 8) {
			n -= 8;
			do {
				DO8 (*to++ = cval);
			} while ((n -= 8) >= 0);
			n += 8;
		}
		if (n > 0) do {
			*to++ = cval;
		} while (--n > 0);
		return (to);
	}
	if (n > 0) do {
		*to++ = cval;
	} while (--n > 0);
	return (to);
}
