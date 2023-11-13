// loginwindow.c 

#include "../include/myapp.h"
#include "../include/loginwindow.h"
#include "../include/authenticatedwindow.h"

struct _LoginWindow{
	GtkApplicationWindow parent;
};

G_DEFINE_TYPE(LoginWindow, login_window, GTK_TYPE_APPLICATION_WINDOW)

// Signal handler for login button click
void on_login_button_clicked(GtkButton *button, AuthState *auth_state) {
    // Perform authentication logic (for simplicity, just set to authenticated)
    auth_state->authenticated = TRUE;
    g_print("login button clicked!");

    // Get the application instance
    MyApp *my_app = MY_APP(g_application_get_default());

    // Access the login window
    GtkWidget *login_window = GTK_WIDGET(gtk_widget_get_ancestor(GTK_WIDGET(button), GTK_TYPE_APPLICATION_WINDOW));

    // Hide the login window
    gtk_widget_hide(login_window);

    // Show the authenticated window
    gtk_widget_show_all(GTK_WIDGET(my_app->authenticated_window));
}


static void login_window_init(LoginWindow *win) {

	/* Initialization code for the login window */
	gtk_window_set_default_size(GTK_WINDOW(win), 740, 480);

	// Access AuthState from the MyApp instance
	MyApp *app = MY_APP(gtk_window_get_application(GTK_WINDOW(win)));
	AuthState *auth_state = &app->auth_state;

	// Create a vertical box
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(win), vbox);

	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 15);

	GtkWidget *label = gtk_label_new("Welcome to the login page!");
	GtkWidget *label_username = gtk_label_new("Username:");
	GtkWidget *entry_username = gtk_entry_new();
	GtkWidget *label_password = gtk_label_new("Password:");
	GtkWidget *entry_password = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE); /* Hide the password */

	GtkWidget *login_button = gtk_button_new_with_label("Login");
	g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(on_login_button_clicked), &auth_state);

	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), label_username, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_username, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_password, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_password, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), login_button, 1, 3, 1, 1);

	// Pack the grid into the center of the vbox
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

	// Center the grid in the middle of the window
	gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
}

static void login_window_class_init(LoginWindowClass *class){
	
	/* class initialization: by example connect a signal handler to the "destroy" signal */
	GObjectClass *object_class = G_OBJECT_CLASS(class);
	object_class->dispose = on_login_window_dispose;
	
}

void on_login_window_dispose(GObject *object) {
    // Dispose code for the login window
    G_OBJECT_CLASS(login_window_parent_class)->dispose(object);

    // Additional cleanup code if needed
/*    LoginWindow *login_window = LOGIN_WINDOW(object);*/

    // Additional cleanup code specific to the login window
    // For example, disconnect signals, release resources, etc.

}


LoginWindow *login_window_new(MyApp *app){

	// Access AuthState from the MyApp instance
	AuthState *auth_state = &app->auth_state;
	return g_object_new(LOGIN_WINDOW_TYPE, "application", app,NULL);

}









