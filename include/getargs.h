/* @(#)getargs.h	1.9 03/06/15 Copyright 1985 J. Schilling */
/*
 *	Definitions for getargs()/getallargs()/getfiles()
 *
 *	Copyright (c) 1985 J. Schilling
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

#ifndef	_GETARGS_H
#define	_GETARGS_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif
#ifndef _PROTOTYP_H
#include <prototyp.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#define	NOARGS		  0	/* No more args			*/
#define	NOTAFLAG	  1	/* Not a flag type argument	*/
#define	BADFLAG		(-1)	/* Not a valid flag argument	*/
#define	BADFMT		(-2)	/* Error in format string	*/
#define	NOTAFILE	(-3)	/* Seems to be a flag type	*/

typedef	int	(*getargfun)	__PR((const void *, void *));

#ifdef	__cplusplus
}
#endif

#endif	/* _GETARGS_H */
