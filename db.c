#include "db.h"

sqlite3
*get_memory_db ()
{
  sqlite3 *db;
  int rc = sqlite3_open(":memory:", &db);

  if (rc != SQLITE_OK)
    {
      sqlite3_close(db);
      return NULL;
    }

  return db;
}
