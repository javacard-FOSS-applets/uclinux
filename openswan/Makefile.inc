# Openswan pathnames and other master configuration
# Copyright (C) 2001, 2002  Henry Spencer.
# Copyright (C) 2003-2006   Xelerance Corporation
# 
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
#
# TODO: Some creative ifeq ($(BUILDENV,xxx) to automatically determine
# where we are building on and disable things (eg KLIPS on OSX)

-include ${OPENSWANSRCDIR}/Makefile.inc.local


# Variables in this file with names starting with INC_ are not for use
# by Makefiles which include it; they are subject to change without warning.
#
# "Final" and "finally" refer to where the files will end up on the
# running IPsec system, as opposed to where they get installed by our
# Makefiles.  (The two are different for cross-compiles and the like,
# where our Makefiles are not the end of the installation process.)
# Paths with FINAL in their names are the only ones that the installed
# software itself depends on.  (Very few things should know about the
# FINAL paths; think twice and consult Henry before making something new
# depend on them.)  All other paths are install targets.
# See also DESTDIR, below.



### boilerplate, do not change
SHELL=/bin/sh

.PHONY:	programs checkprograms clean

### install pathnames

# DESTDIR can be used to supply a prefix to all install targets.
# (Note that "final" pathnames, signifying where files will eventually
# reside rather than where install puts them, are exempt from this.)
# The prefixing is done in this file, so as to have central control over
# it; DESTDIR itself should never appear in any other Makefile.
DESTDIR?=

# "local" part of tree, used in building other pathnames
INC_USRLOCAL=/usr/local

# PUBDIR is where the "ipsec" command goes; beware, many things define PATH
# settings which are assumed to include it (or at least, to include *some*
# copy of the "ipsec" command).
PUBDIR=$(DESTDIR)$(INC_USRLOCAL)/sbin

# BINDIR is where sub-commands get put, FINALBINDIR is where the "ipsec"
# command will look for them when it is run. Also called LIBEXECDIR.
FINALLIBEXECDIR?=$(INC_USRLOCAL)/libexec/ipsec
LIBEXECDIR=$(DESTDIR)$(FINALBINDIR)

FINALBINDIR=${FINALLIBEXECDIR}
BINDIR=${LIBEXECDIR}


# SBINDIR is where the user interface command goes.
FINALSBINDIR?=$(INC_USRLOCAL)/sbin
SBINDIR=$(DESTDIR)$(FINALSBINDIR)

# libdir is where utility files go
FINALLIBDIR?=$(INC_USRLOCAL)/lib/ipsec
LIBDIR=$(DESTDIR)$(FINALLIBDIR)


# where the appropriate manpage tree is located
# location within INC_USRLOCAL
INC_MANDIR=man
# the full pathname
MANTREE=$(DESTDIR)$(INC_USRLOCAL)/$(INC_MANDIR)
# all relevant subdirectories of MANTREE
MANPLACES=man3 man5 man8

# where configuration files go
FINALCONFFILE?=/etc/ipsec.conf
CONFFILE=$(DESTDIR)$(FINALCONFFILE)

FINALCONFDIR?=/etc
CONFDIR=$(DESTDIR)$(FINALCONFDIR)

FINALCONFDDIR?=${FINALCONFDIR}/ipsec.d
CONFDDIR=$(DESTDIR)$(FINALCONFDDIR)

# sample configuration files go into
INC_DOCDIR?=share/doc
FINALEXAMPLECONFDIR=${INC_USRLOCAL}/${INC_DOCDIR}/openswan
EXAMPLECONFDIR=${DESTDIR}${FINALEXAMPLECONFDIR}

FINALDOCDIR?=${INC_USRLOCAL}/${INC_DOCDIR}/openswan
DOCDIR=${DESTDIR}${FINALDOCDIR}

# where per-conn pluto logs go
FINALVARDIR?=/var
VARDIR?=${DESTDIR}${FINALVARDIR}
FINALLOGDIR?=${FINALVARDIR}/log
LOGDIR?=${DESTDIR}${FINALLOGDIR}


# An attempt is made to automatically figure out where boot/shutdown scripts 
# will finally go:  the first directory in INC_RCDIRS which exists gets them.
# If none of those exists (or INC_RCDIRS is empty), INC_RCDEFAULT gets them.
# With a non-null DESTDIR, INC_RCDEFAULT will be used unless one of the
# INC_RCDIRS directories has been pre-created under DESTDIR.
INC_RCDIRS=/etc/rc.d/init.d /etc/rc.d /etc/init.d /sbin/init.d
INC_RCDEFAULT=/etc/rc.d/init.d

# RCDIR is where boot/shutdown scripts go; FINALRCDIR is where they think
# will finally be (so utils/Makefile can create a symlink in BINDIR to the
# place where the boot/shutdown script will finally be, rather than the
# place where it is installed).
FINALRCDIR=$(shell for d in $(INC_RCDIRS) ; \
		do if test -d $(DESTDIR)/$$d ; \
		then echo $$d ; exit 0 ; \
		fi ; done ; echo $(INC_RCDEFAULT) )
RCDIR=$(DESTDIR)$(FINALRCDIR)



### kernel pathnames

# Kernel location:  where patches are inserted, where kernel builds are done.

# this is a hack using the wildcard to look for existence of a file/dir
ifneq ($(wildcard /usr/src/linux-2.6),)
KERNELSRC?=/usr/src/linux-2.6
else
ifneq ($(wildcard /usr/src/linux-2.4),)
KERNELSRC?=/usr/src/linux-2.4
else
KERNELSRC?=/usr/src/linux
endif
endif

# where kernel configuration outputs are located
KCFILE=$(KERNELSRC)/.config
ACFILE=$(KERNELSRC)/include/linux/autoconf.h
VERFILE=$(KERNELSRC)/include/linux/version.h

# where KLIPS kernel module is install
OSMOD_DESTDIR?=net/ipsec

# What command to use to load the modules. openwrt does not have modprobe
MODPROBE?=modprobe -q

### misc installation stuff

# what program to use when installing things
INSTALL=install

# flags to the install program, for programs, manpages, and config files
# -b has install make backups (n.b., unlinks original), --suffix controls
# how backup names are composed.
# Note that the install procedures will never overwrite an existing config
# file, which is why -b is not specified for them.
INSTBINFLAGS=-b --suffix=.old
INSTSUIDFLAGS=--mode=u+rxs,g+rx,o+rx --group=root -b --suffix=.old
INSTMANFLAGS=
INSTCONFFLAGS=
# For OSX use
#INSTBINFLAGS=-b -B .old
#INSTSUIDFLAGS=--mode=u+rxs,g+rx,o+rx --group=root -b -B .old

# flags for bison, overrode in packages/default/foo
BISONOSFLAGS=


### misc configuration, included here in hopes that other files will not
### have to be changed for common customizations.

# extra compile flags, for userland and kernel stuff, e.g. -g for debug info
# you can add to this in the defaults file using +=
USERCOMPILE?=-g ${WERROR} ${PORTDEFINE}
#USERCOMPILE?=-g -O3 ${WERROR} 
KLIPSCOMPILE=-O3 -DCONFIG_KLIPS_ALG
# for AMD64 use 
#USERCOMPILE?=-g -O3 -m64
#KLIPSCOMPILE=-O3 -m64 -mno-red-zone

PORTINCLUDE?=

# command used to link/copy KLIPS into kernel source tree
# There are good reasons why this is "ln -s"; only people like distribution
# builders should ever change it.
KLIPSLINK=ln -s -f

# extra options for use in kernel build
KERNMAKEOPTS=

# kernel Makefile targets to be done before build
# Can be overridden if you are *sure* your kernel doesn't need them.  (2.2.xx
# and later reportedly do not.)
KERNDEP=dep
KERNCLEAN=clean

# kernel make name:  zImage for 2.0.xx, bzImage for 2.2.xx and later, and
# boot on non-x86s (what ever happened to standards?)
INC_B=$(shell test -d $(DIRIN22) && echo b)
KERNEL=$(shell if expr " `uname -m`" : ' i.86' >/dev/null ; \
	then echo $(INC_B)zImage ; \
	else echo boot ; \
	fi)

# look for XMLTO command
XMLTO?=$(shell which xmlto|grep /)

#
# default number of bits for ipsec newhostkey
#
RSAKEYBITS:=2192

# temporary directory to be used when building RPMs, and where to put the
# resulting RPM tree
RPMKERNDIR := $(shell echo `pwd`/tmp.rpmkernel)
RPMTMPDIR := $(shell echo `pwd`/tmp.rpmbuild)
RPMDEST := $(shell echo `pwd`/rpms)

# Newer versions of RPM do not permit building of packages with the "rpm" 
# command. For RedHat systems with older version of RPM, use:
# RPMBUILD=rpm
# instead.
RPMBUILD=rpmbuild

### paths to resources on the host system
#
# Set this to a RedHat kernel-sources RPM. This normally extracts into
# /usr/src/linux-2.4, but you might have extracted it elsewhere with
# rpm2cpio.
# Note: there is no kernel-source rpm anymore for Fedora. Either run
# rpmbuild -bp on the kernel src.rpm and grab the tree from 
# /usr/src/redhat/BUILD/ or use something like the example below using the
# module directory.
# note: there is now a kernel-devel rpm.
#RH_KERNELSRC?=/usr/src/linux-2.4
RH_KERNELSRC?=/lib/modules/2.6.9-1.681_FC3/build

#RH_KERNELSRC=/c2/kernel/rh/linux-2.4.9-13


## build environment variations
##

#
# USE_ variables determine if features are compiled into Openswan.
#       these let you turn on/off specific features
# HAVE_ variables let you tell Openswan what system related libraries
#       you may or maynot have

#Support for NSS crypto library
USE_LIBNSS?=false

# LWRES is the lightweight resolver, part of BIND9
# We test with LWRES, but ship with it off, as it requires
# additional headers not present on most systems.
# Note you need a locally running bind9 nameserver with lwres{} enabled
# to use this, or have the "lwres" package installed and running.
# This only affects conns that use DNS for keys in lookups.
USE_LWRES?=true

# Do a new lookup every time a connection is (re)started. This works better
# on hosts with some dyndns service, since DPD will cause a new dns lookup,
# but it could be a potential security issue if receiving spoofed dns.
USE_DYNAMICDNS?=false

# Do we want all the configuration files like ipsec.conf and ipsec.secrets
# and any certificates to be in a single directory defined by 
# FINALCONFDDIR?
USE_SINGLE_CONF_DIR?=false

# whether or not to include ipsec policy code into pluto.
# false for now, since it is still experimental.
USE_IPSECPOLICY?=true

# Build ikeping (a utility for testing IKE daemons) in the distribution
USE_IKEPING?=true

# Build support for KEY RR 
# this will become false in the future, as all OE sites transition to
# using TXT instead of KEY records.  See references to 'Flag Day'
USE_KEYRR?=true

# Build support for Linux 2.4 and 2.6 KLIPS kernel level IPsec support
# for pluto
USE_KLIPS?=true

# KLIPS needs PFKEYv2, but sometimes we want PFKEY without KLIPS
USE_PFKEYv2?=true

# Build support for 2.6 KLIPS/MAST variation in pluto
USE_MAST?=true

# MAST is generally a prerequisite for SAREF support in applications
USE_SAREF_KERNEL=false

# Build support for Linux NETKEY (XFRM) kernel level IPsec support for
# pluto (aka "native", "kame")
USE_NETKEY?=true

# Whether or not to use iproute2 based commands.
# On Kernel 2.0, and early 2.2 systems you may need to either install the
# iproute2 package, or set this to false. Required for USE_NETKEY.
USE_IPROUTE2?=true

# include support for BSD/KAME IPsec in pluto (on *BSD)
USE_BSDKAME?=false

# Build support for sending Openswan Vendor IDs
USE_VENDORID?=true

# Build aggressive mode authentication system code - both Server and Client.
# This is off by default, since aggressive mode leads to denial of service
# attacks.
USE_AGGRESSIVE?=true

# Build XAUTH authentication system code - both Server and Client.
# This is off by default, since XAUTH is tricky, and you can get into 
# security trouble unless you do additional configuration.
USE_XAUTH?=true

# When doing XAUTH, include PAM support as well, requires HAVE_THREADS be
# true as well
USE_XAUTHPAM?=false

# whether to support NAT Traversal (aka NAT-T)
USE_NAT_TRAVERSAL?=true

# where to support NAT-T in transport mode (needed for Win2K NAT-T Interop)
USE_NAT_TRAVERSAL_TRANSPORT_MODE?=true

# Include LDAP support (currently used for fetching CRLs)
USE_LDAP?=false

# Include libcurl support (currently used for fetching CRLs)
USE_LIBCURL?=false

# Include Smartcard support (disabled by default, as most users don't
# have the required hardware and drivers/software installed)
USE_SMARTCARD?=false

# should opportunistic encryption be turned on by default?
# Enabled during testing, but probably turned off in shipping versions.
USE_OE?=true
ifeq ($(USE_OE),false)
# warning: examples subdirectory is statically defined here
OE_FLAG=\#Disable Opportunistic Encryption\\ninclude ${FINALCONFDDIR}/examples/no_oe.conf
else
endif

# should we include all manner of known to be broken/weak?
# use this only if you are building some kind of a testing
# device. Normal use does not need any of this.
USE_WEAKSTUFF?=false

# Build algorithms that don't even encrypt (also must set WEAKSTUFF)
# unless you are doing negative testing, turning this on is foolish.
USE_NOCRYPTO?=false

# should we include additional (strong) algorithms?  It adds a measureable
# amount of code space to pluto, and many of the algorithms have not had
# the same scrutiny that AES and 3DES have received, but offers possibilities 
# of switching away from AES/3DES quickly. 
USE_EXTRACRYPTO?=true

# Do we want to limit the number of ipsec connections artificially
USE_IPSEC_CONNECTION_LIMIT?=false
IPSEC_CONNECTION_LIMIT?=250

# Do we have pthreads available?  Only yes if you need it for XAUTH+PAM,
# or if you need it for CRL fetching.
# 
HAVE_THREADS?=false

# Do we have an external stats daemon we can push state changes to?
# Currently hardcoded to /bin/statsd
HAVE_STATSD?=false

# Do we have Openssl libraries available for BIGNUM support?
# Required of HAVE_OCF support
HAVE_OPENSSL?=false

# Do we have OCF available?
HAVE_OCF?=false

# Do we assume that the /bin/sh is BASH?
# if so, then internationalization code is retained in the shell scripts
USE_BASH?=true

# Whether or not to include TaProoM (TCL Pluto Mix) into pluto.
# you need at least swig 1.3.24, as well as tcl libraries and includes
USE_TAPROOM?=false

# Use dmalloc. Requires -DLEAK_DETECTIVE to be set in programs/pluto/Makefile
USE_DMALLOC?=false

NONINTCONFIG=oldconfig

# Should we build with object directories?
# (not really a code option, but a build option)
# by default we will start using object directories.
ifeq ($(USE_OBJDIR),)
USE_OBJDIR?=true
endif

# supply kernel-configuration ARCH defaults
ifeq ($(ARCH),)
ARCH := $(shell uname -m)
endif
# always sanitize $(ARCH)
ARCH := $(shell echo $(ARCH) | sed -e s/i.86/i386/ -e s/sun4u/sparc64/ -e s/arm.*/arm/ -e s/sa110/arm/ -e 's/ //g')

ifeq ($(OSDEP),)
OSDEP:=$(shell uname -s | tr 'A-Z' 'a-z')
endif

-include ${OPENSWANSRCDIR}/Makefile.ver
IPSECVERSION:=${IPSECBASEVERSION}$(shell ${OPENSWANSRCDIR}/packaging/utils/setlocalversion ${OPENSWANSRCDIR})
export IPSECVERSION

# include OSDEP/ARCH specific makefiles, if any.
# OSDEP=linux,bsd,cygwin,darwin
# 
# but, BUILDENV could be mingw32-linux, darwin, or mingw32, etc..
ifeq ($(BUILDENV),)
BUILDENV=$(shell uname -s | tr 'A-Z' 'a-z' | sed -e 's/\(.*\)-.*/\1/')
endif
export BUILDENV
export OSDEP
include ${OPENSWANSRCDIR}/packaging/defaults/${BUILDENV}
-include ${OPENSWANSRCDIR}/packaging/defaults/${BUILDENV}.${ARCH}

# On MAC OSX , we have to use YACC and not BISON. And use different backup
# file suffix.
ifeq ($(BUILDENV),"darwin")
USE_YACC?=true
INSTBINFLAGS=-b -B .old
INSTSUIDFLAGS=--mode=u+rxs,g+rx,o+rx --group=root -b -B .old
endif

ifeq ($(USE_OBJDIR),true)
OBJDIR=OBJ.${BUILDENV}.${ARCH}
OBJDIRTOP=${OPENSWANSRCDIR}/${OBJDIR}
endif

# where to place the object files which are built 
OBJDIR?=.
OBJDIRTOP?=${OPENSWANSRCDIR}

### paths within the source tree

KLIPSINC=${OPENSWANSRCDIR}/linux/include
KLIPSSRCDIR=${OPENSWANSRCDIR}/linux/net/ipsec
#KLIPSSRCDIR=/mara1/git/klips/net/ipsec

LIBOPENSWANDIR=${OPENSWANSRCDIR}/lib/libopenswan
OPENSWANLIB=${OBJDIRTOP}/lib/libopenswan/libopenswan.a
PLUTOLIB=${OBJDIRTOP}/lib/libpluto/libpluto.a
OSWLOGLIB=${OBJDIRTOP}/lib/libopenswan/liboswlog.a

LWRESDIR=${OPENSWANSRCDIR}/lib/liblwres
LIBLWRES=${OBJDIRTOP}/lib/liblwres/liblwres.a
LIBDNS=${OBJDIRTOP}/lib/libdns/libdns.a
LIBISC=${OBJDIRTOP}/lib/libisc/libisc.a
LIBBSDPFKEY=${OBJDIRTOP}/lib/libbsdpfkey/libbsdpfkey.a
ISCARCH?=unix
ISCHOSTARCH?=unix

LIBDESSRCDIR=${OPENSWANSRCDIR}/linux/crypto/ciphers/des
LIBDESLITE:=${OBJDIRTOP}/lib/libcrypto/libdes/libdes.a
LIBOSWCRYPTO=${OBJDIRTOP}/lib/libcrypto/liboswcrypto/liboswcrypto.a
LIBAES=${OBJDIRTOP}/lib/libcrypto/libaes/libaes.a
LIBMD5=${OBJDIRTOP}/lib/libcrypto/libmd5/libmd5.a
LIBMD2=${OBJDIRTOP}/lib/libcrypto/libmd2/libmd2.a
LIBSHA1=${OBJDIRTOP}/lib/libcrypto/libsha1/libsha1.a
LIBBLOWFISH=${OBJDIRTOP}/lib/libcrypto/libblowfish/libblowfish.a
LIBTWOFISH=${OBJDIRTOP}/lib/libcrypto/libtwofish/libtwofish.a
LIBSERPENT=${OBJDIRTOP}/lib/libcrypto/libserpent/libserpent.a
LIBSHA2=${OBJDIRTOP}/lib/libcrypto/libsha2/libsha2.a
CRYPTOLIBS=${LIBAES} ${LIBSHA1} ${LIBMD5} ${LIBMD2} ${LIBDESLITE}

ifeq ($(USE_EXTRACRYPTO),true)
CRYPTOLIBS+=${LIBSHA2} ${LIBSERPENT} ${LIBTWOFISH} ${LIBBLOWFISH}
endif

CRYPTOLIBS += ${LIBOSWCRYPTO}
ifeq ($(HAVE_OCF),true)
CRYPTOLIBS += -lcrypto
endif

LIBPOLICYDIR=${OPENSWANSRCDIR}/linux/lib/libipsecpolicy
POLICYLIB=${OBJDIRTOP}/lib/libipsecpolicy/libipsecpolicy.a

WHACKLIB=${OBJDIRTOP}/lib/libwhack/libwhack.a
IPSECCONFLIB=${OBJDIRTOP}/lib/libipsecconf/libipsecconf.a

# export everything so that scripts can use them.
export LIBOPENSWANDIR OPENSWANSRCDIR ARCH PORTINCLUDE 
export LIBOPENSWANDIR OPENSWANLIB OSWLOGLIB PLUTOLIB LWRESDIR LIBLWRES LIBDNS
export LIBISC ISCARCH ISCHOSTARCH LIBDESSRCDIR LIBDESLITE LIBAES
export LIBMD5 LIBMD2 LIBSHA1 LIBBLOWFISH LIBTWOFISH LIBSERPENT
export LIBSHA2 CRYPTOLIBS LIBPOLICYDIR POLICYLIB WHACKLIB IPSECCONFLIB
export LIBOSWCRYPTO

#KERNELBUILDMFLAGS=--debug=biv V=1 

# for emacs
#
# Local Variables: ;;;
# mode: makefile ;;;
# End Variables: ;;;
#
