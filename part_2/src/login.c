/* login.c */
#include <gtk/gtk.h>
#include <stdbool.h>
#include "../include/database.h"
#include "../include/login.h"

/* Declare instance of login page */
LoginPage login_page;

/* Handle click on login button */
void on_login_button_clicked(GtkButton *button, gpointer data) {

    const char *username = gtk_entry_get_text(GTK_ENTRY(login_page.entry_username));
    const char *password = gtk_entry_get_text(GTK_ENTRY(login_page.entry_password));
    GtkWidget *stack = login_page.stack;
    GtkWidget *error_label = login_page.error_label;

    /* Check if user exists */
    if (check_user(username)) {
        /* Check if the password is correct */
        if (check_password(username, password)) {
	    /* display correct child if success */
            gtk_stack_set_visible_child_name(GTK_STACK(stack), "main");
            gtk_label_set_text(GTK_LABEL(error_label), "");  // Clear error message
        } else {
            /* Handle incorrect password */
            gtk_label_set_text(GTK_LABEL(error_label), "Incorrect password");
        }
    } else {
        /* User not exists */
        gtk_label_set_text(GTK_LABEL(error_label), "User does not exist");
    }
}

/* Go to register page at click */
void create_user_page_button_clicked(GtkButton *button, gpointer data)
{
	GtkWidget *stack = GTK_WIDGET(data);
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "create_user");
}

/* Initialize the login page */
void login_init(GtkWidget *stack) {

	/* Init the LoginPage structure */
	login_page.stack = stack;

	/* Create a Box container */
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	/* Create a Grid */
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 15);

	/* Add widgets */
	GtkWidget *label = gtk_label_new("Login Page");
	GtkWidget *label_username = gtk_label_new("Username:");
	login_page.entry_username = gtk_entry_new();
	GtkWidget *label_password = gtk_label_new("Password:");
	login_page.entry_password = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(login_page.entry_password), FALSE); /* Hide the password */
	login_page.error_label = gtk_label_new("");
	
	/* Login button connected to callback function */
	GtkWidget *login_button = gtk_button_new_with_label("Login");
	g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), stack);
	
	/* Go to register  page */
	GtkWidget *create_user_button = gtk_button_new_with_label("No account ?");
	g_signal_connect(create_user_button, "clicked", G_CALLBACK(create_user_page_button_clicked), stack);
	
	/* Attach all widgets */
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), label_username, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), login_page.entry_username, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_password, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), login_page.entry_password, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), login_button, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), login_page.error_label, 0, 4, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), create_user_button, 0, 5, 2, 1);
	
	/* Pack the grid and center it */
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
	gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	
	/* Set stack title for this page */
	gtk_stack_add_titled(GTK_STACK(stack), vbox, "login", "Login Page");
}

