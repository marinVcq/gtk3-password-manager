#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* Database config */
#define DATABASE_NAME "password_manager.db"

/* Password structure */
typedef struct {
    int password_id;
    char *username;
    char *email;
    char *service_name;
    char *service_link;
    char *password;
    char *creation_date;
    char *update_date;
    int user_id;
} PasswordInfo;

int initialize_database();
int create_tables(sqlite3 *db);
bool check_user(const char *username);
bool check_password(const char *username, const char *password);
bool insert_user(const char *username, const char *email, const char *password);
bool insert_password(const char *username, const char *email, const char *password,
                     const char *service_name, const char *service_link, int user_id);
PasswordInfo *fetch_all_passwords(int user_id);
int get_result_count(int user_id);
PasswordInfo *fetch_all_passwords_filtered(int user_id, const char *filter);
int get_result_count_filtered(int user_id, const char *filter);


#endif // DATABASE_H

