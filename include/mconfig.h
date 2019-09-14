/* @(#)mconfig.h	1.47 03/11/25 Copyright 1995 J. Schilling */
/*
 *	definitions for machine configuration
 *
 *	Copyright (c) 1995 J. Schilling
 *
 *	This file must be included before any other file.
 *	If this file is not included before stdio.h you will not be
 *	able to get LARGEFILE support
 *
 *	Use only cpp instructions.
 *
 *	NOTE: SING: (Schily Is Not Gnu)
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

#ifndef _MCONFIG_H
#define	_MCONFIG_H

/*
 * Tell our users that this is a Schily SING compile environment.
 */
#define	IS_SCHILY

/*
 * This hack that is needed as long as VMS has no POSIX shell.
 */
#ifdef	VMS
#	define	USE_STATIC_CONF
#endif

#ifdef	USE_STATIC_CONF
#include <xmconfig.h>	/* This is the current static autoconf stuff */
#else
#include <xconfig.h>	/* This is the current dynamic autoconf stuff */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The NetBSD people want to bother us.
 * They removed the definition for 'unix' and are bleating for every test
 * for #if defined(unix). So we need to check for NetBSD early.
 */
#ifndef	IS_UNIX
#	if defined(__NetBSD__)
#		define	IS_UNIX
#	endif
#endif

#ifndef	IS_UNIX
#	if (defined(unix) || defined(__unix) || defined(__unix__)) && !defined(__DJGPP__)
#		define	IS_UNIX
#	endif
#endif

#ifdef	__MSDOS__
#	define	IS_MSDOS
#endif

#if defined(tos) || defined(__tos)
#	define	IS_TOS
#endif

#ifdef	THINK_C
#	define	IS_MAC
#endif

#if defined(sun) || defined(__sun) || defined(__sun__)
#	define	IS_SUN
#endif

#if defined(__CYGWIN32__) || defined(__CYGWIN__)
#	define	IS_GCC_WIN32
#	define	IS_CYGWIN

#if	defined(unix) || defined(_X86)
#	define	IS_CYGWIN_1
#endif
#endif

/*--------------------------------------------------------------------------*/
/*
 * Some magic that cannot (yet) be figured out with autoconf.
 */

#if defined(sun3) || defined(mc68000) || defined(mc68020)
#	ifndef	HAVE_SCANSTACK
#	define	HAVE_SCANSTACK
#	endif
#endif
#ifdef sparc
#	ifndef	HAVE_LDSTUB
#	define	HAVE_LDSTUB
#	endif
#	ifndef	HAVE_SCANSTACK
#	define	HAVE_SCANSTACK
#	endif
#endif
#if	defined(__i386_) || defined(i386)
#	ifndef	HAVE_XCHG
#	define	HAVE_XCHG
#	endif
#	ifndef	HAVE_SCANSTACK
#	define	HAVE_SCANSTACK
#	endif
#endif

/*
 * Use of SCANSTACK is disabled by default
 */
#ifndef	USE_SCANSTACK
#	undef	HAVE_SCANSTACK
#else
/*
 * But ....
 * The tests are much better now, so always give it a chance.
 */
#ifndef	HAVE_SCANSTACK
#	define	HAVE_SCANSTACK
#endif
#endif

/*
 * Allow to overwrite the defines in the makefiles by calling
 *
 *	make COPTX=-DFORCE_SCANSTACK
 */
#ifdef	FORCE_SCANSTACK
#	undef	NO_SCANSTACK
#ifndef	HAVE_SCANSTACK
#	define	HAVE_SCANSTACK
#endif
#ifndef	USE_SCANSTACK
#	define	USE_SCANSTACK
#endif
#endif

/*
 * This is the global switch to deactivate stack scanning
 */
#ifdef	NO_SCANSTACK
#	ifdef	HAVE_SCANSTACK
#	undef	HAVE_SCANSTACK
#	endif
#endif

#if	defined(SOL2) || defined(SOL2) || \
	defined(S5R4) || defined(__S5R4) || defined(SVR4)
#	ifndef	__SVR4
#		define	__SVR4
#	endif
#endif

#ifdef	__SVR4
#	ifndef	SVR4
#		define	SVR4
#	endif
#endif

/*
 * SunOS 4.x / SunOS 5.x
 */
#if defined(IS_SUN)
#	define	HAVE_GETAV0
#endif

/*
 * AIX
 */
#if	defined(_IBMR2) || defined(_AIX)
#	ifndef	IS_UNIX
#	define	IS_UNIX		/* ??? really ??? */
#	endif
#endif

/*
 * QNX
 */
#if defined(__QNX__)
#	ifndef	IS_UNIX
#	define	IS_UNIX
#	endif
#endif

/*
 * Silicon Graphics	(must be before SVR4)
 */
#if defined(sgi) || defined(__sgi)
#	define	__NOT_SVR4__	/* Not a real SVR4 implementation */
#endif

/*
 * Data General
 */
#if defined(__DGUX__)
#ifdef	XXXXXXX
#	undef	HAVE_MTGET_DSREG
#	undef	HAVE_MTGET_RESID
#	undef	HAVE_MTGET_FILENO
#	undef	HAVE_MTGET_BLKNO
#endif
#	define	mt_type		mt_model
#	define	mt_dsreg	mt_status1
#	define	mt_erreg	mt_status2
	/*
	 * DGUX hides its flock as dg_flock.
	 */
#	define	HAVE_FLOCK
#	define	flock	dg_flock
	/*
	 * Use the BSD style wait on DGUX to get the resource usages of child
	 * processes.
	 */
#	define	_BSD_WAIT_FLAVOR
#endif

/*
 * Apple Rhapsody (This is the name for Mac OS X beta)
 */
#if defined(__NeXT__) && defined(__TARGET_OSNAME) && __TARGET_OSNAME == rhapsody
#	define	HAVE_OSDEF /* prevent later definitions to overwrite current */
#	ifndef	IS_UNIX
#	define	IS_UNIX
#	endif
#endif

/*
 * NextStep
 */
#if defined(__NeXT__) && !defined(HAVE_OSDEF)
#define	NO_PRINT_OVR
#undef	HAVE_USG_STDIO		/*
				 * NeXT Step 3.x uses __flsbuf(unsigned char, FILE *)
				 * instead of __flsbuf(int, FILE *)
				 */
#	ifndef	IS_UNIX
#	define	IS_UNIX
#	endif
#endif

/*
 * Mac OS X
 */
#if defined(__APPLE__) && defined(__MACH__)
#	ifndef	IS_UNIX
#	define	IS_UNIX
#	endif
#	define	IS_MACOS_X
#endif

/*
 * NextStep 3.x has a broken linker that does not allow us to override
 * these functions.
 */
#ifndef	__OPRINTF__

#ifdef	NO_PRINT_OVR
#	define	printf	Xprintf
#	define	fprintf	Xfprintf
#	define	sprintf	Xsprintf
#endif

#endif	/* __OPRINTF__ */

/*--------------------------------------------------------------------------*/
/*
 * If there is no flock defined by the system, use emulation
 * through fcntl record locking.
 */
#ifndef HAVE_FLOCK
#define	LOCK_SH		1	/* shared lock */
#define	LOCK_EX		2	/* exclusive lock */
#define	LOCK_NB		4	/* don't block when locking */
#define	LOCK_UN		8	/* unlock */
#endif

#ifndef	_PROTOTYP_H
#include <prototyp.h>
#endif

/*
 * gcc 2.x generally implements the long long type.
 */
#ifdef	__GNUC__
#	if	__GNUC__ > 1
#		ifndef	HAVE_LONGLONG
#			define	HAVE_LONGLONG
#		endif
#	endif
#endif

#ifdef	__CHAR_UNSIGNED__	/* GNU GCC define (dynamic)	*/
#ifndef CHAR_IS_UNSIGNED
#define	CHAR_IS_UNSIGNED	/* Sing Schily define (static)	*/
#endif
#endif

/*
 * Convert to GNU name
 */
#ifdef	HAVE_STDC_HEADERS
#	ifndef	STDC_HEADERS
#		define	STDC_HEADERS
#	endif
#endif
/*
 * Convert to SCHILY name
 */
#ifdef	STDC_HEADERS
#	ifndef	HAVE_STDC_HEADERS
#		define	HAVE_STDC_HEADERS
#	endif
#endif

#ifdef	IS_UNIX
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	'/'
#	define	PATH_DELIM_STR	"/"
#	define	far
#	define	near
#endif

/*
 * Win32 with Gygwin
 */
#ifdef	IS_GCC_WIN32
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	'/'
#	define	PATH_DELIM_STR	"/"
#	define	HAVE_DOS_DRIVELETTER
#	define	far
#	define	near
#endif

/*
 * OS/2 EMX
 */
#ifdef	__EMX__				/* We don't want to call it UNIX */
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	'/'
#	define	PATH_DELIM_STR	"/"
#	define	HAVE_DOS_DRIVELETTER
#	define	far
#	define	near
#endif

#ifdef	__BEOS__			/* We don't want to call it UNIX */
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	'/'
#	define	PATH_DELIM_STR	"/"
#	define	far
#	define	near
#endif

/*
 * DOS with DJGPP
 */
#ifdef	__DJGPP__			/* We don't want to call it UNIX */
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	'/'
#	define	PATH_DELIM_STR	"/"
#	define	HAVE_DOS_DRIVELETTER
#endif

/*
 * Vanilla DOS
 */
#if	defined(IS_MSDOS) && !defined(__DJGPP__)
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	'\\'
#	define	PATH_DELIM_STR	"\\"
#	define	HAVE_DOS_DRIVELETTER
#endif

/*
 * ATARI TOS
 */
#ifdef	IS_TOS
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	'\\'
#	define	PATH_DELIM_STR	"\\"
#	define	HAVE_DOS_DRIVELETTER
#	define	far
#	define	near
#endif

/*
 * Mac OS 9
 */
#ifdef	IS_MAC
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	':'
#	define	PATH_DELIM_STR	":"
#	define	far
#	define	near
#endif

/*
 * I hope this will make compilation on unknown OS easier.
 */
#ifndef	HAVE_PATH_DELIM			/* Default to POSIX rules */
#	define	HAVE_PATH_DELIM
#	define	PATH_DELIM	'/'
#	define	PATH_DELIM_STR	"/"
#	define	far
#	define	near
#endif

#ifdef __cplusplus
}
#endif

#endif /* _MCONFIG_H */
