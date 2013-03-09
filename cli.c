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

  cli.c  -  command line interface
  See http://cr.yp.to/checkpwd/ for interface description

*/

#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include "checkpassword_pg.h"
#include "config.h"

/* returns new value of i, or call exit with code 2 on overflow */
static int find_zero (int i, const char *data)
{
  while (i < 512 && data[i])
    i++;
  if (i == 512) {
    syslog (LOG_ERR, "bad input at position %i", i);
    exit (2);
  }
  return i;
}


static void read_data (char *data)
{
  size_t size;
  ssize_t r;

  size = 512;
  while ((r = read(3, data, size)) > 0) {
    size -= r;
    data += r;
  }
  close(3);
  if (r == 0)
    return;
  if (r < 0) {
    syslog (LOG_ERR, "read failed");
    exit (2);
  }
}


int main (int argc, char **argv)
{
  char data[512];
  const char *login;
  const char *pass;
  const char *time;
  int i;

  openlog ("checkpassword-pg", 0, LOG_AUTHPRIV);
  setlogmask(LOG_UPTO(LOG_INFO));

  read_data (data);

  login = data;

  i = find_zero (0, data) + 1;
  pass = data + i;

  i = find_zero (i, data) + 1;
  time = data + i;

  find_zero (i, data);

  if (argc < 2) {
    syslog (LOG_ERR, "no program to run");
    return 2;
  }

  load_config();

  argv[0] = argv[1];
  return checkpassword_pg (login, pass, time, argv);
}
