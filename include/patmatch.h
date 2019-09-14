/* @(#)patmatch.h	1.10 03/08/24 Copyright 1985 J. Schilling */

#ifndef	_PATMATCH_H
#define	_PATMATCH_H
/*
 *	Definitions for the pattern matching functions.
 *
 *	Copyright (c) 1985,1995 J. Schilling
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
/*
 *	The pattern matching functions are based on the algorithm
 *	presented by Martin Richards in:
 *
 *	"A Compact Function for Regular Expression Pattern Matching",
 *	Software-Practice and Experience, Vol. 9, 527-534 (1979)
 *
 *	Several changes have been made to the original source which has been
 *	written in BCPL:
 *
 *	'/'	is replaced by	'!'		(to allow UNIX filenames)
 *	'(',')' are replaced by	'{', '}'
 *	'\''	is replaced by	'\\'		(UNIX compatible quote)
 *
 *	Character classes have been added to allow "[<character list>]"
 *	to be used.
 *	Start of line '^' and end of line '$' have been added.
 *
 *	Any number in the following comment is zero or more occurrencies
 */
#ifndef _MCONFIG_H
#include <mconfig.h>
#endif
#ifndef _PROTOTYP_H
#include <prototyp.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#define	ALT	'!'	/* Alternation in match i.e. this!that!the_other */
#define	REP	'#'	/* Any number of occurrences of the following expr */
#define	NIL	'%'	/* Empty string (exactly nothing) */
#define	STAR	'*'	/* Any number of any character (equivalent of #?) */
#define	ANY	'?'	/* Any one character */
#define	QUOTE	'\\'	/* Quotes the next character */
#define	LBRACK	'{'	/* Begin of precedence grouping */
#define	RBRACK	'}'	/* End of precedence grouping */
#define	LCLASS	'['	/* Begin of character set */
#define	RCLASS	']'	/* End of character set */
#define	NOT	'^'	/* If first in set: invert set content */
#define	RANGE	'-'	/* Range notation in sets */
#define	START	'^'	/* Begin of a line */
#define	END	'$'	/* End of a line */

/*
 * A list of case statements that may be used for a issimple() or ispattern()
 * funtion that checks whether a string conrtains characters that need the
 * pattern matcher.
 *
 * Note that this list does not contain NOT or RANGE because you need
 * LCLASS and RCLASS in addition.
 */
#define	casePAT	case ALT: case REP: case NIL: case STAR: case ANY:	\
		case QUOTE: case LBRACK: case RBRACK:			\
		case LCLASS: case RCLASS: case START: case END:


#define	MAXPAT	128	/* Maximum length of pattern */

extern	int	    patcompile	__PR((const unsigned char * __pat, int __patlen, int * __aux));

extern	unsigned char *opatmatch	__PR((const unsigned char * __pat, const int * __aux,
						const  unsigned char * __str, int __soff, int __slen,
						int __alt));
extern	unsigned char *opatlmatch __PR((const unsigned char * __pat, const int * __aux,
						const  unsigned char * __str, int __soff, int __slen,
						int __alt));
extern	unsigned char *patmatch	__PR((const unsigned char * __pat, const int * __aux,
						const  unsigned char * __str, int __soff, int __slen,
						int __alt, int __state[]));
extern	unsigned char *patlmatch __PR((const unsigned char * __pat, const int * __aux,
						const  unsigned char * __str, int __soff, int __slen,
						int __alt, int __state[]));

#ifdef	__cplusplus
}
#endif

#endif	/* _PATMATCH_H */
