/* @(#)mmapdefs.h	1.1 01/02/25 Copyright 2001 J. Schilling */
/*
 *	Definitions to be used for mmap()
 *
 *	Copyright (c) 2001 J. Schilling
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
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	_MMAPDEFS_H
#define	_MMAPDEFS_H

#ifndef	_MCONFIG_H
#include <mconfig.h>
#endif

#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>
#define	_INCL_SYS_TYPES_H
#endif

#if defined(HAVE_SMMAP)

#ifndef	_INCL_SYS_MMAN_H
#include <sys/mman.h>
#define	_INCL_SYS_MMAN_H
#endif

#ifndef	MAP_ANONYMOUS
#	ifdef	MAP_ANON
#	define	MAP_ANONYMOUS	MAP_ANON
#	endif
#endif

#ifndef MAP_FILE
#	define MAP_FILE		0	/* Needed on Apollo Domain/OS */
#endif

/*
 * Needed for Apollo Domain/OS and may be for others?
 */
#ifdef	_MMAP_WITH_SIZEP
#	define	mmap_sizeparm(s)	(&(s))
#else
#	define	mmap_sizeparm(s)	(s)
#endif

#endif	/* defined(HAVE_SMMAP) */

#endif	/* _MMAPDEFS_H */
