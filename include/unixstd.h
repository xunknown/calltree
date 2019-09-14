/* @(#)unixstd.h	1.10 03/03/06 Copyright 1996 J. Schilling */
/*
 *	Definitions for unix system interface
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

#ifndef _UNIXSTD_H
#define	_UNIXSTD_H

#ifndef	_MCONFIG_H
#include <mconfig.h>
#endif

#ifdef	HAVE_UNISTD_H

#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>
#define	_INCL_SYS_TYPES_H
#endif
#ifndef	_INCL_UNISTD_H
#include <unistd.h>
#define	_INCL_UNISTD_H
#endif

#ifndef	_SC_PAGESIZE
#ifdef	_SC_PAGE_SIZE	/* HP/UX & OSF */
#define	_SC_PAGESIZE	_SC_PAGE_SIZE
#endif
#endif

#else	/* HAVE_UNISTD_H */

/*
 * unistd.h grants things like off_t to be typedef'd.
 */
#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>
#define	_INCL_SYS_TYPES_H
#endif

#endif	/* HAVE_UNISTD_H */

#ifndef	STDIN_FILENO
#	ifdef	JOS
#		ifndef	_JOS_IO_H
#		include <jos_io.h>
#		endif
#	else
#		define	STDIN_FILENO	0
#		define	STDOUT_FILENO	1
#		define	STDERR_FILENO	2
#	endif
#endif

#ifndef	R_OK
/* Symbolic constants for the "access" routine: */
#define	R_OK	4	/* Test for Read permission */
#define	W_OK	2	/* Test for Write permission */
#define	X_OK	1	/* Test for eXecute permission */
#define	F_OK	0	/* Test for existence of File */
#endif

/* Symbolic constants for the "lseek" routine: */
#ifndef	SEEK_SET
#define	SEEK_SET	0	/* Set file pointer to "offset" */
#endif
#ifndef	SEEK_CUR
#define	SEEK_CUR	1	/* Set file pointer to current plus "offset" */
#endif
#ifndef	SEEK_END
#define	SEEK_END	2	/* Set file pointer to EOF plus "offset" */
#endif

#if	!defined(HAVE_UNISTD_H) || !defined(_POSIX_VERSION)
/*
 * Maybe we need a lot more definitions here...
 * It is not clear whether we should have prototyped definitions.
 */
extern	int	access	__PR((const char *, int));
extern	int	close	__PR((int));
extern	int	dup	__PR((int));
extern	int	dup2	__PR((int, int));
extern	void	_exit	__PR((int));
extern	int	link	__PR((const char *, const char *));
extern	int	read	__PR((int, void *, size_t));
extern	int	unlink	__PR((const char *));
extern	int	write	__PR((int, void *, size_t));
#endif

#endif	/* _UNIXSTD_H */
