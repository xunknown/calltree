/* @(#)cmpbytes.c	1.15 03/06/15 Copyright 1988, 1995-2003 J. Schilling */
#ifndef lint
static	char sccsid[] =
	"@(#)cmpbytes.c	1.15 03/06/15 Copyright 1988, 1995-2003 J. Schilling";
#endif  /* lint */
/*
 *	compare data
 *
 *	Copyright (c) 1988, 1995-2003 J. Schilling
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

EXPORT int
cmpbytes(fromp, top, cnt)
	const void	*fromp;
	const void	*top;
	int		cnt;
{
	register const char	*from	= (char *)fromp;
	register const char	*to	= (char *)top;
	register int		n;
	register int		i;

	/*
	 * If we change cnt to be unsigned, check for == instead of <=
	 */
	if ((n = cnt) <= 0)
		return (cnt);

	/*
	 * Compare byte-wise until properly aligned for a long pointer.
	 */
	i = sizeof (long) - 1;
	while (--n >= 0 && --i >= 0 && !l2aligned(from, to)) {
		if (*to++ != *from++)
			goto cdiff;
	}
	n++;

	if (n >= (int)(8 * sizeof (long))) {
		if (l2aligned(from, to)) {
			register const long *froml = (const long *)from;
			register const long *tol   = (const long *)to;
			register int rem = n % (8 * sizeof (long));

			n /= (8 * sizeof (long));
			do {
				DO8(
					if (*tol++ != *froml++)
						break;
				);
			} while (--n > 0);

			if (n > 0) {
				--froml;
				--tol;
				to = (const char *)tol;
				from = (const char *)froml;
				goto ldiff;
			}
			to = (const char *)tol;
			from = (const char *)froml;
			n = rem;
		}

		if (n >= 8) {
			n -= 8;
			do {
				DO8(
					if (*to++ != *from++)
						goto cdiff;
				);
			} while ((n -= 8) >= 0);
			n += 8;
		}
		if (n > 0) do {
			if (*to++ != *from++)
				goto cdiff;
		} while (--n > 0);
		return (cnt);
	}
	if (n > 0) do {
		if (*to++ != *from++)
			goto cdiff;
	} while (--n > 0);
	return (cnt);
ldiff:
	n = sizeof (long);
	do {
		if (*to++ != *from++)
			goto cdiff;
	} while (--n > 0);
cdiff:
	return (--from - (char *)fromp);
}
