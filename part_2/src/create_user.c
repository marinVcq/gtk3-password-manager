/* create_user.c */
#include <stdbool.h>
#include "../include/create_user.h"
#include "../include/database.h"

void on_create_user_button_clicked(GtkButton *button, gpointer data)
{
	/* here form validation and add it into db */ 
	g_print("try to add user\n");
}

void create_user_init(GtkWidget *stack) { // Change GtkStack to GtkWidget

	// Create a vertical box
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 15);

	GtkWidget *label = gtk_label_new("Welcome to the Register page!");
	GtkWidget *label_email = gtk_label_new("Email:");
	GtkWidget *entry_email = gtk_entry_new();
	GtkWidget *label_username = gtk_label_new("Username:");
	GtkWidget *entry_username = gtk_entry_new();
	GtkWidget *label_password = gtk_label_new("Password:");
	GtkWidget *entry_password = gtk_entry_new();
	GtkWidget *label_password_check = gtk_label_new("Password check:");
	GtkWidget *entry_password_check = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE); /* Hide the password */

	GtkWidget *create_user_button = gtk_button_new_with_label("Create User");
	g_signal_connect(create_user_button, "clicked", G_CALLBACK(on_create_user_button_clicked), stack);

	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), label_email, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_email, 1, 1, 1, 1);
	
	
	gtk_grid_attach(GTK_GRID(grid), label_username, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_username, 1, 2, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_password, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_password, 1, 3, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_password_check, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_password_check, 1, 4, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), create_user_button, 1, 5, 1, 1);

	// Pack the grid into the center of the vbox
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

	// Center the grid in the middle of the window
	gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);

    gtk_stack_add_titled(GTK_STACK(stack), vbox, "create_user", "Register Page");
}
