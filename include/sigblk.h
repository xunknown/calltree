/* @(#)sigblk.h	1.10 03/07/10 Copyright 1985, 1995-2003 J. Schilling */
/*
 *	software signal block definition
 *
 *	Copyright (c) 1985, 1995-2003 J. Schilling
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

#ifndef	_SIGBLK_H
#define	_SIGBLK_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif
#ifndef _STANDARD_H
#include <standard.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct sigblk {
	long		**sb_savfp;	/* Real saved framepointer	*/
	struct sigblk	*sb_signext;	/* Next sw signal blk for this func */
	short		sb_siglen;	/* Strlen for sb_signame	*/
	const char	*sb_signame;	/* Name of software signal	*/

					/* sb_sigfun: function to call	*/
	int		(*sb_sigfun)	__PR((const char *, long, long));

	long		sb_sigarg;	/* Second arg for sb_sigfun	*/
} SIGBLK;

/*
 * The handler function is called with three arguments:
 *
 *	1)	The name of the software signal
 *	2)	The argument from the handlecond() call
 *	3)	The argument from the raisecond() call
 */
typedef	int	(*handlefunc_t)		__PR((const char *, long, long));

extern	void	handlecond		__PR((const char *, SIGBLK *,
					    int(*)(const char *, long, long),
									long));
extern	void	raisecond		__PR((const char *, long));
extern	void	starthandlecond		__PR((SIGBLK *));
extern	void	unhandlecond		__PR((SIGBLK *));

#ifdef	__cplusplus
}
#endif

#endif	/* _SIGBLK_H */
