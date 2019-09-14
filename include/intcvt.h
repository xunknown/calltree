/* @(#)intcvt.h	1.4 03/12/29 Copyright 1986-2003 J. Schilling */
/*
 *	Definitions for conversion to/from integer data types of various size.
 *
 *	Copyright (c) 1986-2003 J. Schilling
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

#ifndef	_INTCVT_H
#define	_INTCVT_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif

#define	i_to_2_byte(a, i)	(((Uchar *)(a))[0] = ((i) >> 8) & 0xFF,\
				    ((Uchar *)(a))[1] = (i) & 0xFF)

#define	i_to_3_byte(a, i)	(((Uchar *)(a))[0] = ((i) >> 16)& 0xFF,\
				    ((Uchar *)(a))[1] = ((i) >> 8) & 0xFF,\
				    ((Uchar *)(a))[2] = (i) & 0xFF)

#define	i_to_4_byte(a, i)	(((Uchar *)(a))[0] = ((i) >> 24)& 0xFF,\
				    ((Uchar *)(a))[1] = ((i) >> 16)& 0xFF,\
				    ((Uchar *)(a))[2] = ((i) >> 8) & 0xFF,\
				    ((Uchar *)(a))[3] = (i) & 0xFF)



#define	a_to_byte(a)		(((Int8_t *) a)[0])

#define	a_to_u_byte(a)		((UInt8_t) \
				(((Uchar *) a)[0]		& 0xFF))

#define	a_to_u_2_byte(a)	((UInt16_t) \
				((((Uchar *) a)[1]		& 0xFF) | \
				    (((Uchar *) a)[0] << 8	& 0xFF00)))

#define	a_to_2_byte(a)		(int)(Int16_t)a_to_u_2_byte(a)

#define	a_to_u_3_byte(a)	((Ulong) \
				((((Uchar *) a)[2]		& 0xFF) | \
				    (((Uchar *) a)[1] << 8	& 0xFF00) | \
				    (((Uchar *) a)[0] << 16	& 0xFF0000)))

#define	a_to_3_byte(a)		a_to_u_3_byte(a)	/* XXX Is there a signed version ? */

#ifdef	__STDC__
#	define	__TOP_4BYTE	0xFF000000UL
#else
#	define	__TOP_4BYTE	0xFF000000
#endif

#define	a_to_u_4_byte(a)	((Ulong) \
				((((Uchar*) a)[3]		& 0xFF) | \
				    (((Uchar*) a)[2] << 8	& 0xFF00) | \
				    (((Uchar*) a)[1] << 16	& 0xFF0000) | \
				    (((Uchar*) a)[0] << 24	& __TOP_4BYTE)))

#define	a_to_4_byte(a)		(long)(Int32_t)a_to_u_4_byte(a)

/*
 * Little Endian versions of above macros
 */
#define	li_to_2_byte(a, i)	(((Uchar *)(a))[1] = ((i) >> 8) & 0xFF,\
				    ((Uchar *)(a))[0] = (i) & 0xFF)

#define	li_to_3_byte(a, i)	(((Uchar *)(a))[2] = ((i) >> 16)& 0xFF,\
				    ((Uchar *)(a))[1] = ((i) >> 8) & 0xFF,\
				    ((Uchar *)(a))[0] = (i) & 0xFF)

#define	li_to_4_byte(a, i)	(((Uchar *)(a))[3] = ((i) >> 24)& 0xFF,\
				    ((Uchar *)(a))[2] = ((i) >> 16)& 0xFF,\
				    ((Uchar *)(a))[1] = ((i) >> 8) & 0xFF,\
				    ((Uchar *)(a))[0] = (i) & 0xFF)


#define	la_to_u_2_byte(a)	((UInt16_t) \
				((((Uchar*) a)[0]		& 0xFF) | \
				    (((Uchar*) a)[1] << 8	& 0xFF00)))

#define	la_to_2_byte(a)		(int)(Int16_t)la_to_u_2_byte(a)

#define	la_to_u_3_byte(a)	((Ulong) \
				((((Uchar*) a)[0]		& 0xFF) | \
				    (((Uchar*) a)[1] << 8	& 0xFF00) | \
				    (((Uchar*) a)[2] << 16	& 0xFF0000)))

#define	la_to_3_byte(a)		la_to_u_3_byte(a)	/* XXX Is there a signed version ? */

#define	la_to_u_4_byte(a)	((Ulong) \
				((((Uchar*) a)[0]		& 0xFF) | \
				    (((Uchar*) a)[1] << 8	& 0xFF00) | \
				    (((Uchar*) a)[2] << 16	& 0xFF0000) | \
				    (((Uchar*) a)[3] << 24	& __TOP_4BYTE)))

#define	la_to_4_byte(a)		(long)(Int32_t)la_to_u_4_byte(a)

#endif	/* _INTCVT_H */
