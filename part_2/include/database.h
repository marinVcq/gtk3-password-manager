#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Database config */
#define DATABASE_NAME "password_manager.db"

/* Password structure */
typedef struct {
    int password_id;
    const char *username;
    const char *email;
    const char *service_name;
    const char *service_link;
    const char *password;
    const char *creation_date;
    const char *update_date;
    int user_id;
} PasswordInfo;

int initialize_database();
int create_tables(sqlite3 *db);
bool check_user(const char *username);
bool check_password(const char *username, const char *password);
bool insert_user(const char *username, const char *email, const char *password);
bool insert_password(const char *username, const char *email, const char *password,
                     const char *service_name, const char *service_link);
PasswordInfo* fetch_passwords(int* num_passwords);

#endif // DATABASE_H

