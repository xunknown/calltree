/* @(#)btorder.h	1.16 03/06/15 Copyright 1996 J. Schilling */
/*
 *	Definitions for Bit and Byte ordering
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


#ifndef	_BTORDER_H
#define	_BTORDER_H

#ifndef	_INCL_SYS_TYPES_H
#include <sys/types.h>			/* try to load isa_defs.h on Solaris */
#define	_INCL_SYS_TYPES_H
#endif

#ifndef _MCONFIG_H
#include <mconfig.h>			/* load bit/byte-oder from xmconfig.h*/
#endif

/*
 * Convert bit-order definitions from xconfig.h into our values
 * and verify them.
 */
#if defined(HAVE_C_BITFIELDS)	&& \
    defined(BITFIELDS_LTOH)
#define	_BIT_FIELDS_LTOH
#endif

#if defined(HAVE_C_BITFIELDS)	&& \
    defined(BITFIELDS_HTOL)
#define	_BIT_FIELDS_HTOL
#endif

#if defined(HAVE_C_BITFIELDS) && \
	!defined(BITFIELDS_HTOL)
#define	BITFIELDS_LTOH
#define	_BIT_FIELDS_LTOH
#endif

#if	defined(_BIT_FIELDS_LTOH) && defined(_BIT_FIELDS_HTOL)
/*
 * #error will not work for all compilers (e.g. sunos4)
 * The following line will abort compilation on all compilers
 * if none of the above is defines. And that's  what we want.
 */
error  Only one of _BIT_FIELDS_LTOH or _BIT_FIELDS_HTOL may be defined
#endif


/*
 * Convert byte-order definitions from xconfig.h into our values
 * and verify them.
 * Note that we cannot use the definitions _LITTLE_ENDIAN and _BIG_ENDIAN
 * because they are used on IRIX-6.5 with different meaning.
 */
#if defined(HAVE_C_BIGENDIAN) && \
	!defined(WORDS_BIGENDIAN)
#define	WORDS_LITTLEENDIAN
/*#define	_LITTLE_ENDIAN*/
#endif

#if defined(HAVE_C_BIGENDIAN)	&& \
    defined(WORDS_BIGENDIAN)
#undef	WORDS_LITTLEENDIAN
/*#define	_BIG_ENDIAN*/
#endif

#if	defined(_BIT_FIELDS_LTOH) || defined(_BIT_FIELDS_HTOL)
/*
 * Bitorder is already known.
 */
#else
/*
 * Bitorder not yet known.
 */
#	if defined(sun3) || defined(mc68000) || \
	    defined(sun4) || defined(__sparc) || defined(sparc) || \
	    defined(__hppa) || defined(_ARCH_PPC) || defined(_IBMR2)
#		define _BIT_FIELDS_HTOL
#	endif

#	if defined(__sgi) && defined(__mips)
#		define _BIT_FIELDS_HTOL
#	endif

#	if defined(__i386__) || defined(__i386) || defined(i386) || \
	    defined(__alpha__) || defined(__alpha) || defined(alpha) || \
	    defined(__arm__) || defined(__arm) || defined(arm)
#		define _BIT_FIELDS_LTOH
#	endif

#	if defined(__ppc__) || defined(ppc) || defined(__ppc) || \
	    defined(__PPC) || defined(powerpc) || defined(__powerpc__)

#		if	defined(__BIG_ENDIAN__)
#			define _BIT_FIELDS_HTOL
#		else
#			define _BIT_FIELDS_LTOH
#		endif
#	endif
#endif

#endif	/* _BTORDER_H */
