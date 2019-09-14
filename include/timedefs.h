/* @(#)timedefs.h	1.11 03/11/24 Copyright 1996 J. Schilling */
/*
 *	Generic header for users of time(), gettimeofday() ...
 *
 *	It includes definitions for time_t, struct timeval, ...
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

#ifndef	_TIMEDEFS_H
#define	_TIMEDEFS_H

#ifndef	_MCONFIG_H
#include <mconfig.h>
#endif

#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>		/* Needed for time_t		*/
#define	_INCL_SYS_TYPES_H
#endif

#ifdef	TIME_WITH_SYS_TIME
#	ifndef	_INCL_SYS_TIME_H
#	include <sys/time.h>
#	define	_INCL_SYS_TIME_H
#	endif
#	ifndef	_INCL_TIME_H
#	include <time.h>
#	define	_INCL_TIME_H
#	endif
#else
#ifdef	HAVE_SYS_TIME_H
#	ifndef	_INCL_SYS_TIME_H
#	include <sys/time.h>
#	define	_INCL_SYS_TIME_H
#	endif
#else
#	ifndef	_INCL_TIME_H
#	include <time.h>
#	define	_INCL_TIME_H
#	endif
#endif
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#if	defined(__CYGWIN32__) || defined(__EMX__) || defined(__linux__) || defined(__DJGPP__)
/*
 * Cygnus defines struct timeval in sys/time.h but not timerclear
 * timerclear is defined in windows32/Sockets.h ???
 *
 * EMX for OS/2 defines struct timeval in sys/time.h but not timerclear
 *
 * Linux defines struct timeval in sys/time.h but if __USE_BSD is not
 * defined, timerclear is missing.
 */
#ifndef	timerclear
#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0
#endif
#endif

#ifndef	timerclear

#ifndef	VMS
struct timeval {
	long	tv_sec;
	long	tv_usec;
};
#endif

struct timezone {
	int	tz_minuteswest;
	int	tz_dsttime;
};

#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0

#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _TIMEDEFS_H */
