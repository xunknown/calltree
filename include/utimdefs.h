/* @(#)utimdefs.h	1.5 03/06/15 Copyright 2001 J. Schilling */
/*
 *	Defines for utimes() / utime()
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
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef	_UTIMDEFS_H
#define	_UTIMDEFS_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif

#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>
#define	_INCL_SYS_TYPES_H
#endif

#ifdef	HAVE_UTIMES
#ifndef _TIMEDEFS_H
#include <timedefs.h>
#endif
#endif

#ifdef	HAVE_UTIME_H
#ifndef	_INCL_UTIME_H
#include <utime.h>
#define	_INCL_UTIME_H
#endif
#else
#ifdef	HAVE_SYS_UTIME_H
#ifndef	_INCL_SYS_UTIME_H
#include <sys/utime.h>
#define	_INCL_SYS_UTIME_H
#endif
#else
struct utimbuf {
	time_t	actime;
	time_t	modtime;
};
#endif
#endif

#ifdef	__comment__
/*
 * file.c contains this
 * I am not sure if it is really needed.
 * It may be a good idea to add a test for HAVE_STRUCT_UTIMBUF
 * as in gnutar.
 */
#if (__COHERENT__ >= 0x420)
# include <sys/utime.h>
#else
#  include <utime.h>
#endif

#endif	/* __comment__ */


#endif	/* _UTIMDEFS_H */
