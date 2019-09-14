/* @(#)seterrno.c	1.8 03/06/15 Copyright 1985, 1995-2003 J. Schilling */
/*
 *	Set error number
 *
 *	Copyright (c) 1985, 1995-2003 J. Schilling
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
#include <errno.h>
#include <schily.h>

#ifndef	HAVE_ERRNO_DEF
extern	int	errno;
#endif

#ifdef	seterrno
#undef	seterrno
#endif

EXPORT int
seterrno(err)
	int	err;
{
	int	old = errno;

	errno = err;
	return (old);
}
