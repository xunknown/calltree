/* @(#)strcatl.c	1.12 03/10/29 Copyright 1985, 1989, 1995-2003 J. Schilling */
/*
 *	list version of strcat()
 *
 *	concatenates all past first parameter until a NULL pointer is reached
 *
 *	WARNING: a NULL constant is not a NULL pointer, so a caller must
 *		cast a NULL constant to a pointer: (char *)NULL
 *
 *	returns pointer past last character (to '\0' byte)
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

#include <mconfig.h>
#include <vadefs.h>
#include <standard.h>
#include <schily.h>

/* VARARGS3 */
#ifdef	PROTOTYPES
EXPORT char *
strcatl(char *to, ...)
#else
EXPORT char *
strcatl(to, va_alist)
	char *to;
	va_dcl
#endif
{
		va_list	args;
	register char	*p;
	register char	*tor = to;

#ifdef	PROTOTYPES
	va_start(args, to);
#else
	va_start(args);
#endif
	while ((p = va_arg(args, char *)) != NULL) {
		while ((*tor = *p++) != '\0') {
			tor++;
		}
	}
	*tor = '\0';
	va_end(args);
	return (tor);
}
