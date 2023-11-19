
/** @file db.h
 *
 * @brief Utilities to setup and teardown the DB.
 */


#ifndef AT_DB
#define AT_DB

#include <sqlite3.h>
#include <stddef.h>

/** @todo stdio is only included for testing, remove when done */
#include <stdio.h>

/** @brief Setup and return an instance of the sqlite db in memory, or
           NULL if any error occurs */
sqlite3 *get_memory_db ();

/** @brief Setup and initialize a memory database. Return a pointer to the db or NULL if any error occurs */
sqlite3 *setup_memory_db ();
#endif
