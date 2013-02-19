
PREFIX = /usr/local

INSTALL = install
DEBUG_CFLAGS = -O0 -ggdb -DDEBUG
RELEASE_CFLAGS = -O2 -s -DNDEBUG
CFLAGS += -W -Wall -Werror -ansi -pedantic ${RELEASE_CFLAGS}
CPPFLAGS += -I/usr/local/include/postgresql
LDFLAGS += -L/usr/local/lib/postgresql -L/usr/local/lib
