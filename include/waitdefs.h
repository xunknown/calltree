/* @(#)waitdefs.h	1.10 03/02/25 Copyright 1995-2003 J. Schilling */
/*
 *	Definitions to deal with various kinds of wait flavour
 *
 *	Copyright (c) 1995-2003 J. Schilling
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

#ifndef	_WAITDEFS_H
#define	_WAITDEFS_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif

/*
 * Needed for SysVr4
 */
#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>
#define	_INCL_SYS_TYPES_H
#endif

#if	defined(HAVE_WAIT_H)
#	ifndef	_INCL_WAIT_H
#	include <wait.h>
#	define	_INCL_WAIT_H
#	endif
#else
/*
 * K&R Compiler doesn't like #elif
 */
#	if	defined(HAVE_SYS_WAIT_H)	/* POSIX.1 compl. sys/wait.h */
#	undef	HAVE_UNION_WAIT			/* POSIX.1 doesn't use U_W   */
#		ifndef	_INCL_SYS_WAIT_H
#		include <sys/wait.h>
#		define	_INCL_SYS_WAIT_H
#		endif
#	else
#	if	defined(HAVE_UNION_WAIT)	/* Pure BSD U_W / sys/wait.h */
#		ifndef	_INCL_SYS_WAIT_H
#		include <sys/wait.h>
#		define	_INCL_SYS_WAIT_H
#		endif
#	endif
#	endif
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef HAVE_UNION_WAIT
#	define WAIT_T union wait
#	ifndef WSTOPPED
#		define	WSTOPPED	0x7F
#	endif
#	ifndef WTERMSIG
#		define WTERMSIG(status)		((status).w_termsig)
#	endif
#	ifndef WCOREDUMP
#		define WCOREDUMP(status)	((status).w_coredump)
#	endif
#	ifndef WEXITSTATUS
#		define WEXITSTATUS(status)	((status).w_retcode)
#	endif
#	ifndef WSTOPSIG
#		define WSTOPSIG(status)		((status).w_stopsig)
#	endif
#	ifndef WIFSTOPPED
#		define WIFSTOPPED(status)	((status).w_stopval == \
								WSTOPPED)
#	endif
#	ifndef WIFSIGNALED
#		define WIFSIGNALED(status) 	((status).w_stopval != \
						WSTOPPED && \
						(status).w_termsig != 0)
#	endif
#	ifndef WIFEXITED
#		define WIFEXITED(status)	((status).w_stopval != \
						WSTOPPED && \
						(status).w_termsig == 0)
#	endif
#else
#	define WAIT_T int
#	ifndef WTERMSIG
#		define WTERMSIG(status)		((status) & 0x7F)
#	endif
#	ifndef WCOREDUMP
#		define WCOREDUMP(status)	((status) & 0x80)
#	endif
#	ifndef WEXITSTATUS
#		define WEXITSTATUS(status)	(((status) >> 8) & 0xFF)
#	endif
#	ifndef WSTOPSIG
#		define WSTOPSIG(status)		(((status) >> 8) & 0xFF)
#	endif
#	ifndef WIFSTOPPED
#		define	WIFSTOPPED(status)	(((status) & 0xFF) == 0x7F)
#	endif
#	ifndef WIFSIGNALED
#		define	WIFSIGNALED(status)	(((status) & 0xFF) != 0x7F && \
						WTERMSIG(status) != 0)
#	endif
#	ifndef WIFEXITED
#		define	WIFEXITED(status)	(((status) & 0xFF) == 0)
#	endif
#endif


#ifndef	WCOREFLG
#define	WCOREFLG	0x80
#endif

#ifndef	WSTOPFLG
#define	WSTOPFLG	0x7F
#endif

#ifndef	WCONTFLG
#define	WCONTFLG	0xFFFF
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _WAITDEFS_H */
