// myapp.c 

#include "../include/myapp.h"
#include "../include/loginwindow.h"
#include "../include/authenticatedwindow.h"


struct _MyApp {
  GtkApplication parent;
};

G_DEFINE_TYPE(MyApp, my_app, GTK_TYPE_APPLICATION)

void my_app_activate(GApplication *app) {
    // Implement the activation logic here, if needed
    // For now, you can leave it empty or add any specific logic you require
}

void my_app_startup(GApplication *app){

	g_print("Startup signal received.\n");

	G_APPLICATION_CLASS(my_app_parent_class)->startup(app);

	LoginWindow *login_win = login_window_new(MY_APP(app));
	gtk_widget_show_all(GTK_WIDGET(login_win));
}


static void my_app_class_init(MyAppClass *class) {

}

static void my_app_init(MyApp *app) {
  // Initialization code for the application
}

MyApp *my_app_new(void) {
	return g_object_new(MY_APP_TYPE, "application-id", "org.gtk.myapp", NULL);
}

