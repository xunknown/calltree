/* @(#)filewrite.c	1.13 03/06/15 Copyright 1986, 1995-2003 J. Schilling */
/*
 *	Copyright (c) 1986, 1995-2003 J. Schilling
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

#include "io.h"

static	char	_writeerr[]	= "file_write_err";

#ifdef	HAVE_USG_STDIO

EXPORT int
filewrite(f, vbuf, len)
	register FILE	*f;
	void	*vbuf;
	int	len;
{
	register int	n;
	int	cnt;
	char		*buf = vbuf;

	down2(f, _IOWRT, _IORW);

	if (f->_flag & _IONBF) {
		cnt = write(fileno(f), buf, len);
		if (cnt < 0) {
			f->_flag |= _IOERR;
			if (!(my_flag(f) & _IONORAISE))
				raisecond(_writeerr, 0L);
		}
		return (cnt);
	}
	cnt = 0;
	while (len > 0) {
		if (f->_cnt <= 0) {
			if (usg_flsbuf((unsigned char) *buf++, f) == EOF)
				break;
			cnt++;
			if (--len == 0)
				break;
		}
		if ((n = f->_cnt >= len ? len : f->_cnt) > 0) {
			f->_ptr = (unsigned char *)movebytes(buf, f->_ptr, n);
			buf += n;
			f->_cnt -= n;
			cnt += n;
			len -= n;
		}
	}
	if (!ferror(f))
		return (cnt);
	if (!(my_flag(f) & _IONORAISE))
	raisecond(_writeerr, 0L);
	return (-1);
}

#else

EXPORT int
filewrite(f, vbuf, len)
	register FILE	*f;
	void	*vbuf;
	int	len;
{
	int	cnt;
	char		*buf = vbuf;

	down2(f, _IOWRT, _IORW);

	if (my_flag(f) & _IOUNBUF)
		return (write(fileno(f), buf, len));
	cnt = fwrite(buf, 1, len, f);

	if (!ferror(f))
		return (cnt);
	if (!(my_flag(f) & _IONORAISE))
	raisecond(_writeerr, 0L);
	return (-1);
}

#endif	/* HAVE_USG_STDIO */
