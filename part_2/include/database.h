#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int initialize_database(const char *database_name);
int create_tables(sqlite3 *db);
bool check_user(const char *username);
bool check_password(const char *username, const char *password);

#endif // DATABASE_H

