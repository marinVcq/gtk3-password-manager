// myapp.h

#ifndef MYAPP_H
#define MYAPP_H

#include <gtk/gtk.h>
#include <sqlite3.h>

#include "loginwindow.h"
#include "authenticatedwindow.h"

#define MY_APP_TYPE (my_app_get_type())

/* Structure to store database */
typedef struct {
	sqlite3 *db;
}DBManager;


/* Structure to represent user authentication */
typedef struct _AuthState{
	gboolean authenticated;
}AuthState;

/* Structure to represent the MyApp instance */
typedef struct _MyApp {
	GtkApplication parent;
	LoginWindow *login_window;
	AuthenticatedWindow *authenticated_window;
	AuthState auth_state;
	DBManager db_manager;
} MyApp;


/* Create a custom GObject which inherit of GtkApplication method */
G_DECLARE_FINAL_TYPE(MyApp, my_app, MY, APP, GtkApplication);

/* Create an instance of MyApp */
MyApp *my_app_new(void);
void my_app_activate(GApplication *app);
void my_app_startup(GApplication *app);
void on_app_shutdown(MyApp *app, gpointer user_data);

/* Function to initialize database */
void init_database(DBManager *db_manager);

/* Function to close the database */
void close_database(DBManager *db_manager);


#endif // MYAPP_H
