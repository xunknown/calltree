#ident %W% %E% %Q%
###########################################################################
SRCROOT=	..
RULESDIR=	RULES
include		$(SRCROOT)/$(RULESDIR)/rules.top
###########################################################################

INSDIR=		include
TARGET=		avoffset.h
TARGETC=	avoffset
CPPOPTS +=	-DUSE_SCANSTACK
CPPOPTS +=	-D__OPRINTF__
CFILES=		avoffset.c

###########################################################################
include		$(SRCROOT)/$(RULESDIR)/rules.inc
###########################################################################
