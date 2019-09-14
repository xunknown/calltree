/* @(#)getcwd.h	1.3 01/07/15 Copyright 1998 J. Schilling */
/*
 *	Definitions for getcwd()
 *
 *	Copyright (c) 1998 J. Schilling
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

#ifndef	_GETCWD_H
#define	_GETCWD_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif

#ifdef JOS
#	ifndef	_INCL_SYS_STYPES_H
#	include <sys/stypes.h>
#	define	_INCL_SYS_STYPES_H
#	endif
	extern char	*gwd();
#	define		getcwd(b, len)	gwd(b)
#else
#	ifndef	HAVE_GETCWD
#		define	getcwd(b, len)	getwd(b)
#	endif
#endif

#endif	/* _GETCWD_H */
