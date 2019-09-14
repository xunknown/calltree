/* @(#)fctldefs.h	1.13 03/02/23 Copyright 1996 J. Schilling */
/*
 *	Generic header for users of open(), creat() and chmod()
 *
 *	Copyright (c) 1996 J. Schilling
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

#ifndef _FCTLDEFS_H
#define	_FCTLDEFS_H

#ifndef	_MCONFIG_H
#include <mconfig.h>
#endif

#ifndef	_STATDEFS_H
#include <statdefs.h>		/* For 3rd arg of open() and chmod()	*/
#endif

#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>		/* Needed for fcntl.h			*/
#define	_INCL_SYS_TYPES_H
#endif

#ifdef	HAVE_SYS_FILE_H
/*
 * Historical systems with flock() only need sys/file.h
 */
#	ifndef	_INCL_SYS_FILE_H
#	include <sys/file.h>
#	define	_INCL_SYS_FILE_H
#	endif
#endif
#ifdef	HAVE_FCNTL_H
#	ifndef	_INCL_FCNTL_H
#	include <fcntl.h>
#	define	_INCL_FCNTL_H
#endif
#endif

/*
 * Do not define more than O_RDONLY / O_WRONLY / O_RDWR / O_BINARY
 * The values may differ.
 *
 * O_BINARY is defined here to allow all applications to compile on a non DOS
 * environment without repeating this definition.
 */
#ifndef	O_RDONLY
#	define	O_RDONLY	0
#endif
#ifndef	O_WRONLY
#	define	O_WRONLY	1
#endif
#ifndef	O_RDWR
#	define	O_RDWR		2
#endif
#ifndef	O_BINARY			/* Only present on DOS or similar */
#	define	O_BINARY	0
#endif
#ifndef	O_NDELAY			/* This is undefined on BeOS :-( */
#	define	O_NDELAY	0
#endif

#ifndef	O_ACCMODE
#define	O_ACCMODE		(O_RDONLY|O_WRONLY|O_RDWR)
#endif

#endif	/* _FCTLDEFS_H */
