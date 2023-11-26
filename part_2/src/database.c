/* database.c */
#include "../include/database.h"

/* Function to initialize database */
int initialize_database() {
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

/* Function to insert password in the database */
bool insert_password(const char *username, const char *email, const char *password,
                     const char *service_name, const char *service_link) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    const char *insert_password_sql = "INSERT INTO passwords (username, email, service_name, service_link, password, creation_date, update_date, user_id) VALUES (?, ?, ?, ?, ?, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, (SELECT user_id FROM users WHERE username = ?));";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, insert_password_sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error (prepare statement): %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    /* Bind parameters */
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, service_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, service_link, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, username, -1, SQLITE_STATIC);

    /* execute the statement */
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error (execution): %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    /* Close database after Finalize */
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
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

	/* Bind parameters */
	sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, password, -1, SQLITE_STATIC);

	/* Execute the statement */
	rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE) {
	fprintf(stderr, "SQL error (execution): %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	return false;
	}

	/* Finalize statement and close database */
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return true;
}

/* Function to check if user exists in the database */
bool check_user(const char *username) {
	sqlite3 *db;
	int rc = sqlite3_open(DATABASE_NAME, &db);

	if (rc != SQLITE_OK) {
	fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	return false;
	}

	const char *check_user_sql = "SELECT 1 FROM users WHERE username = ? LIMIT 1;";
	sqlite3_stmt *stmt;

	rc = sqlite3_prepare_v2(db, check_user_sql, -1, &stmt, 0);

	if (rc != SQLITE_OK) {
	fprintf(stderr, "SQL error (prepare statement): %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	return false;
	}

	/* Bind parameters */
	sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

	/* Execute statement */
	rc = sqlite3_step(stmt);

	bool user_exists = (rc == SQLITE_ROW);

	/* Finalize the statement and close the database */
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return user_exists;
}

/* Function to check if the provided password is correct for a given username */
bool check_password(const char *username, const char *password) {
	sqlite3 *db;
	int rc = sqlite3_open(DATABASE_NAME, &db);

	if (rc != SQLITE_OK) {
	fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	return false;
	}

	const char *check_password_sql = "SELECT 1 FROM users WHERE username = ? AND password = ? LIMIT 1;";
	sqlite3_stmt *stmt;

	rc = sqlite3_prepare_v2(db, check_password_sql, -1, &stmt, 0);

	if (rc != SQLITE_OK) {
	fprintf(stderr, "SQL error (prepare statement): %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	return false;
	}

	/* Bind parameters */
	sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

	/* Execute the statement */
	rc = sqlite3_step(stmt);

	bool password_correct = (rc == SQLITE_ROW);

	/* Finalize the statement and close the database */
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return password_correct;
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
