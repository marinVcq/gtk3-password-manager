#include <gtk/gtk.h>
#include "login.h"

void on_login_button_clicked(GtkButton *button, gpointer data) 
{
	GtkWidget *stack = GTK_WIDGET(data);

	/* Auth logic here soon */
	
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "main");
}

void create_user_page_button_clicked(GtkButton *button, gpointer data)
{
	GtkWidget *stack = GTK_WIDGET(data);
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "create_user");
}

void login_init(GtkWidget *stack) { // Change GtkStack to GtkWidget

	// Create a vertical box
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 15);

	GtkWidget *label = gtk_label_new("Welcome to the login page!");
	GtkWidget *label_username = gtk_label_new("Username:");
	GtkWidget *entry_username = gtk_entry_new();
	GtkWidget *label_password = gtk_label_new("Password:");
	GtkWidget *entry_password = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE); /* Hide the password */
	
	/* Login button */
	GtkWidget *login_button = gtk_button_new_with_label("Login");
	g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), stack);
	
	/* Go create user page */
	GtkWidget *create_user_button = gtk_button_new_with_label("No account ?");
	g_signal_connect(create_user_button, "clicked", G_CALLBACK(create_user_page_button_clicked), stack);
	

	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), label_username, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_username, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_password, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_password, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), login_button, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), create_user_button, 0, 4, 2, 1);
	
	// Pack the grid into the center of the vbox
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

	// Center the grid in the middle of the window
	gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);

    gtk_stack_add_titled(GTK_STACK(stack), vbox, "login", "Login Page");
}

