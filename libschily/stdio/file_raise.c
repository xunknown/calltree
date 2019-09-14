/* @(#)file_raise.c	1.7 03/06/15 Copyright 1986, 1995-2003 J. Schilling */
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

EXPORT void
file_raise(f, flg)
	register FILE *f;
	int flg;
{
	int	oflag;
extern	int	_io_glflag;

	if (f == (FILE *)NULL) {
		if (flg)
			_io_glflag &= ~_IONORAISE;
		else
			_io_glflag |= _IONORAISE;
		return;
	}
	down(f);

	oflag = my_flag(f);

	if (flg)
		oflag &= ~_IONORAISE;
	else
		oflag |= _IONORAISE;

	set_my_flag(f, oflag);
}
