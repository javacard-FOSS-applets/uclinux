# Copyright (C) 2000, 2001  Internet Software Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SOFTWARE CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# $Id: Makefile,v 1.3 2005/09/17 21:57:45 mcr Exp $

OPENSWANSRCDIR?=$(shell cd ../..; pwd)
include ${OPENSWANSRCDIR}/Makefile.inc

CINCLUDES =	-I${srcdir}${ISCARCH}/include \
		-I${srcdir}nothreads/include \
		-I. -I./include -I${srcdir}include \
		$(PORTINCLUDE) -I${OPENSWANSRCDIR}/include
CDEFINES = -g -DHAVE_STRERROR ${USERCOMPILE} ${PORTINCLUDE}
# CWARNINGS = -Werror

CFLAGS+=${CINCLUDES} ${CDEFINES} ${CWARNINGS}

VERSION="@(\#) openswan-hacking-9.3-for-osw2"
LIBINTERFACE=2
LIBREVISION=0
LIBAGE=1
LIB=libisc
VPATH+=${srcdir}nls 
VPATH+=${srcdir}${ISCARCH}

OBJS =		mem.o buffer.o inet_pton.o assertions.o error.o 
OBJS += 	lib.o region.o lex.o hex.o string.o result.o base64.o
OBJS += 	msgcat.o parseint.o stdio.o stdtime.o ondestroy.o
OBJS += 	task.o event.o errno2result.o strerror.o 
OBJS +=		rwlock.o random.o inet_aton.o inet_ntop.o

SRCS =		mem.c buffer.c inet_pton.c assertions.c error.c 
SRCS += 	lib.c region.c lex.c hex.c string.c result.c base64.c
SRCS +=		msgcat.c parseint.c stdio.c stdtime.c ondestroy.c
SRCS +=		task.c event.c errno2result.c strerror.c 
SRCS +=		rwlock.c random.c inet_aton.c inet_ntop.c

programs all: ${LIB}.a

version.o: version.c
	${LIBTOOL} ${CC} ${ALL_CFLAGS} \
		-DVERSION=\"${VERSION}\" \
		-DLIBINTERFACE=${LIBINTERFACE} \
		-DLIBREVISION=${LIBREVISION} \
		-DLIBAGE=${LIBAGE} \
		${CINCLUDES} ${CDEFINES} ${CWARNINGS} \
		-c ${srcdir}version.c

${LIB}.a: ${OBJS} version.o
	${AR} ${ARFLAGS} $@ ${OBJS} version.o

timestamp: ${LIB}.a
	touch timestamp

clean distclean mostlyclean realclean cleanall spotless::
	rm -f ${LIB}.a ${LIB}.la timestamp $(OBJS) version.o

install checkprograms check install_file_list:
	@true

TAGS: ${SRCS}
	etags ${SRCS}
