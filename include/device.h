/* @(#)device.h	1.12 03/06/15 Copyright 1995 J. Schilling */
/*
 *	Generic header for users of major(), minor() and makedev()
 *
 *	Copyright (c) 1995 J. Schilling
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

#ifndef	_DEVICE_H
#define	_DEVICE_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif
#ifndef _PROTOTYP_H
#include <prototyp.h>
#endif

/*
 * On generic SVR4, major is a function (defined in sys/mkdev.h).
 * On Solaris it is defined ...
 * As we cannot just test if major is #define'd, we have to
 * define _FOUND_MAJOR_ instead.
 *
 * WARNING: Do never include <sys/sysmacros.h> in SVR4, it contains
 * an old definition for major()/minor() defining 8 minorbits.
 * Use <sys/mkdev.h> instead.
 */
#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>
#define	_INCL_SYS_TYPES_H
#endif
/*
 * Some systems define major in <sys/types.h>.
 * We are ready...
 */
#ifdef major
#	define _FOUND_MAJOR_
#endif

#ifdef MAJOR_IN_MKDEV
#	ifndef	_INCL_SYS_MKDEV_H
#	include <sys/mkdev.h>
#	define	_INCL_SYS_MKDEV_H
#	endif
#	define _FOUND_MAJOR_
#endif

#ifndef _FOUND_MAJOR_
#	ifdef MAJOR_IN_SYSMACROS
#		ifndef	_INCL_SYS_SYSMACROS_H
#		include <sys/sysmacros.h>
#		define	_INCL_SYS_SYSMACROS_H
#		endif
#		define _FOUND_MAJOR_
#	endif
#endif

/*
 * If we are on HP/UX before HP/UX 8,
 * major/minor are not in <sys/sysmacros.h>.
 */
#ifndef _FOUND_MAJOR_
#	if defined(hpux) || defined(__hpux__) || defined(__hpux)
#		ifndef	_INCL_SYS_MKOD_H
#		include <sys/mknod.h>
#		define	_INCL_SYS_MKOD_H
#		endif
#		define _FOUND_MAJOR_
#	endif
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * For all other systems define major()/minor() here.
 * XXX Check if this definition will be usefull for ms dos too.
 */
#ifndef _FOUND_MAJOR_
#	define major(dev)		(((dev) >> 8) & 0xFF)
#	define minor(dev)		((dev) & 0xFF)
#	define makedev(majo, mino)	(((majo) << 8) | (mino))
#endif

/*
 * Don't pollute namespace...
 */
#undef _FOUND_MAJOR_

#ifdef	__XDEV__
/*
 * The following defines are currently only needed for 'star'.
 * We make it conditional code to avoid to pollute the namespace.
 */
#define	XDEV_T	unsigned long

extern	int	minorbits;
extern	XDEV_T	minormask;
extern	XDEV_T	_dev_mask[];

#define	dev_major(dev)			(((XDEV_T)(dev)) >> minorbits)
#define	_dev_major(mbits, dev)		(((XDEV_T)(dev)) >> (mbits))

#define	dev_minor(dev)			(((XDEV_T)(dev)) & minormask)
#define	_dev_minor(mbits, dev)		(((XDEV_T)(dev)) & _dev_mask[(mbits)])


#define	dev_make(majo, mino)		((((XDEV_T)(majo)) << minorbits) | \
							((XDEV_T)(mino)))
#define	_dev_make(mbits, majo, mino)	((((XDEV_T)(majo)) << (mbits) | \
							((XDEV_T)(mino)))

extern	void	dev_init	__PR((BOOL debug));
#ifndef	dev_major
extern	XDEV_T	dev_major	__PR((XDEV_T dev));
extern	XDEV_T	_dev_major	__PR((int mbits, XDEV_T dev));
extern	XDEV_T	dev_minor	__PR((XDEV_T dev));
extern	XDEV_T	_dev_minor	__PR((int mbits, XDEV_T dev));
extern	XDEV_T	dev_make	__PR((XDEV_T majo, XDEV_T mino));
extern	XDEV_T	_dev_make	__PR((int mbits, XDEV_T majo, XDEV_T mino));
#endif

#endif	/* __XDEV__ */

#ifdef	__cplusplus
}
#endif

#endif	/* _DEVICE_H */
