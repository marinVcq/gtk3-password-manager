// myapp.c 

#include "../include/myapp.h"
#include "../include/loginwindow.h"
#include "../include/authenticatedwindow.h"

G_DEFINE_TYPE(MyApp, my_app, GTK_TYPE_APPLICATION)

void my_app_activate(GApplication *app) {

/*	AuthState *auth_state = &MY_APP(app)->auth_state;*/
	/* Initialize database */
	close_database(&MY_APP(app)->db_manager);
}

void my_app_startup(GApplication *app){

	g_print("Startup signal received.\n");
	AuthState *auth_state = &MY_APP(app)->auth_state;
	auth_state->authenticated = FALSE;

	G_APPLICATION_CLASS(my_app_parent_class)->startup(app);

	LoginWindow *login_win = login_window_new(MY_APP(app));
	gtk_widget_show_all(GTK_WIDGET(login_win));
	
	/* Initialize database */
	init_database(&MY_APP(app)->db_manager);
}


static void my_app_class_init(MyAppClass *class) {

}

static void my_app_init(MyApp *app) {

	/* Initialize database */
	init_database(&MY_APP(app)->db_manager);
	}

MyApp *my_app_new(void) {
	return g_object_new(MY_APP_TYPE, "application-id", "org.gtk.myapp", NULL);
}

void init_database(DBManager *db_manager) {
    int rc = sqlite3_open("password_manager.db", &db_manager->db);
    if (rc != SQLITE_OK) {
        g_print("Cannot open database: %s\n", sqlite3_errmsg(db_manager->db));
        // Handle error, possibly exit the application
    }

    // Create the tables if they don't exist
    const char *create_users_table = "CREATE TABLE IF NOT EXISTS users ("
                                     "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "username TEXT NOT NULL,"
                                     "email TEXT NOT NULL,"
                                     "password TEXT NOT NULL);";

    const char *create_passwords_table = "CREATE TABLE IF NOT EXISTS passwords ("
                                         "password_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                         "username TEXT NOT NULL,"
                                         "email TEXT NOT NULL,"
                                         "service_name TEXT NOT NULL,"
                                         "service_link TEXT NOT NULL,"
                                         "password TEXT NOT NULL,"
                                         "creation_date TEXT NOT NULL,"
                                         "update_date TEXT NOT NULL,"
                                         "user_id INTEGER REFERENCES users(user_id) ON DELETE CASCADE);";

    rc = sqlite3_exec(db_manager->db, create_users_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        g_print("Cannot create users table: %s\n", sqlite3_errmsg(db_manager->db));
        // Handle error
    }else{
    	g_print("Create 'users' table successfully\n");
    }
    rc = sqlite3_exec(db_manager->db, create_passwords_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        g_print("Cannot create passwords table: %s\n", sqlite3_errmsg(db_manager->db));
        // Handle error
    }else{
    	g_print("Create 'passwords' table successfully\n");
    }
}

void close_database(DBManager *db_manager) {
    sqlite3_close(db_manager->db);
}

