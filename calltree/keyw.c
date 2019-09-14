/* @(#)keyw.c	1.11 99/01/30 Copyright 1985, 1999 J. Schilling */
#ifndef lint
static	char sccsid[] =
	"@(#)keyw.c	1.11 99/01/30 Copyright 1985, 1999 J. Schilling";
#endif
/*
 *	A program to produce a static calltree for C-functions
 *
 *	C langugage key words
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
#include "sym.h"
#include "clex.h"

EXPORT	void	initkeyw	__PR((void));
EXPORT	BOOL	keyword		__PR((char * name));

LOCAL	sym_t	*keywords = NULL;

LOCAL	char *keywlist[] = {
		"char", "double", "enum", "float", "int", "long", "short",
		"struct", "union", "void",

		"auto", "const", "extern", "register", "signed", "static",
		"unsigned", "volatile",

		"break", "case", "continue", "default", "do", "else","for",
		"goto", "if", "return", "sizeof", "switch", "typedef", "while",

		0
};

EXPORT void
initkeyw()
{
	register char	**np = keywlist;

	while (*np != 0)
		lookup(*np++, &keywords, L_CREATE);
}

EXPORT BOOL
keyword(name)
	char	*name;
{
	return (lookup(name, &keywords, L_LOOK) != NULL);
}
