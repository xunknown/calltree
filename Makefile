#ident %W% %E% %Q%
###########################################################################
# Sample makefile for the source root
###########################################################################
SRCROOT=	.
DIRNAME=	SRCROOT
RULESDIR=	RULES
include		$(SRCROOT)/$(RULESDIR)/rules.top
###########################################################################

include		$(SRCROOT)/TARGETS/Targetdirs

###########################################################################
# Due to a bug in SunPRO make we need special rules for the root makefile
#
include		$(SRCROOT)/$(RULESDIR)/rules.rdi
###########################################################################
