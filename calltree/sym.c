/* @(#)sym.c	1.17 99/01/30 Copyright 1985, 1999 J. Schilling */
#ifndef lint
static	char sccsid[] =
	"@(#)sym.c	1.17 99/01/30 Copyright 1985, 1999 J. Schilling";
#endif
/*
 *	A program to produce a static calltree for C-functions
 *	symbol handling
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
#include <stdxlib.h>
#include <strdefs.h>
#include "sym.h"
#include "strsubs.h"

LOCAL	sym_t	*newsym		__PR((char *name, sym_t *gtab));
EXPORT	sym_t	*lookup		__PR((char *name, sym_t **table, sym_t *gtab));

LOCAL sym_t *
newsym(name, gtab)
	char	*name;
	sym_t	*gtab;
{
	sym_t *tmp;
	sym_t *t = (sym_t *)0;

	tmp = (sym_t *) xmalloc(sizeof(sym_t), "allocsym");
	tmp->s_left		= (sym_t *) NULL;
	tmp->s_right		= (sym_t *) NULL;
	tmp->s_filename		= (char *) NULL;
	tmp->s_sym		= (sym_t *) NULL;
	tmp->s_lineno		= 0;
	tmp->s_flags		= 0;

	if (gtab != L_CREATE)
		t = lookup(name, &gtab, FALSE);
	if (t) {
		tmp->s_name = t->s_name;
	} else {
		tmp->s_name = xmalloc(strlen(name)+1, "allocsym string");
	}
	strcpy(tmp->s_name, name);
	return (tmp);
}

EXPORT sym_t *
lookup(name, table, gtab)
		 char	*name;
	register sym_t	**table;
		 sym_t	*gtab;
{
	register int	cmp;

	if (*table) {
		cmp = strcmp(name, (*table)->s_name);
		if (cmp == 0)
			return (*table);
		else if (cmp < 0)
			return (lookup(name, &((*table)->s_left), gtab));
		else if (cmp > 0)
			return (lookup(name, &((*table)->s_right), gtab));

	} else if (gtab != L_LOOK) {
		return (*table = newsym(name, gtab));
	}
	return ((sym_t *)0);
}
