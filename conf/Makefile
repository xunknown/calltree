#ident @(#)Makefile	1.2 04/01/23 
###########################################################################
# Written 1998 by J. Schilling
###########################################################################
# Makefile for local dynamic configuration
###########################################################################
#@@C@@
###########################################################################
SRCROOT=	..
RULESDIR=	RULES
include		$(SRCROOT)/$(RULESDIR)/rules.top
###########################################################################

CONFFILES=	Inull rules.cnf xconfig.h

PCONFFILES=	$(CONFFILES:%=$(OINCSDIR)/%)

all: config

clobber:
	$(RM_F) $(PCONFFILES)

distclean:
		$(RM) $(RM_RF)		$(PCONFFILES) \
						.vedtmp* *.bak OBJ/* \
						$(SRCROOT)/libs/* $(SRCROOT)/incs/*

###########################################################################
# Now done in rules.top
#include		$(SRCROOT)/$(RULESDIR)/rules.cnf
###########################################################################

OTHERTARGETS=	clean install ibins depend rmdep \
		TAGS tags rmtarget relink

$(OTHERTARGETS):
	@echo "$@: nothing to make"

