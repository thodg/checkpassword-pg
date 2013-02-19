
PREFIX = /usr/local

CC = gcc
INSTALL = install
DEBUG_CFLAGS = -O0 -ggdb
RELEASE_CFLAGS = -O2 -g
CFLAGS += -W -Wall -Werror -ansi -pedantic ${DEBUG_CFLAGS}
CPPFLAGS += -I${prefix}/include/postgresql83
LDFLAGS += -L${prefix}/lib/postgresql83
