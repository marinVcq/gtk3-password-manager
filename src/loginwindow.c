// loginwindow.c 

#include "../include/loginwindow.h"

struct _LoginWindow{
	GtkApplicationWindow parent;
};

G_DEFINE_TYPE(LoginWindow, login_window, GTK_TYPE_APPLICATION_WINDOW)

static void login_window_init(LoginWindow *win){
	
	/* Initialization code for the login window */
	
	gtk_window_set_default_size(GTK_WINDOW(win), 740,480);
	GtkWidget *label = gtk_label_new("Welcome to the login page!");
	gtk_container_add(GTK_CONTAINER(win), label);


	
}

static void login_window_class_init(LoginWindowClass *class){
	
	/* class initialization: by example connect a signal handler to the "destroy" signal */
	GObjectClass *object_class = G_OBJECT_CLASS(class);
	object_class->dispose = on_login_window_dispose;
	
}

static void on_login_window_dispose(GObject *object) {
    // Dispose code for the login window
    G_OBJECT_CLASS(login_window_parent_class)->dispose(object);

    // Additional cleanup code if needed
}

LoginWindow *login_window_new(MyApp *app){
	return g_object_new(LOGIN_WINDOW_TYPE, "application", app,NULL);

}









