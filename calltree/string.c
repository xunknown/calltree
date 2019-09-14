/* @(#)string.c	1.14 03/11/23 Copyright 1985, 1999 J. Schilling */
#ifndef lint
static	char sccsid[] =
	"@(#)string.c	1.14 03/11/23 Copyright 1985, 1999 J. Schilling";
#endif
/*
 *	A program to produce a static calltree for C-functions
 *
 *	string handling and allocation
 *
 *	Copyright (c) 1985, 1999 J. Schilling
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
#include <stdio.h>
#include <standard.h>
#include <stdxlib.h>
#include <strdefs.h>
#include <vadefs.h>
#include <schily.h>
#include "strsubs.h"

EXPORT	char	*xmalloc	__PR((unsigned int amt, char *txt));
EXPORT	char	*concat		__PR((char *first, ...));

EXPORT char *
xmalloc(amt, txt)
	unsigned int	amt;
	char		*txt;
{
	char	*ret;

	if ((ret = (char *) malloc(amt)) == 0)
		comerr("Can't alloc %d bytes for %s.\n", amt, txt);
	return (ret);
}

/* VARARGS1 */
#ifdef	PROTOTYPES
EXPORT char *
concat(char *first, ...)
#else
EXPORT char *
concat(first, va_alist)
	char	*first;
	va_dcl
#endif
{
	va_list		args;
	char		*ret;
	register int	i;
	register unsigned len;
	register int	nstr;
	register char	*p1;
	register char	*p2;

#ifdef	PROTOTYPES
	va_start(args, first);
#else
	va_start(args);
#endif
	p1 = first;
	for (nstr = 0, len = 0; p1 != NULL; nstr++, p1 = va_arg(args, char *)) {
		len += strlen(p1);
	}
	va_end(args);

	p2 = ret = xmalloc(len + 1, "string concat");

#ifdef	PROTOTYPES
	va_start(args, first);
#else
	va_start(args);
#endif
	p1 = first;
	for (i = 0; i < nstr; i++) {
		for (; (*p2 = *p1++) != '\0'; p2++);
		p1 = va_arg(args, char *);
	}
	*p2 = '\0';
	va_end(args);
	return (ret);
}
