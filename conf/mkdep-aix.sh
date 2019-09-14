#!/bin/sh
#ident "@(#)mkdep-aix.sh	1.1 02/10/11 "
###########################################################################
# Copyright 2002 by J. Schilling
###########################################################################
#
# Create dependency list with AIX cc
#
###########################################################################
#
# This script will probably not work correctly with a list of C-files
# but as we don't need it with 'smake' or 'gmake' it seems to be sufficient.
#
# Note that AIX cc will create a file foo.u for every foo.c file. The file
# foo.u is located in the directory where cc is run.
# For this reason, there may be problems of other software likes to create
# foo.u during compilation. Please report problems.
#
###########################################################################
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not, write to
# the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
###########################################################################
FILES=
UFILES=
trap 'rm -f $UFILES ; exit 1' 1 2 15

for i in "$@"; do

	case "$i" in

	-*)	# ignore options
		;;
	*.c)	if [ ! -z "$FILES" ]; then
			FILES="$FILES "
		fi
		b=`basename $i ''`
		FILES="$FILES$b"
		;;
	esac
done

UFILES=`echo "$FILES" | sed -e 's;\([^.]*\)\.c;\1.u;g'`

rm -f $UFILES
cc -M -E > /dev/null "$@"
cat $UFILES
rm -f $UFILES
