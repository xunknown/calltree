/* @(#)sprintf.c	1.14 03/06/15 Copyright 1985, 1988-2003 J. Schilling */
/*
 *	Copyright (c) 1985, 1988-2003 J. Schilling
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

/*
 * Do not include stdio.h, BSD systems define sprintf the wrong way!
 */
EXPORT	int sprintf __PR((char *, const char *, ...));

#ifdef	PROTOTYPES
static void _cput(char c, long ba)
#else
static void _cput(c, ba)
	char	c;
	long	ba;
#endif
{
	*(*(char **) ba)++ = c;
}

/* VARARGS2 */
#ifdef	PROTOTYPES
EXPORT int
sprintf(char *buf, const char *form, ...)
#else
EXPORT int
sprintf(buf, form, va_alist)
	char	*buf;
	char	*form;
	va_dcl
#endif
{
	va_list	args;
	int	cnt;
	char	*bp = buf;

#ifdef	PROTOTYPES
	va_start(args, form);
#else
	va_start(args);
#endif
	cnt = format(_cput, (long)&bp, form,  args);
	va_end(args);
	*bp = '\0';

	return (cnt);
}
