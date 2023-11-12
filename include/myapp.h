// myapp.h

#ifndef MYAPP_H
#define MYAPP_H

#include <gtk/gtk.h>

#define MY_APP_TYPE (my_app_get_type())

/* Structure to represent use authentication */
typedef struct {
	gboolean authenticated;
	
}AuthState;

/* Create a custom GObject which inherit of GtkApplication method */
G_DECLARE_FINAL_TYPE(MyApp, my_app, MY, APP, GtkApplication);

/* Create an instance of MyApp */
MyApp *my_app_new(void);
void my_app_activate(GApplication *app);
void my_app_startup(GApplication *app);
void on_app_shutdown(MyApp *app, gpointer user_data);


#endif // MYAPP_H
