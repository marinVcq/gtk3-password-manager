/* login.c */
#include <gtk/gtk.h>
#include "../include/login.h"

/* Handle click on login button */
void on_login_button_clicked(GtkButton *button, gpointer data) 
{
	GtkWidget *stack = GTK_WIDGET(data);
	/* Auth logic here soon */
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "main");
}

/* Handle click on create user button */
void create_user_page_button_clicked(GtkButton *button, gpointer data)
{
	GtkWidget *stack = GTK_WIDGET(data);
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "create_user");
}

/* Login page initialization */
void login_init(GtkWidget *stack) {

	/* Create a box container & a grid */
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 15);

	GtkWidget *label = gtk_label_new("This is the login page!");
	
	/* Go to main page at click */
	GtkWidget *login_button = gtk_button_new_with_label("Login");
	g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), stack);
	
	/* Go to create user page at click */
	GtkWidget *create_user_button = gtk_button_new_with_label("No account ?");
	g_signal_connect(create_user_button, "clicked", G_CALLBACK(create_user_page_button_clicked), stack);
	
	/* Attach button and label to grid */
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), login_button, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), create_user_button, 0, 4, 2, 1);
	
	/* pack the grid into the center of the box */
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
	
	/* Center the grid in the middle of the window */
	gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	
	/* Add a stack title to this page */ 
    	gtk_stack_add_titled(GTK_STACK(stack), vbox, "login", "Login Page");
}

