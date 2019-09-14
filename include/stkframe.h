/* @(#)stkframe.h	1.10 03/06/15 Copyright 1995 J. Schilling */
/*
 * Common definitions for routines that parse the stack frame.
 *
 * This file has to be fixed if you want to port routines which use getfp().
 * Have a look at struct frame below and use it as a sample,
 * the new struct frame must at least contain a member 'fr_savfp'.
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

#ifndef _STKFRAME_H
#define	_STKFRAME_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif

#if defined(sun) && (defined(SVR4) || defined(__SVR4) || defined(__SVR4__))
	/*
	 * Solaris 2.x aka SunOS 5.x
	 */
#	ifdef	i386
		/*
		 * On Solaris 2.1 x86 sys/frame.h is not useful at all
		 * On Solaris 2.4 x86 sys/frame.h is buggy (fr_savfp is int!!)
		 */
#		ifndef	_INCL_SYS_REG_H
#		include <sys/reg.h>
#		define	_INCL_SYS_REG_H
#		endif
#	endif
#	ifndef	_INCL_SYS_FRAME_H
#	include <sys/frame.h>
#	define	_INCL_SYS_FRAME_H
#	endif

#else
# if	defined(sun)
	/*
	 * SunOS 4.x
	 */
#	ifndef	_INCL_MACHINE_FRAME_H
#	include <machine/frame.h>
#	define	_INCL_MACHINE_FRAME_H
#	endif
# else
	/*
	 * Anything that is not SunOS
	 */

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * XXX: I hope this will be useful on other machines (no guarantee)
 * XXX: It is taken from a sun Motorola system, but should also be useful
 * XXX: on a i386.
 * XXX: In general you have to write a sample program, set a breakpoint
 * XXX: on a small function and inspect the stackframe with adb.
 */

struct frame {
	struct frame	*fr_savfp;	/* saved frame pointer */
	int		fr_savpc;	/* saved program counter */
	int		fr_arg[1];	/* array of arguments */
};

#ifdef	__cplusplus
}
#endif

# endif	/* ! defined (sun) */
#endif	/* ! defined (sun) && (defined(SVR4) || defined(__SVR4) || defined(__SVR4__)) */

#endif	/* _STKFRAME_H */
