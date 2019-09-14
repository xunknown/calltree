/* @(#)fileseek.c	1.11 03/06/15 Copyright 1986, 1996-2003 J. Schilling */
/*
 *	Copyright (c) 1986, 1996-2003 J. Schilling
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

/*
 * Note that because of a definition in io.h we are using fseeko()/ftello()
 * instead of fseek()/ftell() if available.
 */

static	char	_seekerr[]	= "file_seek_err";

EXPORT int
fileseek(f, pos)
	register FILE	*f;
	off_t	pos;
{
	int	ret;

	down(f);
	ret = fseek(f, pos, SEEK_SET);
	if (ret < 0 && !(my_flag(f) & _IONORAISE))
		raisecond(_seekerr, 0L);
	return (ret);
}
