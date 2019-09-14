/* @(#)mtiodefs.h	1.4 02/08/26 Copyright 1995,2000-2002 J. Schilling */
/*
 *	Generic header for users of magnetic tape ioctl interface.
 *
 *	If there is no local mtio.h or equivalent, define
 *	simplified mtio definitions here in order
 *	to be able to do at least remote mtio on systems
 *	that have no local mtio
 *
 *	Copyright (c) 1995,2000-2002 J. Schilling
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
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	_MTIODEFS_H
#define	_MTIODEFS_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif

#ifdef	HAVE_SYS_MTIO_H

#include <sys/mtio.h>

#else	/* ! HAVE_SYS_MTIO_H */


#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Definitions for magnetic tape io control commands
 */

/*
 * structure for MTIOCTOP - magnetic tape operation command
 */
struct	mtop {
	short	mt_op;		/* op code (see below)			*/
	daddr_t	mt_count;	/* repeat count or param		*/
};

/*
 * op code values for mt_op
 */
#define	MTWEOF		0	/* write EOF record(s)			*/
#define	MTFSF		1	/* fwd space over file mark(s)		*/
#define	MTBSF		2	/* back space over file mark(s) (1/2" only ) */
#define	MTFSR		3	/* fwd space record(s) (to inter-record gap) */
#define	MTBSR		4	/* back space record(s) (to inter-record gap)*/
#define	MTREW		5	/* rewind tape				*/
#define	MTOFFL		6	/* rewind and put the drive offline	*/
#define	MTNOP		7	/* no operation (sets status ?)		*/

/*
 * structure for MTIOCGET - magnetic tape get status command
 */
struct	mtget {
	short	mt_type;	/* type of magnetic tape device		*/
				/* the next two regs are device dependent */
	short	mt_dsreg;	/* drive status 'register'		*/
	short	mt_erreg;	/* error 'register'			*/
	daddr_t	mt_resid;	/* transfer residual count		*/
	daddr_t	mt_fileno;	/* file # for current position		*/
	daddr_t	mt_blkno;	/* block # for current position		*/
};

#define	HAVE_MTGET_TYPE
#define	HAVE_MTGET_DSREG
#define	HAVE_MTGET_ERREG
#define	HAVE_MTGET_RESID
#define	HAVE_MTGET_FILENO
#define	HAVE_MTGET_BLKNO

/*
 * Define some junk here as software may assume that these two definitions
 * are always present.
 */
#define	MTIOCGET	0x12340001
#define	MTIOCTOP	0x12340002

#ifdef	__cplusplus
}
#endif

#endif	/* HAVE_SYS_MTIO_H */

#endif /* _MTIODEFS_H */
