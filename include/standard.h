/* @(#)standard.h	1.31 03/08/23 Copyright 1985 J. Schilling */
/*
 *	standard definitions
 *
 *	This file should be included past:
 *
 *	mconfig.h / config.h
 *	stdio.h
 *	stdlib.h	(better use stdxlib.h)
 *	unistd.h	(better use unixstd.h) needed LARGEFILE support
 *
 *	If you need stdio.h, you must include it before standard.h
 *
 *	Copyright (c) 1985 J. Schilling
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

#ifndef _STANDARD_H
#define	_STANDARD_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif
#ifndef _PROTOTYP_H
#include <prototyp.h>
#endif

#ifdef	M68000
#	ifndef	tos
#		define	JOS	1
#	endif
#endif

/*
 *	fundamental constants
 */
#ifndef	NULL
#	define	NULL		0
#endif
#ifndef	TRUE
#	define	TRUE		1
#	define	FALSE		0
#endif

/*
 *	Program exit codes
 */
#define	EX_BAD			(-1)

/*
 *	standard storage class definitions
 */
#define	GLOBAL	extern
#define	IMPORT	extern
#define	EXPORT
#define	INTERN	static
#define	LOCAL	static
#define	FAST	register

#ifndef	PROTOTYPES
#	ifndef	const
#		define	const
#	endif
#	ifndef	signed
#		define	signed
#	endif
#	ifndef	volatile
#		define	volatile
#	endif
#endif	/* PROTOTYPES */

/*
 *	standard type definitions
 *
 *	The hidden Schily BOOL definition is used in case we need to deal
 *	with other BOOL defines on systems we like to port to.
 */
typedef int __SBOOL;
typedef int BOOL;
#ifdef	JOS
#	ifndef	__GNUC__
#	define	NO_VOID
#	endif
#endif
#ifdef	NO_VOID
	typedef	int	VOID;
#	ifndef	lint
		typedef int void;
#	endif
#else
	typedef	void	VOID;
#endif

#if	defined(_INCL_SYS_TYPES_H) || defined(off_t)
#	ifndef	FOUND_OFF_T
#	define	FOUND_OFF_T
#	endif
#endif
#if	defined(_INCL_SYS_TYPES_H) || defined(size_t)
#	ifndef	FOUND_SIZE_T
#	define	FOUND_SIZE_T
#	endif
#endif

#ifdef	__never_def__
/*
 * It turns out that we cannot use the folloginw definition because there are
 * some platforms that do not behave application friendly. These are mainly
 * BSD-4.4 based systems (which #undef a definition when size_t is available.
 * We actually removed this code because of a problem with QNX Neutrino.
 * For this reason, it is important not to include <sys/types.h> directly but
 * via the Schily SING include files so we know whether it has been included
 * before we come here.
 */
#if	defined(_SIZE_T)	|| defined(_T_SIZE_)	|| defined(_T_SIZE) || \
	defined(__SIZE_T)	|| defined(_SIZE_T_)	|| \
	defined(_GCC_SIZE_T)	|| defined(_SIZET_)	|| \
	defined(__sys_stdtypes_h) || defined(___int_size_t_h) || defined(size_t)

#ifndef	FOUND_SIZE_T
#	define	FOUND_SIZE_T	/* We already included a size_t definition */
#endif
#endif
#endif	/* __never_def__ */

#if defined(_JOS) || defined(JOS)
#	ifndef	_SCHILY_H
#	include <schily.h>
#	endif

#	ifndef	_JOS_DEFS_H
#	include <jos_defs.h>
#	endif

#	ifndef	_JOS_IO_H
#	include <jos_io.h>
#	endif
#endif

#endif	/* _STANDARD_H */
