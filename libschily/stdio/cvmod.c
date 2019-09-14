/* @(#)cvmod.c	2.8 03/06/15 Copyright 1986, 1995-2003 J. Schilling */
/*
 *	Copyright (c) 1986, 1995-2003 J. Schilling
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

#include "io.h"

#ifndef	O_BINARY
#define	O_BINARY	0
#endif
#ifndef	O_LARGEFILE
#define	O_LARGEFILE	0
#endif

EXPORT int
_cvmod(mode, omode, flag)
	const char	*mode;
	int		*omode;
	int		*flag;
{
	while (*mode) {
		switch (*mode) {

		case 'r':   *omode |= O_RDONLY;	*flag |= FI_READ;	break;
		case 'w':   *omode |= O_WRONLY;	*flag |= FI_WRITE;	break;
		case 'e':   *omode |= O_EXCL;				break;
		case 'c':   *omode |= O_CREAT;	*flag |= FI_CREATE;	break;
		case 't':   *omode |= O_TRUNC;	*flag |= FI_TRUNC;	break;
		case 'a':   *omode |= O_APPEND;	*flag |= FI_APPEND;	break;
		case 'u':			*flag |= FI_UNBUF;	break;
			/* dummy on UNIX */
		case 'b':   *omode |= O_BINARY; *flag |= FI_BINARY;	break;
			/*
			 * XXX do we need this ?
			 * XXX May this be a problem?
			 */
		case 'l':   *omode |= O_LARGEFILE;			break;
		default:    raisecond(_badmode, 0L);
			    return (0);
		}
		mode++;
	}
	if (*flag & FI_READ && *flag & FI_WRITE) {
		*omode &= ~(O_RDONLY|O_WRONLY);
		*omode |= O_RDWR;
	}
	return (1);
}
