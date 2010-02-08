
#define CHKPW_PG_CONNINFO \
  "host='127.0.0.1' port='5432' dbname='courier' user='courier' password='changeme'"


#define CHKPW_PG_QUERY \
  "SELECT id FROM passwd WHERE id=$1 AND clear=$2 LIMIT 1"
