/* @(#)jmpdefs.h	1.2 00/11/08 Copyright 1999 J. Schilling */
/*
 *	Definitions that help to handle a jmp_buf
 *
 *	Copyright (c) 1998 J. Schilling
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

#ifndef	_JMPDEFS_H
#define	_JMPDEFS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
	jmp_buf	jb;
} jmps_t;

#ifdef	__cplusplus
}
#endif

#endif	/* _JMPDEFS_H */
