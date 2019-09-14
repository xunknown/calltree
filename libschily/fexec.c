/* @(#)fexec.c	1.23 03/10/29 Copyright 1985, 1995-2003 J. Schilling */
/*
 *	Execute a program with stdio redirection
 *
 *	Copyright (c) 1985, 1995-2003 J. Schilling
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
#define	fexecl	__nothing_1_	/* prototype in schily.h is wrong */
#define	fexecle	__nothing_2_	/* prototype in schily.h is wrong */
#include <schily.h>
#undef	fexecl
#undef	fexecle
	int fexecl	__PR((const char *, FILE *, FILE *, FILE *, ...));
	int fexecle	__PR((const char *, FILE *, FILE *, FILE *, ...));
#include <unixstd.h>
#include <stdxlib.h>
#include <strdefs.h>
#include <vadefs.h>

#ifdef JOS
#	include <error.h>
#else
#	include <errno.h>
#endif
#include <fctldefs.h>
#include <dirdefs.h>
#include <maxpath.h>

#define	MAX_F_ARGS	16

#ifdef	__EMX__
#define	PATH_ENV_DELIM	';'
#else
#define	PATH_ENV_DELIM	':'
#endif

extern	char **environ;

LOCAL void	 fdcopy __PR((int, int));
LOCAL void	 fdmove __PR((int, int));
LOCAL const char *chkname __PR((const char *, const char *));
LOCAL const char *getpath __PR((char * const *));

#ifdef	PROTOTYPES
EXPORT int
fexecl(const char *name, FILE *in, FILE *out, FILE *err, ...)
#else
EXPORT int
fexecl(name, in, out, err, va_alist)
	char	*name;
	FILE	*in;
	FILE	*out;
	FILE	*err;
	va_dcl
#endif
{
	va_list	args;
	int	ac = 0;
	char	*xav[MAX_F_ARGS];
	char	**av;
	char	**pav;
	char	*p;
	int	ret;

#ifdef	PROTOTYPES
	va_start(args, err);
#else
	va_start(args);
#endif
	while (va_arg(args, char *) != NULL)
		ac++;
	va_end(args);

	if (ac < MAX_F_ARGS) {
		pav = av = xav;
	} else {
		pav = av = (char **)malloc((ac+1)*sizeof (char *));
		if (av == 0)
			return (-1);
	}

#ifdef	PROTOTYPES
	va_start(args, err);
#else
	va_start(args);
#endif
	do {
		p = va_arg(args, char *);
		*pav++ = p;
	} while (p != NULL);
	va_end(args);

	ret = fexecv(name, in, out, err, ac, av);
	if (av != xav)
		free(av);
	return (ret);
}

#ifdef	PROTOTYPES
EXPORT int
fexecle(const char *name, FILE *in, FILE *out, FILE *err, ...)
#else
EXPORT int
fexecle(name, in, out, err, va_alist)
	char	*name;
	FILE	*in;
	FILE	*out;
	FILE	*err;
	va_dcl
#endif
{
	va_list	args;
	int	ac = 0;
	char	*xav[MAX_F_ARGS];
	char	**av;
	char	**pav;
	char	*p;
	char	**env;
	int	ret;

#ifdef	PROTOTYPES
	va_start(args, err);
#else
	va_start(args);
#endif
	while (va_arg(args, char *) != NULL)
		ac++;
	env = va_arg(args, char **);
	va_end(args);

	if (ac < MAX_F_ARGS) {
		pav = av = xav;
	} else {
		pav = av = (char **)malloc((ac+1)*sizeof (char *));
		if (av == 0)
			return (-1);
	}

#ifdef	PROTOTYPES
	va_start(args, err);
#else
	va_start(args);
#endif
	do {
		p = va_arg(args, char *);
		*pav++ = p;
	} while (p != NULL);
	va_end(args);

	ret = fexecve_calltree(name, in, out, err, av, env);
	if (av != xav)
		free(av);
	return (ret);
}

EXPORT int
fexecv(name, in, out, err, ac, av)
	const char *name;
	FILE *in, *out, *err;
	int ac;
	char *av[];
{
	av[ac] = NULL;			/*  force list to be null terminated */
	return (fexecve_calltree(name, in, out, err, av, environ));
}

EXPORT int
fexecve_calltree(name, in, out, err, av, env)
	const char *name;
	FILE *in, *out, *err;
	char * const av[], * const env[];
{
	char	nbuf[MAXPATHNAME+1];
	char	*np;
	const char *path;
	int	ret;
	int	fin;
	int	fout;
	int	ferr;
#ifndef	JOS
	int	o[3];
	int	f[3];
	int	errsav;
#endif

	fflush(out);
	fflush(err);
	fin  = fdown(in);
	fout = fdown(out);
	ferr = fdown(err);
#ifdef JOS

	/*
	 * If name contains a pathdelimiter ('/' on unix)
	 * or name is too long ...
	 * try exec without path search.
	 */
	if (find('/', name) || strlen(name) > MAXFILENAME) {
		ret = exec_env(name, fin, fout, ferr, av, env);

	} else if ((path = getpath(env)) == NULL) {
		ret = exec_env(name, fin, fout, ferr, av, env);
		if ((ret == ENOFILE) && strlen(name) <= (sizeof (nbuf) - 6)) {
			strcatl(nbuf, "/bin/", name, (char *)NULL);
			ret = exec_env(nbuf, fin, fout, ferr, av, env);
			if (ret == EMISSDIR)
				ret = ENOFILE;
		}
	} else {
		int	nlen = strlen(name);

		for (;;) {
			np = nbuf;
			/*
			 * JOS always uses ':' as PATH Environ separator
			 */
			while (*path != ':' && *path != '\0' &&
				np < &nbuf[MAXPATHNAME-nlen-2]) {

				*np++ = *path++;
			}
			*np = '\0';
			if (*nbuf == '\0')
				strcatl(nbuf, name, (char *)NULL);
			else
				strcatl(nbuf, nbuf, "/", name, (char *)NULL);
			ret = exec_env(nbuf, fin, fout, ferr, av, env);
			if (ret == EMISSDIR)
				ret = ENOFILE;
			if (ret != ENOFILE || *path == '\0')
				break;
			path++;
		}
	}
	return (ret);

#else	/* JOS */

	if (fin != 0) {
		f[0] = fcntl(0, F_GETFD, 0);
		o[0] = dup(0);
		fcntl(o[0], F_SETFD, 1);
		fdcopy(fin, 0);
	}
	if (fout != 1) {
		f[1] = fcntl(1, F_GETFD, 0);
		o[1] = dup(1);
		fcntl(o[1], F_SETFD, 1);
		fdcopy(fout, 1);
	}
	if (ferr != 2) {
		f[2] = fcntl(2, F_GETFD, 0);
		o[2] = dup(2);
		fcntl(o[2], F_SETFD, 1);
		fdcopy(ferr, 2);
	}
	if (fin != 0)
		close(fin);
	if (fout != 1)
		close(fout);
	if (ferr != 2)
		close(ferr);

	/*
	 * If name contains a pathdelimiter ('/' on unix)
	 * or name is too long ...
	 * try exec without path search.
	 */
#ifdef	FOUND_MAXFILENAME
	if (strchr(name, '/') || strlen(name) > (unsigned)MAXFILENAME) {
#else
	if (strchr(name, '/')) {
#endif
		ret = execve(name, av, env);

	} else if ((path = getpath(env)) == NULL) {
		ret = execve(name, av, env);
		if ((geterrno() == ENOENT) && strlen(name) <= (sizeof (nbuf) - 6)) {
			strcatl(nbuf, "/bin/", name, (char *)NULL);
			ret = execve(nbuf, av, env);
		}
	} else {
		int	nlen = strlen(name);

		for (;;) {
			np = nbuf;
			while (*path != PATH_ENV_DELIM && *path != '\0' &&
				np < &nbuf[MAXPATHNAME-nlen-2]) {

				*np++ = *path++;
			}
			*np = '\0';
			if (*nbuf == '\0')
				strcatl(nbuf, name, (char *)NULL);
			else
				strcatl(nbuf, nbuf, "/", name, (char *)NULL);
			ret = execve(nbuf, av, env);
			if (geterrno() != ENOENT || *path == '\0')
				break;
			path++;
		}
	}
	errsav = geterrno();
			/* reestablish old files */
	if (ferr != 2) {
		fdmove(2, ferr);
		fdmove(o[2], 2);
		if (f[2] == 0)
			fcntl(2, F_SETFD, 0);
	}
	if (fout != 1) {
		fdmove(1, fout);
		fdmove(o[1], 1);
		if (f[1] == 0)
			fcntl(1, F_SETFD, 0);
	}
	if (fin != 0) {
		fdmove(0, fin);
		fdmove(o[0], 0);
		if (f[0] == 0)
			fcntl(0, F_SETFD, 0);
	}
	seterrno(errsav);
	return (ret);

#endif	/* JOS */
}

#ifndef	JOS

LOCAL void
fdcopy(fd1, fd2)
	int	fd1;
	int	fd2;
{
	close(fd2);
	fcntl(fd1, F_DUPFD, fd2);
}

LOCAL void
fdmove(fd1, fd2)
	int	fd1;
	int	fd2;
{
	fdcopy(fd1, fd2);
	close(fd1);
}

#endif

/*----------------------------------------------------------------------------
|
|	get PATH from env
|
+----------------------------------------------------------------------------*/

LOCAL const char *
getpath(env)
	char	* const *env;
{
	char * const *p = env;
	const char *p2;

	if (p != NULL) {
		while (*p != NULL) {
			if ((p2 = chkname("PATH", *p)) != NULL)
				return (p2);
			p++;
		}
	}
	return (NULL);
}


/*----------------------------------------------------------------------------
|
| Check if name is in environment.
| Return pointer to value name is found.
|
+----------------------------------------------------------------------------*/

LOCAL const char *
chkname(name, ev)
	const char	*name;
	const char	*ev;
{
	for (;;) {
		if (*name != *ev) {
			if (*ev == '=' && *name == '\0')
				return (++ev);
			return (NULL);
		}
		name++;
		ev++;
	}
}
