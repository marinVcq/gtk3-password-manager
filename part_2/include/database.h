#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Database config */
#define DATABASE_NAME "password_manager.db"

int initialize_database();
int create_tables(sqlite3 *db);
bool check_user(const char *username);
bool check_password(const char *username, const char *password);
bool insert_user(const char *username, const char *email, const char *password);
bool insert_password(const char *username, const char *email, const char *password,
                     const char *service_name, const char *service_link);

#endif // DATABASE_H

