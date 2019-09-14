/* @(#)movebytes.c	1.13 03/06/15 Copyright 1985, 1989, 1995-2003 J. Schilling */
/*
 *	move data
 *
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

#include <standard.h>
#include <align.h>
#include <schily.h>

#define	DO8(a)	a; a; a; a; a; a; a; a;

EXPORT char *
movebytes(fromv, tov, cnt)
	const void	*fromv;
	void		*tov;
	int		cnt;
{
	register const char	*from	= fromv;
	register char		*to	= tov;
	register int		n;

	/*
	 * If we change cnt to be unsigned, check for == instead of <=
	 */
	if ((n = cnt) <= 0)
		return (to);

	if (from >= to) {
		/*
		 * source is on higher adresses than destination:
		 *	move bytes forwards
		 */
		if (n >= (int)(8 * sizeof (long))) {
			if (l2aligned(from, to)) {
				register const long *froml = (const long *)from;
				register long *tol = (long *)to;
				register int rem = n % (8 * sizeof (long));

				n /= (8 * sizeof (long));
				do {
					DO8 (*tol++ = *froml++);
				} while (--n > 0);

				from = (const char *)froml;
				to = (char *)tol;
				n = rem;
			}

			if (n >= 8) {
				n -= 8;
				do {
					DO8 (*to++ = *from++);
				} while ((n -= 8) >= 0);
				n += 8;
			}

			if (n > 0) do {
				*to++ = *from++;
			} while (--n > 0);
			return (to);
		}
		if (n > 0) do {
			*to++ = *from++;
		} while (--n > 0);
		return (to);
	} else {
		char *ep;

		/*
		 * source is on lower adresses than destination:
		 *	move bytes backwards
		 */
		to += n;
		from += n;
		ep = to;
		if (n >= (int)(8 * sizeof (long))) {
			if (l2aligned(from, to)) {
				register const long *froml = (const long *)from;
				register long *tol = (long *)to;
				register int rem = n % (8 * sizeof (long));

				n /= (8 * sizeof (long));
				do {
					DO8 (*--tol = *--froml);
				} while (--n > 0);

				from = (const char *)froml;
				to = (char *)tol;
				n = rem;
			}
			if (n >= 8) {
				n -= 8;
				do {
					DO8 (*--to = *--from);
				} while ((n -= 8) >= 0);
				n += 8;
			}
			if (n > 0) do {
				*--to = *--from;
			} while (--n > 0);
			return (ep);
		}
		if (n > 0) do {
			*--to = *--from;
		} while (--n > 0);
		return (ep);
	}
}
