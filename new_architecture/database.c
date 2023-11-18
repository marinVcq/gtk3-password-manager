#include "database.h"

int initialize_database(const char *database_name) {
    sqlite3 *db;
    int rc = sqlite3_open(database_name, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    rc = create_tables(db);

    sqlite3_close(db);

    return rc;
}

int create_tables(sqlite3 *db) {
    const char *users_table = "CREATE TABLE IF NOT EXISTS users ("
                              "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "username TEXT NOT NULL,"
                              "email TEXT NOT NULL,"
                              "password TEXT NOT NULL);";

    const char *passwords_table = "CREATE TABLE IF NOT EXISTS passwords ("
                                  "password_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "username TEXT NOT NULL,"
                                  "email TEXT NOT NULL,"
                                  "service_name TEXT NOT NULL,"
                                  "service_link TEXT NOT NULL,"
                                  "password TEXT NOT NULL,"
                                  "creation_date TEXT NOT NULL,"
                                  "update_date TEXT NOT NULL,"
                                  "user_id INTEGER REFERENCES users(user_id) ON DELETE CASCADE);";

    char *errMsg = 0;

    int rc = sqlite3_exec(db, users_table, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error (users table): %s\n", errMsg);
        sqlite3_free(errMsg);
        return rc;
    }

    rc = sqlite3_exec(db, passwords_table, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error (passwords table): %s\n", errMsg);
        sqlite3_free(errMsg);
        return rc;
    }

    return rc;
}

