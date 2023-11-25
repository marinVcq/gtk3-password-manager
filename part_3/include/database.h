#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int initialize_database(const char *database_name);
int create_tables(sqlite3 *db);

#endif // DATABASE_H

