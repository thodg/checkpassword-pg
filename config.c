/*

  checkpassword-pg  -  checkpassword with postgresql backend

  Copyright 2008-2013 Thomas de Grivel

  Permission to use, copy, modify, and distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include "config.h"

char *conf_pg_connect = CHKPW_PG_CONNECT;
char *conf_pg_query = CHKPW_PG_QUERY;

static char * readfile (const char *path)
{
  FILE *fp = fopen(path, "r");
  if (fp) {
    char *content = 0;
    size_t n = 0;
    getdelim(&content, &n, 0, fp);
    if (!feof(fp)) {
      syslog (LOG_ERR, "%s: nul byte", path);
      exit(111);
    }
    if (ferror(fp)) {
      syslog(LOG_ERR, "%s: read error", path);
      exit(111);
    }
    return content;
  }
  else if (errno != ENOENT) {
    syslog(LOG_ERR, "%s: %m", path);
    exit(111);
  }
  return 0;
}

static void load_config_file (char *path, size_t n,
			      const char *name, char **conf)
{
  char *c;
  size_t l = strlcpy(path + n, name, PATH_MAX - n);
  if (n + l >= PATH_MAX) {
    syslog(LOG_ERR, "config dir path is too long");
    exit(111);
  }
  c = readfile(path);
  if (c)
    *conf = c;
}

void load_config ()
{
  char path[PATH_MAX];
  size_t n = strlcpy(path, CHKPW_PG_CONFDIR, sizeof(path));
  if (n >= PATH_MAX) {
    syslog(LOG_ERR, "config dir path is too long");
    exit(111);
  }
  load_config_file(path, n, "connect", &conf_pg_connect);
  load_config_file(path, n, "query", &conf_pg_query);
}
