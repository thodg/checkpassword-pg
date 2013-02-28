
.include "conf-openbsd.mk"

LIBS = -lpq

HEADERS = \
	checkpassword_pg.h \
	config.h

SOURCES = \
	checkpassword_pg.c \
	cli.c

DISTFILES = ${HEADERS} ${SOURCES} \
	Makefile conf-linux.mk conf-openbsd.mk

OBJECTS = ${SOURCES:.c=.o}

all: checkpassword-pg

##  install

install: checkpassword-pg
	${INSTALL} -m 0755 checkpassword-pg ${PREFIX}/bin

##  dist

DISTNAME = checkpassword-pg
VERSION = 0.2
DIST = ${DISTNAME}-$(VERSION)
dist: ${DIST}.tar.gz

${DIST}.tar.gz: ${DISTFILES}
	mkdir ${DIST}
	ln ${DISTFILES} ${DIST}
	tar czf ${DIST}.tar.gz.tmp ${DIST}
	rm -rf ${DIST}
	mv ${DIST}.tar.gz.tmp ${DIST}.tar.gz

lowh-dist: ${DIST}.tar.gz
	rsync -tv --ignore-existing ${DIST}.tar.gz lowh-dist@lowh.net:dist/LowH/${DISTNAME}/

##  clean

CLEANFILES = *.o ${DISTNAME} ${DIST}.tar.gz.tmp ${DIST}
clean:
	rm -rf ${CLEANFILES}

##  build

checkpassword-pg: ${OBJECTS} ${HEADERS} Makefile
	${CC} -o $@ ${CFLAGS} ${LDFLAGS} ${OBJECTS} ${LIBS}

%.o: %.c ${HEADERS} Makefile
	${CC} ${CFLAGS} ${CPPFLAGS} -c $<
