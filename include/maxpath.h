/* @(#)maxpath.h	1.6 03/08/23 Copyright 1985, 1995, 1998 J. Schilling */
/*
 *	Definitions for dealing with statically limitations on pathnames
 *
 *	Copyright (c) 1985, 1995, 1998 J. Schilling
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

#ifndef	_MAXPATH_H
#define	_MAXPATH_H

#ifndef	_DIRDEFS_H
#include <dirdefs.h>			/* Includes mconfig.h if needed	    */
#endif

#ifdef	JOS
#ifndef	_JOS_MAXP_H
#	include <jos_maxp.h>
#endif
#	define	FOUND_MAXPATHNAME
#	define	FOUND_MAXFILENAME
#else

#	ifdef	MAXPATHLEN
#		define	MAXPATHNAME	MAXPATHLEN	/* From sys/param.h */
#		define	FOUND_MAXPATHNAME
#	else
#	ifdef	PATH_MAX
#		define	MAXPATHNAME	PATH_MAX	/* From limits.h    */
#		define	FOUND_MAXPATHNAME
#	else
#		define	MAXPATHNAME	256		/* Is there a limit? */
#	endif
#	endif

/*
 * Don't use defaults here to allow recognition of problems.
 */
#	ifdef	MAXNAMELEN
#		define	MAXFILENAME	MAXNAMELEN	/* From sys/param.h */
#		define	FOUND_MAXFILENAME
#	else
#	ifdef	MAXNAMLEN
#		define	MAXFILENAME	MAXNAMLEN	/* From dirent.h    */
#		define	FOUND_MAXFILENAME
#	else
#	ifdef	DIRSIZ
#		define	MAXFILENAME	DIRSIZ		/* From sys/dir.h   */
#		define	FOUND_MAXFILENAME
#	endif
#	endif
#	endif

#if	!defined(FOUND_MAXFILENAME) && defined(FOUND_DIRSIZE)
#	define	MAXFILENAME		DIRSIZE		/* From dirdefs.h    */
#	define	FOUND_MAXFILENAME
#endif

#endif	/* JOS */

#endif	/* _MAXPATH_H */
