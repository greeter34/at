
/** @file db.h
 *
 * @brief Utilities to setup and teardown the DB.
 */


#ifndef AT_DB
#define AT_DB

#include <sqlite3.h>
#include <stddef.h>

/** @brief Setup and return an instance of the sqlite db in memory, or
           NULL if any error occurs */
sqlite3 *get_memory_db ();

#endif
