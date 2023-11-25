/* database.c */
#include "../include/database.h"

/* Function to initialize database */
int initialize_database(const char *database_name) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    rc = create_tables(db);

    sqlite3_close(db);

    return rc;
}

/* Function to insert new user in database */
bool insert_user(const char *username, const char *email, const char *password) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    const char *insert_user_sql = "INSERT INTO users (username, email, password) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, insert_user_sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error (prepare statement): %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    // Bind parameters to the prepared statement
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, password, -1, SQLITE_STATIC);

    // Execute the statement
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error (execution): %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}
/* Function to check if user exist in database */
bool check_user(const char *username){
	/* Not implemented yet */
	return true;
}

/* Function to check if password is correct */
bool check_password(const char *username, const char *password){
	/* Not implemented yet */
	return true;
}

/* Function to create table users and passwords */
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

