#
#  checkpassword-pg  -  checkpassword with postgresql backend
#
#  Copyright 2008-2013 Thomas de Grivel
#
#  Permission to use, copy, modify, and distribute this software for any
#  purpose with or without fee is hereby granted, provided that the above
#  copyright notice and this permission notice appear in all copies.
#
#  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#

.include "conf-openbsd.mk"

LIBS = -lpq

HEADERS = \
	checkpassword_pg.h \
	config.h

SOURCES = \
	checkpassword_pg.c \
	cli.c \
	config.c

DISTFILES = ${HEADERS} ${SOURCES} \
	Makefile conf-linux.mk conf-openbsd.mk

OBJECTS = ${SOURCES:.c=.o}

all: checkpassword-pg

##  install

install: checkpassword-pg
	${INSTALL} -m 0755 checkpassword-pg ${PREFIX}/bin

##  dist

DISTNAME = checkpassword-pg
VERSION = 0.3
DIST = ${DISTNAME}-$(VERSION)
dist: ${DIST}.tar.gz

${DIST}.tar.gz: ${DISTFILES}
	mkdir ${DIST}
	ln ${DISTFILES} ${DIST}
	tar czf ${DIST}.tar.gz.tmp ${DIST}
	rm -rf ${DIST}
	mv ${DIST}.tar.gz.tmp ${DIST}.tar.gz

lowh-dist: ${DIST}.tar.gz
	scp ${DIST}.tar.gz lowh-dist@lowh.net:dist/LowH/${DISTNAME}/

##  clean

CLEANFILES = *.o ${DISTNAME} ${DIST}.tar.gz.tmp ${DIST}
clean:
	rm -rf ${CLEANFILES}

##  build

checkpassword-pg: ${OBJECTS} ${HEADERS} Makefile
	${CC} -o $@ ${CFLAGS} ${LDFLAGS} ${OBJECTS} ${LIBS}

%.o: %.c ${HEADERS} Makefile
	${CC} ${CFLAGS} ${CPPFLAGS} -c $<
