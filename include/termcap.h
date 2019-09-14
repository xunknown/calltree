/* @(#)termcap.h	1.6 03/06/15 Copyright 1995 J. Schilling */
/*
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

#ifndef	_TERMCAP_H
#define	_TERMCAP_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif
#ifndef _PROTOTYP_H
#include <prototyp.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Flags for tcsetflags()
 */
#define	TCF_NO_TC		0x0001	/* Don't follow tc= entries */
#define	TCF_NO_SIZE		0x0002	/* Don't get actual ttysize (li#/co#)*/
#define	TCF_NO_STRIP		0x0004	/* Don't strip down termcap buffer */

extern	char	PC;		/* Pad character */
extern	char	*BC;		/* Backspace if not "\b" from "bc" capability*/
extern	char	*UP;		/* Cursor up string from "up" capability */
extern	short	ospeed;		/* output speed coded as in ioctl */

extern	int	tgetent		__PR((char *bp, char *name));
extern	int	tcsetflags	__PR((int flags));
extern	char	*tcgetbuf	__PR((void));
extern	int	tgetnum		__PR((char *ent));
extern	BOOL	tgetflag	__PR((char *ent));
extern	char	*tgetstr		__PR((char *ent, char **array));
extern	char	*tdecode		__PR((char *ep, char **array));

extern	int	tputs		__PR((char *cp, int affcnt, int (*outc)(int c)));
extern	char	*tgoto		__PR((char *cm, int destcol, int destline));

#ifdef	__cplusplus
}
#endif

#endif	/* _TERMCAP_H */
