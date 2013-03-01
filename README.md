checkpassword-pg
================

Replacement for Dan J. Bernstein's checkpassword with PostgreSQL
backend.

`checkpassword-pg` connects to a PostgreSQL database and executes one
query to check if the provided username and password are valid.


Compile time, aka once and for all
----------------------------------

Default connection informations can be set by defining
`CHKPW_PG_CONNECTION`.

The default SQL query can be set by defining `CHKPW_PG_QUERY`.


Run time, [insert your favourite runtime pun here]
--------------------------------------------------

Connexion informations are read from `/etc/checkpassword-pg/connection`
if the file exists, otherwise default connection informations are used.

The SQL query is read from `/etc/checkpassword-pg/connection`
if the file exists, otherwise the default SQL query is used.


License
-------

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
