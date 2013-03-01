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

#ifndef  CHKPW_PG_CONFIG_H
# define CHKPW_PG_CONFIG_H

# ifndef  CHKPW_PG_CONNECT
#  define CHKPW_PG_CONNECT \
  "dbname='lowh-mail'"
# endif

extern char *conf_pg_connect;

# ifndef  CHKPW_PG_QUERY
#  define CHKPW_PG_QUERY ("SELECT id FROM mailboxes"			\
			  " WHERE username||'@'||domain = $1"		\
			  "   AND password = crypt($2, password) LIMIT 1")
# endif

extern char *conf_pg_query;

# ifndef  CHKPW_PG_CONFDIR /* XXX keep trailing slash */
#  define CHKPW_PG_CONFDIR "/etc/checkpassword_pg/"
# endif

void load_config ();

#endif
