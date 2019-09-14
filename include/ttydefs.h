/* @(#)ttydefs.h	1.26 03/02/28 Copyright 1984-2003 J. Schilling */
/*
 *	Terminal driver tty mode handling
 *
 *	Copyright (c) 1984-2003 J. Schilling
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


#ifndef	_TTYDEFS_H
#define	_TTYDEFS_H

#ifndef	_MCONFIG_H
#include <mconfig.h>
#endif

#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>
#define	_INCL_SYS_TYPES_H
#endif

#ifdef	JOS
#	include <ttymodes.h>
#	include <spfcode.h>
#else
#ifdef	HAVE_TERMIOS_H
#	include <termios.h>
#	define	_INCL_TERMIOS_H
#	ifdef TIOCGETA				/* FreeBSD */
#		define	TCGETS	TIOCGETA
#		define	TCSETSW	TIOCSETAW
#	endif
#	ifdef TCGETATTR
#		define	TCGETS	TCGETATTR
#		define	TCSETSW	TCSETATTRD
#	endif
#else
#	ifdef	HAVE_TERMIO_H
#		include	<termio.h>
#		define	_INCL_TERMIO_H
#		ifndef	TCGETS
#		define	termios	termio
#		define	TCGETS	TCGETA
#		define	TCSETSW	TCSETAW
#		endif
#	else
#		define	USE_V7_TTY
#	endif
#endif
#endif

#if !defined(HAVE_TCGETATTR) || !defined(HAVE_TCSETATTR)
#	undef	TCSANOW
#endif

#ifndef	TCSANOW
#	if	!defined(TCGETS) || !defined(TCSETSW)
#		define	USE_V7_TTY
#	endif
#endif

#if !defined(_INCL_TERMIOS_H) && !defined(_INCL_TERMIO_H)
#ifdef	HAVE_SYS_IOCTL_H
#	ifndef	_INCL_SYS_IOCTl_H
#	include	<sys/ioctl.h>
#	define	_INCL_SYS_IOCTL_H
#	endif
#endif
#endif

#ifdef	HAVE_SYS_BSDTTY_H
#include <sys/bsdtty.h>
#endif

#if	!defined(TIOCGWINSZ) && ! defined(TIOCGSIZE)
#	ifndef	_INCL_SYS_IOCTl_H
#	include	<sys/ioctl.h>
#	define	_INCL_SYS_IOCTL_H
#	endif
#endif

#ifndef	OXTABS					/* OS/2 EMX */
#define	OXTABS	0
#endif
#ifndef	XTABS
#	ifndef	TAB3				/* FreeBSD */
#	define	TABDLY	OXTABS
#	define	XTABS	OXTABS
#	else
#	define	XTABS	TAB3
#	endif
#endif
#ifndef	ONLCR					/* OS/2 EMX */
#define	ONLCR	0
#endif
#ifndef	OCRNL					/* FreeBSD */
#	define	OCRNL	0
#endif
#ifndef	ONLRET					/* FreeBSD */
#	define	ONLRET	0
#endif
#ifndef	_POSIX_VDISABLE
#	define	_POSIX_VDISABLE	0
#endif

#endif	/* _TTYDEFS_H */
