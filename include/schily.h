/* @(#)schily.h	1.51 03/07/10 Copyright 1985-2002 J. Schilling */
/*
 *	Definitions for libschily
 *
 *	This file should be included past:
 *
 *	mconfig.h / config.h
 *	standard.h
 *	stdio.h
 *	stdlib.h	(better use stdxlib.h)
 *	unistd.h	(better use unixstd.h) needed LARGEFILE support
 *	string.h
 *	sys/types.h
 *
 *	If you need stdio.h, you must include it before schily.h
 *
 *	NOTE: If you need ctype.h and did not include stdio.h you need to
 *	include ctype.h past schily.h as OpenBSD does not follow POSIX and
 *	defines EOF in ctype.h
 *
 *	Copyright (c) 1985-2002 J. Schilling
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

#ifndef _SCHILY_H
#define	_SCHILY_H

#ifndef _STANDARD_H
#include <standard.h>
#endif
#ifndef _CCOMDEFS_H
#include <ccomdefs.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#if	defined(_INCL_SYS_TYPES_H) || defined(off_t)
#	ifndef	FOUND_OFF_T
#	define	FOUND_OFF_T
#	endif
#endif
#if	defined(_INCL_SYS_TYPES_H) || defined(size_t)
#	ifndef	FOUND_SIZE_T
#	define	FOUND_SIZE_T
#	endif
#endif

#ifdef	__never_def__
/*
 * It turns out that we cannot use the folloginw definition because there are
 * some platforms that do not behave application friendly. These are mainly
 * BSD-4.4 based systems (which #undef a definition when size_t is available.
 * We actually removed this code because of a problem with QNX Neutrino.
 * For this reason, it is important not to include <sys/types.h> directly but
 * via the Schily SING include files so we know whether it has been included
 * before we come here.
 */
#if	defined(_SIZE_T)	|| defined(_T_SIZE_)	|| defined(_T_SIZE) || \
	defined(__SIZE_T)	|| defined(_SIZE_T_)	|| \
	defined(_GCC_SIZE_T)	|| defined(_SIZET_)	|| \
	defined(__sys_stdtypes_h) || defined(___int_size_t_h) || defined(size_t)

#ifndef	FOUND_SIZE_T
#	define	FOUND_SIZE_T	/* We already included a size_t definition */
#endif
#endif
#endif	/* __never_def__ */

#if	defined(HAVE_LARGEFILES)
#	define	_fcons		_fcons64
#	define	fdup		fdup64
#	define	fileluopen	fileluopen64
#	define	fileopen	fileopen64
#	define	filepos		filepos64
#	define	filereopen	filereopen64
#	define	fileseek	fileseek64
#	define	filesize	filesize64
#	define	filestat	filestat64
#	define	_openfd		_openfd64
#endif

#ifdef	EOF	/* stdio.h has been included */
extern	int	_cvmod __PR((const char *, int *, int *));
extern	FILE	*_fcons __PR((FILE *, int, int));
extern	FILE	*fdup __PR((FILE *));
extern	int	fdown __PR((FILE *));
extern	int	fexecl __PR((const char *, FILE *, FILE *, FILE *,
							const char *, ...));
extern	int	fexecle __PR((const char *, FILE *, FILE *, FILE *,
							const char *, ...));
		/* 6th arg not const, fexecv forces av[ac] = NULL */
extern	int	fexecv __PR((const char *, FILE *, FILE *, FILE *, int,
							char **));
extern	int	fexecve_calltree __PR((const char *, FILE *, FILE *, FILE *,
					char * const *, char * const *));
extern	int	fspawnv __PR((FILE *, FILE *, FILE *, int, char * const *));
extern	int	fspawnl __PR((FILE *, FILE *, FILE *,
					const char *, const char *, ...));
extern	int	fspawnv_nowait __PR((FILE *, FILE *, FILE *,
					const char *, int, char *const*));
extern	int	fgetline_calltree __PR((FILE *, char *, int));
extern	int	fgetstr __PR((FILE *, char *, int));
extern	void	file_raise __PR((FILE *, int));
extern	int	fileclose __PR((FILE *));
extern	FILE	*fileluopen __PR((int, const char *));
extern	FILE	*fileopen __PR((const char *, const char *));
#ifdef	FOUND_OFF_T
extern	off_t	filepos __PR((FILE *));
#endif
extern	int	fileread __PR((FILE *, void *, int));
extern	int	ffileread __PR((FILE *, void *, int));
extern	FILE	*filereopen __PR((const char *, const char *, FILE *));
#ifdef	FOUND_OFF_T
extern	int	fileseek __PR((FILE *, off_t));
extern	off_t	filesize __PR((FILE *));
#endif
#ifdef	S_IFMT
extern	int	filestat __PR((FILE *, struct stat *));
#endif
extern	int	filewrite __PR((FILE *, void *, int));
extern	int	ffilewrite __PR((FILE *, void *, int));
extern	int	flush __PR((void));
extern	int	fpipe __PR((FILE **));
/*extern	int	fprintf __PR((FILE *, const char *, ...)) __printflike__(2, 3);*/
extern	int	getbroken __PR((FILE *, char *, char, char **, int));
extern	int	ofindline __PR((FILE *, char, const char *, int,
							char **, int));
extern	int	peekc __PR((FILE *));

#ifdef	__never_def__
/*
 * We cannot define this or we may get into problems with DOS based systems.
 */
extern	int	spawnv __PR((FILE *, FILE *, FILE *, int, char * const *));
extern	int	spawnl __PR((FILE *, FILE *, FILE *,
					const char *, const char *, ...));
extern	int	spawnv_nowait __PR((FILE *, FILE *, FILE *,
					const char *, int, char *const*));
#endif	/* __never_def__m */
#endif	/* EOF */

extern	int	_niread __PR((int, void *, int));
extern	int	_niwrite __PR((int, void *, int));
extern	int	_nixread __PR((int, void *, int));
extern	int	_nixwrite __PR((int, void *, int));
extern	int	_openfd __PR((const char *, int));
extern	int	on_comerr __PR((void (*fun)(int, void *), void *arg));
/*PRINTFLIKE1*/
extern	void	comerr __PR((const char *, ...)) __printflike__(1, 2);
/*PRINTFLIKE2*/
extern	void	comerrno __PR((int, const char *, ...)) __printflike__(2, 3);
/*PRINTFLIKE1*/
extern	int	errmsg __PR((const char *, ...)) __printflike__(1, 2);
/*PRINTFLIKE2*/
extern	int	errmsgno __PR((int, const char *, ...)) __printflike__(2, 3);
#ifdef	FOUND_SIZE_T
/*PRINTFLIKE3*/
extern	int	serrmsg __PR((char *, size_t, const char *, ...)) __printflike__(3, 4);
/*PRINTFLIKE4*/
extern	int	serrmsgno __PR((int, char *, size_t, const char *, ...)) __printflike__(4, 5);
#endif
extern	void	comexit	__PR((int));
extern	char	*errmsgstr __PR((int));
/*PRINTFLIKE1*/
extern	int	error __PR((const char *, ...)) __printflike__(1, 2);
extern	char	*fillbytes __PR((void *, int, char));
extern	char	*findbytes __PR((const void *, int, char));
extern	int	findline __PR((const char *, char, const char *,
							int, char **, int));
extern	int	getline_calltree __PR((char *, int));
extern	int	getstr __PR((char *, int));
extern	int	breakline __PR((char *, char, char **, int));
extern	int	getallargs __PR((int *, char * const**, const char *, ...));
extern	int	getargs __PR((int *, char * const**, const char *, ...));
extern	int	getfiles __PR((int *, char * const**, const char *));
extern	char	*astoi __PR((const char *, int *));
extern	char	*astol __PR((const char *, long *));
extern	char	*astolb __PR((const char *, long *, int base));
#ifdef	_UTYPES_H
extern	char	*astoll __PR((const char *, Llong *));
extern	char	*astollb __PR((const char *, Llong *, int base));
#endif

/*extern	void	handlecond __PR((const char *, SIGBLK *, int(*)(const char *, long, long), long));*/
/*extern	void	unhandlecond __PR((SIGBLK *));*/

extern	int		patcompile __PR((const unsigned char *, int, int *));
extern	unsigned char	*patmatch __PR((const unsigned char *, const int *,
					const unsigned char *, int, int, int, int[]));
extern	unsigned char	*patlmatch __PR((const unsigned char *, const int *,
					const unsigned char *, int, int, int, int[]));

/*extern	int	printf __PR((const char *, ...)) __printflike__(1, 2);*/
extern	char	*movebytes __PR((const void *, void *, int));

extern	void	save_args __PR((int, char **));
extern	int	saved_ac __PR((void));
extern	char	**saved_av __PR((void));
extern	char	*saved_av0 __PR((void));
#ifndef	seterrno
extern	int	seterrno __PR((int));
#endif
extern	void	set_progname __PR((const char *));
extern	char	*get_progname __PR((void));

extern	void	setfp __PR((void * const *));
extern	int	wait_chld __PR((int));		/* for fspawnv_nowait() */
extern	int	geterrno __PR((void));
extern	void	raisecond __PR((const char *, long));
#ifdef	FOUND_SIZE_T
/*
 * We currently cannot define this here because there IXIX has a definition
 * than violates the standard.
 */
#ifndef	HAVE_SNPRINTF
/*PRINTFLIKE3*/
extern	int	snprintf __PR((char *, size_t, const char *, ...)) __printflike__(3, 4);
#endif
#endif
/*extern	int	sprintf __PR((char *, const char *, ...)); ist woanders falsch deklariert !!!*/
extern	char	*strcatl __PR((char *, ...));
extern	int	streql __PR((const char *, const char *));
#ifdef	va_arg
extern	int	format __PR((void (*)(char, long), long, const char *, va_list));
#else
extern	int	format __PR((void (*)(char, long), long, const char *, void *));
#endif

extern	int	ftoes __PR((char *, double, int, int));
extern	int	ftofs __PR((char *, double, int, int));

#ifdef	EOF	/* stdio.h has been included */
/*PRINTFLIKE2*/
extern	int	js_fprintf	__PR((FILE *, const char *, ...)) __printflike__(2, 3);
/*PRINTFLIKE1*/
extern	int	js_printf	__PR((const char *, ...)) __printflike__(1, 2);
#ifdef	FOUND_SIZE_T
/*PRINTFLIKE3*/
extern	int	js_snprintf	__PR((char *, size_t, const char *, ...)) __printflike__(3, 4);
#endif
/*PRINTFLIKE2*/
extern	int	js_sprintf	__PR((char *, const char *, ...)) __printflike__(2, 3);
#endif	/* EOF */

extern	void	swabbytes	__PR((void *, int));
extern	char	**getmainfp	__PR((void));
extern	char	**getavp	__PR((void));
extern	char	*getav0		__PR((void));
extern	void	**getfp		__PR((void));
extern	int	flush_reg_windows __PR((int));
extern	int	cmpbytes	__PR((const void *, const void *, int));
extern	int	cmpnullbytes	__PR((const void *, int));

#ifdef	nonono
#if	defined(HAVE_LARGEFILES)
/*
 * To allow this, we need to figure out how to do autoconfiguration for off64_t
 */
extern	FILE	*_fcons64	__PR((FILE *, int, int));
extern	FILE	*fdup64		__PR((FILE *));
extern	FILE	*fileluopen64	__PR((int, const char *));
extern	FILE	*fileopen64	__PR((const char *, const char *));
#ifdef	FOUND_OFF_T
extern	off64_t	filepos64	__PR((FILE *));
#endif
extern	FILE	*filereopen64	__PR((const char *, const char *, FILE *));
#ifdef	FOUND_OFF_T
extern	int	fileseek64	__PR((FILE *, off64_t));
extern	off64_t	filesize64	__PR((FILE *));
#endif
#ifdef	S_IFMT
extern	int	filestat64	__PR((FILE *, struct stat *));
#endif
extern	int	_openfd64	__PR((const char *, int));
#endif
#endif

#ifdef	__cplusplus
}
#endif

#if defined(_JOS) || defined(JOS)
#	ifndef	_JOS_IO_H
#	include <jos_io.h>
#	endif
#endif

#endif	/* _SCHILY_H */
