#include "db.h"

sqlite3
*get_memory_db ()
{
  sqlite3 *db;
  /** @todo revert back to ":memory:" once done testing */
  int rc = sqlite3_open("./memory.db", &db);

  if (rc != SQLITE_OK)
    {
      sqlite3_close(db);
      return NULL;
    }

  return db;
}

sqlite3
*setup_memory_db ()
{
  sqlite3 *db = get_memory_db ();
  if (!db) return NULL;

  sqlite3_stmt *stmt;
  int rc;
  char *query;

  /* Setup the `locations' table */
  query = "CREATE TABLE locations (x INTEGER NOT NULL, y INTEGER NOT NULL, PRIMARY KEY(x,y))";
  rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
  if (rc != SQLITE_OK)
    {
      return NULL;
    }
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  return db;
}
