/* @(#)clex.c	1.18 00/05/07 Copyright 1985, 1999 J. Schilling */
#ifndef lint
static	char sccsid[] =
	"@(#)clex.c	1.18 00/05/07 Copyright 1985, 1999 J. Schilling";
#endif
/*
 *	A program to produce a static calltree for C-functions
 *
 *	lexicalical section
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

#include <mconfig.h>
#include <stdio.h>
#include <standard.h>
#include <schily.h>
#include "sym.h"
#include "clex.h"

extern BOOL debug;

#define	LEXBSIZE	2048
#define	lexbend		&lexbuf[LEXBSIZE-1]/* no var to make it not trashable*/

EXPORT	unsigned char	lexbuf[LEXBSIZE];
EXPORT	char	*lexfile;
EXPORT	int	lexline;
LOCAL	int	lnextc;
LOCAL	int	lextype;

EXPORT	void	clexinit	__PR((void));
EXPORT	int	clex		__PR((FILE *fp));
LOCAL	void	sympanic	__PR((char* txt));

/*
 * Initialize lexter state.
 */
EXPORT void
clexinit()
{
	lnextc = ' ';
	lextype = T_NONE;
	lexfile = NULL;
	lexline = 1;
}

/*
 * Get next token from input.
 */
EXPORT int
clex(fp)
	FILE	*fp;
{
	register unsigned char	*bp;
	register int		c;

/* if (lnextc == '\n')*/
/*	lexline--;*/

again:
	bp = lexbuf;
	*bp = c = lnextc;
	lextype = T_NONE;

	for (;;*++bp = c = getc(fp)) {

/*		printf("<%c:%3o>:%s(%d)[%s]\n", *bp, *bp, lextnames[lextype], lextype, lexbuf);flush();*/
		if (c == EOF) {
			if (lextype == T_NONE) {
				lextype = T_EOF;
			} else {
				break;
			}

		} else switch(c) {

		case  ' ': case  '\t': case  '\b':
		case  '\v': case  '\f':
		case  '\r': case  '\n':
			/*
			 * blank
			 */
			if (c == '\n')
				lexline++;
			if (lextype == T_NONE) {
				bp--;
			} else {
				if (c == '\n')
					lexline--;
				goto out;
			}
			break;

		case '\'':
			/*
			 * a character
			 */
			if (lextype == T_NONE) {
				lextype = T_CHAR;
				if ((*++bp = getc(fp)) == '\\')
					*++bp = getc(fp);
				if (*bp == '\n')
					lexline++;
				if ((*++bp = getc(fp)) != '\'')
					lextype = T_ERROR;
				if (*bp == '\n')
					lexline++;
			} else {
				goto out;
			}
			break;

		case '"':
			/*
			 * a string
			 */
			if (lextype == T_NONE) {
				lextype = T_STRING;
				while ((c = getc(fp)) != EOF) {
					*++bp = c;
					if (bp >= lexbend)
						sympanic("in string");
					if (c == '\n') {
						lexline++;
					} else if (c == '\\') {
						*++bp = getc(fp);
					} else if (c == '"') {
						*++bp = getc(fp);
						break;
					}
				}
			}
			goto out;

		case '/':
			/*
			 * a divison or the start of a comment
			 */
			if (lextype == T_NONE) {
				lextype = T_OPER;
				if ((*++bp = getc(fp)) == '*') {
					lextype = T_COMMENT;
					while ((c = getc(fp)) != EOF) {
						*bp = c;
					comment:
						if (bp >= lexbend)
							sympanic("in comment");
						if (c == '\n') {
							lexline++;
						} else if (c == '*') {
							if ((*bp++ = getc(fp)) == '/') {
								break;
							} else {
								c = *--bp;
								goto comment;
							}
						}
					}
				} else {
					goto out;
				}
			} else {
				goto out;
			}
			break;

		case ';':
			/*
			 * the end of a statement
			 */
			if (lextype == T_NONE)
				lextype = T_SEMI;
			else
				goto out;
			break;

		case '(':
			/*
			 * This may be the start of an argument list...
			 */
			if (lextype == T_NONE)
				lextype = T_OPEN;
			else
				goto out;
			break;

		case ')':
			/*
			 * This may be the end of an argument list...
			 */
			if (lextype == T_NONE)
				lextype = T_CLOSE;
			else
				goto out;
			break;

		case ',':
			if (lextype == T_NONE)
				lextype = T_COMMA;
			else
				goto out;
			break;

		case '{':
			/*
			 * Start of a block
			 */
			if (lextype == T_NONE)
				lextype = T_LCURLY;
			else
				goto out;
			break;

		case '}':
			/*
			 * End of a block
			 */
			if (lextype == T_NONE)
				lextype = T_RCURLY;
			else
				goto out;
			break;

		case '#':
			if (lextype == T_NONE) {
				lextype = T_HASH;
			} else {
				goto out;
			}
			break;

		case '!': case '%': case '&': case '*': case '+': case '-':
		case '.': case ':': case '<': case '=': case '>': case '?':
		case '[': case '\\': case ']': case '^': case '|': case '~':
		case '`':			/* '`' is GCOS BCD constant */
			if (lextype == T_NONE) {
				lextype = T_OPER;
			} else {
				goto out;
			}
			break;

		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
		case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
		case 's': case 't': case 'u': case 'v': case 'w': case 'x':
		case 'y': case 'z':
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
		case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
		case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
		case 'Y': case 'Z':
		case '_':
		case '$':	/* Allow VMS style identifiers */
			/*
			 * alpha characters (may be an identifier)
			 */
			if (lextype == T_NONE)
				lextype = T_ALPHA;
			else if (lextype != T_ALPHA)
				goto out;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			/*
			 * numeric characters
			 */
			if (lextype == T_NONE)
				lextype = T_NUMBER;
			else if ((lextype != T_NUMBER) && (lextype != T_ALPHA))
				goto out;
			break;

		default:
/*			error("default: '%c'\n", c);*/
			/*
			 * anything else ...
			 */
			if (lextype == T_NONE)
				lextype = T_ERROR;
			else
				goto out;
			break;
		}
	}
out:
	lnextc = *bp;
	*bp = '\0';
	if (bp >= lexbend)
		sympanic("");
	if (lextype == T_ALPHA) {
		if (keyword((char *)lexbuf))
			lextype = T_KEYW;
	}
	if (lextype == T_COMMENT) {
		goto again;
	}

	if (debug > 1) {
		error("%s:%d %s: %s\n",
				lexfile, lexline, lextnames[lextype], lexbuf);
	}
	return(lextype);
}

LOCAL void
sympanic(txt)
	char	*txt;
{
	comerrno(EX_BAD, "PANIC: Symbol buffer too short %s line %d in file '%s'\n",
		txt,
		lexline,
		lexfile);
}

char	*lextnames[] = {
	"NONE",
	"EOF",
	"ERROR",
	"HASH",
	"LCURLY",
	"RCURLY",
	"OPEN",
	"CLOSE",
	"SEMI",
	"COMMA",
	"OPER",
	"CHAR",
	"STRING",
	"ALPHA",
	"NUMBER",
	"COMMENT",
	"KEYW",
	NULL
};
