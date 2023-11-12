// loginwindow.c 

#include "../include/loginwindow.h"

struct _LoginWindow{
	GtkApplicationWindow parent;
};

G_DEFINE_TYPE(LoginWindow, login_window, GTK_TYPE_APPLICATION_WINDOW)

static void login_window_init(LoginWindow *win) {

    /* Initialization code for the login window */
    gtk_window_set_default_size(GTK_WINDOW(win), 740, 480);
    
        // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(win), vbox);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 15);
    
    gtk_container_add(GTK_CONTAINER(win), grid);

    GtkWidget *label = gtk_label_new("Welcome to the login page!");
    GtkWidget *label_username = gtk_label_new("Username:");
    GtkWidget *entry_username = gtk_entry_new();
    GtkWidget *label_password = gtk_label_new("Password:");
    GtkWidget *entry_password = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE); /* Hide the password */

    GtkWidget *button_login = gtk_button_new_with_label("Login");
    g_signal_connect(GTK_BUTTON(button_login), "clicked", G_CALLBACK(on_login_button_clicked), win);

    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), label_username, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_username, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_password, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_password, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_login, 1, 3, 1, 1);
    
        // Pack the grid into the center of the vbox
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    // Center the grid in the middle of the window
    gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
}


void on_login_button_clicked(GtkButton *button, LoginWindow *login_win) {
    // Handle login button click event
    // You can implement your authentication logic here
    // For now, let's just print a message
    g_print("Login button clicked!\n");
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
}

LoginWindow *login_window_new(MyApp *app){
	return g_object_new(LOGIN_WINDOW_TYPE, "application", app,NULL);

}









