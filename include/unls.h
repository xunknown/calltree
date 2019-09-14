/* @(#)unls.h	1.5 03/06/15 2000 J. Schilling */
/*
 *	Modifications to make the code portable Copyright (c) 2000 J. Schilling
 *
 *	Code taken from the Linux kernel.
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

#ifndef _UNLS_H
#define	_UNLS_H

#ifndef _MCONFIG_H
#include <mconfig.h>
#endif
#ifndef _PROTOTYP_H
#include <prototyp.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

struct nls_unicode {
	unsigned char uni1;
	unsigned char uni2;
};

struct nls_table {
	char *charset;
	unsigned char **page_uni2charset;
	struct nls_unicode *charset2uni;

	void (*inc_use_count) 	__PR((void));
	void (*dec_use_count) 	__PR((void));
	struct nls_table *next;
};

extern int		init_nls		__PR((void));
extern int		register_nls		__PR((struct nls_table *));
extern int		unregister_nls		__PR((struct nls_table *));
extern struct nls_table *find_nls		__PR((char *));
extern void		list_nls		__PR((void));
extern struct nls_table *load_nls		__PR((char *));
extern void 		unload_nls		__PR((struct nls_table *));
extern struct nls_table *load_nls_default	__PR((void));
extern int		init_nls_file		__PR((char * name));

#ifdef	__cplusplus
}
#endif

#endif	/* _UNLS_H */
