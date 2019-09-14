/* @(#)avoffset.c	1.22 03/11/23 Copyright 1987, 1995-2003 J. Schilling */
#ifndef lint
static	char sccsid[] =
	"@(#)avoffset.c	1.22 03/11/23 Copyright 1987, 1995-2003 J. Schilling";
#endif
/*
 * This program is a tool to generate the file "avoffset.h".
 * It is used by functions that trace the stack to get to the top of the stack.
 *
 * It generates two defines:
 *	AV_OFFSET	- offset of argv relative to the main() frame pointer
 *	FP_INDIR	- number of stack frames above main()
 *			  before encountering a NULL pointer.
 *
 *	Copyright (c) 1987, 1995-2003 J. Schilling
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
#include <stdxlib.h>
#include <signal.h>

#ifdef	HAVE_SCANSTACK
#	include <stkframe.h>
#endif

LOCAL	RETSIGTYPE	handler 	__PR((int signo));
EXPORT	int		main		__PR((int ac, char **av));
LOCAL	int		stack_direction	__PR((long *lp));

LOCAL	RETSIGTYPE
handler(signo)
	int	signo;
{
	fprintf(stderr, "Warning: Cannot scan stack on this environment.\n");
	exit(0);
}


int
main(ac, av)
	int	ac;
	char	**av;
{
	int		stdir;
#ifdef	HAVE_SCANSTACK
	register struct frame *fp = (struct frame *)getfp();
	register int	i = 0;
	register int	o = 0;
#endif

#ifdef	SIGBUS
	signal(SIGBUS, handler);
#endif
	signal(SIGSEGV, handler);

	printf("/*\n");
	printf(" * This file has been generated automatically\n");
	printf(" * by %s\n", sccsid);
	printf(" * do not edit by hand.\n");
	printf(" *\n");
	printf(" * This file includes definitions for AV_OFFSET and FP_INDIR.\n");
	printf(" * FP_INDIR is the number of fp chain elements above 'main'.\n");
	printf(" * AV_OFFSET is the offset of &av[0] relative to the frame pointer in 'main'.\n");
	printf(" *\n");
	printf(" * If getav0() does not work on a specific architecture\n");
	printf(" * the program which generated this include file may dump core.\n");
	printf(" * In this case, the generated include file does not include\n");
	printf(" * definitions for AV_OFFSET and FP_INDIR but ends after this comment.\n");
	printf(" * If AV_OFFSET or FP_INDIR are missing in this file, all programs\n");
	printf(" * which use the definitions are automatically disabled.\n");
	printf(" */\n");
	stdir = stack_direction(0);
	printf("#define	STACK_DIRECTION	%d\n", stdir);
	fflush(stdout);

#ifdef	HAVE_SCANSTACK
	/*
	 * Note: Scanning the stack to look for argc/argv
	 *	 works only in the main thread.
	 */
	while (fp->fr_savfp) {
		if (fp->fr_savpc == 0)
			break;

		fp = (struct frame *)fp->fr_savfp;

		i++;
	}
	/*
	 * Do not add any printf()'s before this line to allow avoffset
	 * to abort without printing more than the comment above.
	 */
	fp = (struct frame *)getfp();
	o = ((char *)av) - ((char *)fp);
	if ((o % sizeof (char *)) != 0) {
		fprintf(stderr, "AV_OFFSET value (%d) not a multiple of pointer size.\n", o);
		fprintf(stderr, "Disabling scanning the stack.\n");
		exit(0);
	}
	if (o < -1000 || o > 1000) {
		fprintf(stderr, "AV_OFFSET value (%d) does not look reasonable.\n", o);
		fprintf(stderr, "Disabling scanning the stack.\n");
		exit(0);
	}
	printf("#define	AV_OFFSET	%d\n", o);
	printf("#define	FP_INDIR	%d\n", i);
#endif
	exit(0);
	return (0);	/* keep lint happy */
}

LOCAL int
stack_direction(lp)
	long	*lp;
{
	auto long	*dummy[4];
	int		i;

	for (i = 0; i < 4; i++)
		dummy[i] = lp;

	if (lp == 0) {
		return (stack_direction((long *)dummy));
	} else {
		if ((long *)dummy == lp)
			return (0);
		return (((long *)dummy > lp) ? 1 : -1);
	}
}

#define	IS_AVOFFSET
#include <getfp.c>
