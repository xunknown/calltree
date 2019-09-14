#ident @(#)rules.inc	1.3 04/01/23 
###########################################################################
# Written 1999 by J. Schilling
###########################################################################
#
# Rules for creating include files (usually found in .../incs/machdir)
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
include		$(SRCROOT)/$(RULESDIR)/rules.obj
###########################################################################

PTARGET=	$(OINCSDIR)/$(TARGET)
PTARGETC=	$(ARCHDIR)/$(TARGETC)

_INSMODEI=	$(_UNIQ)$(INSMODE)
__INSMODEI=	$(_INSMODEI:$(_UNIQ)=$(INSMODEF))
INSMODEI=	$(__INSMODEI:$(_UNIQ)%=%)

all:		$(PTARGETC) $(PTARGET)

$(PTARGETC):	$(OFILES) $(SRCLIBS)
		$(LDCC) -o $@ $(POFILES) $(LDFLAGS) $(LDLIBS)

$(PTARGET):	$(OINCSDIR) $(PTARGETC)
		@echo "	==> GENERATING include file \"$@\""; $(PTARGETC) > $@

###########################################################################
include		$(SRCROOT)/$(RULESDIR)/rules.clr
include		$(SRCROOT)/$(RULESDIR)/rules.ins
include		$(SRCROOT)/$(RULESDIR)/rules.tag
include		$(SRCROOT)/$(RULESDIR)/rules.hlp
include		$(SRCROOT)/$(RULESDIR)/rules.dep
###########################################################################
