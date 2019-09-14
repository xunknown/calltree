#!/bin/sh
#ident "@(#)mkdep-hpux.sh	1.1 02/10/10 "
###########################################################################
# Copyright 2002 by J. Schilling
###########################################################################
#
# Create dependency list with the HP-UX bundled cc
#
###########################################################################
#
# This script will probably not work correctly with a list of C-files
# but as we don't need it with 'smake' or 'gmake' it seems to be sufficient.
#
# Due to a design bug in the compiler interface we cannot tell the compiler
# to output the list on stdout, -Wp,-M- does not work. As the default
# output is on stderr and the output is even completely confused with
# error messages and warnings, we cannot just grep away the warnings
# like we do on SCO unix.
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

trap 'rm -fr /tmp/cpp-m.$$ ; exit 1' 1 2 15

cc -Wp,-M/tmp/cpp-m.$$ -E > /dev/null "$@" 

cat /tmp/cpp-m.$$

rm -f /tmp/cpp-m.$$
