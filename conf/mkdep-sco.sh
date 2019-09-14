#!/bin/sh
#ident "@(#)mkdep-sco.sh	1.5 03/03/05 "
###########################################################################
# Copyright 1999 by J. Schilling
###########################################################################
#
# Create dependency list with SCO's cc
#
###########################################################################
#
# This script will probably not work correctly with a list of C-files
# but as we don't need it with 'smake' or 'gmake' it seems to be sufficient.
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
# You should have received a copy of the GNU General Public License along with
# this program; see the file COPYING.  If not, write to the Free Software
# Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
###########################################################################
FILES=

for i in "$@"; do

	case "$i" in

	-*)	# ignore options
		;;
	*.c)	if [ ! -z "$FILES" ]; then
			FILES="$FILES "
		fi
		# base name from $i
		base=`echo $i | sed -e 's;[^/]*/;;'`
		FILES="$FILES$base"
		;;
	esac
done

OFILES=`echo "$FILES" | sed -e 's;\([^.]*\)\.c;\1.o;g'`

cc -H -E 2>&1 > /dev/null "$@" | grep -hv '^"' | grep -hv '^UX:' | sed -e "s;^;$OFILES: ;"
