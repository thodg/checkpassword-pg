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

#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <libpq-fe.h>
#include "checkpassword_pg.h"
#include "config.h"


static void run_prog (char * const prog[])
{
  execve (prog[0], prog, NULL);
  syslog (LOG_ERR, "execve failed");
  exit (111);
}


int checkpassword_pg (const char *login,
                      const char *pass,
                      const char *time,
                      char * const prog[])
{
  PGconn        *conn;
  PGresult      *result;
  const char    *params[3];
  int           n;

  conn = PQconnectdb (conf_pg_connect);
  if (!conn || PQstatus(conn) != CONNECTION_OK) {
    syslog (LOG_ERR, "connect failed");
    if (conn)
      PQfinish (conn);
    exit (111);
  }

  params[0] = login;
  params[1] = pass;
  params[2] = time;
  result = PQexecParams (conn, conf_pg_query, 2, NULL, params, NULL, NULL, 0);
  if (PQresultStatus (result) != PGRES_TUPLES_OK) {
    syslog (LOG_ERR, "PQexecParams(\"%s\", \"%s\", \"%s\", \"%s\") failed: %s",
	    conf_pg_query, login, pass, time, PQresultErrorMessage (result));
    PQfinish (conn);
    exit (111);
  }

  n = PQntuples (result);
  PQfinish (conn);

  switch (n) {
  case 0:
    exit (1);
  case 1:
    run_prog (prog);
  default:
    syslog (LOG_WARNING, "result has %i tuples", n);
    exit (111);
  }
  return 0;
}
