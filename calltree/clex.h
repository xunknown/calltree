/* @(#)clex.h	1.14 99/01/30 Copyright 1985, 1999 J. Schilling */
/*
 *	C lexer definitions
 *
 *	Copyright (c) 1985, 1999 J. Schilling
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
 * The known lexer token types
 */
#define T_NONE		0	/* C-lexer initial state	*/
#define T_EOF		1	/* EOF condifion found		*/
#define T_ERROR		2	/* Found junk characters	*/
#define T_HASH		3	/* Found a '#'			*/
#define T_LCURLY	4	/* Found a '{'			*/
#define T_RCURLY	5	/* Found a '}'			*/
#define T_OPEN		6	/* Found a '('			*/
#define T_CLOSE		7	/* Found a ')'			*/
#define T_SEMI		8	/* Found a ';'			*/
#define T_COMMA		9	/* Found a ','			*/
#define T_OPER		10	/* Found an operator symbol	*/
#define T_CHAR		11	/* Found character 'x'		*/
#define T_STRING	12	/* Sound string "xxxxxx"	*/
#define T_ALPHA		13	/* Found an alpha identifier	*/
#define T_NUMBER	14	/* Found a number		*/
#define T_COMMENT	15	/* Found a comment		*/
#define T_KEYW		16	/* Found a C keyword		*/

#define	LEXBSIZE	2048	/* Max size of a token or string*/

extern	unsigned char	lexbuf[];	/* the token buffer	*/
extern	char		*lexfile;	/* the current filename	*/
extern	int		lexline;	/* the current line #	*/
extern	char		*lextnames[];	/* lex token types names*/

extern	void	initkeyw	__PR((void));
extern	BOOL	keyword		__PR((char *name));
extern	void	clexinit	__PR((void));
extern	int	clex		__PR((FILE *fp));
