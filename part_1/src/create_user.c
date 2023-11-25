/* create_user.c */
#include "../include/create_user.h"

/* Handle create user button click */
void on_create_user_button_clicked(GtkButton *button, gpointer data)
{
	/* here form validation and add user into database */ 
	g_print("try to add user\n");
}

/* Create user page initialization */
void create_user_init(GtkWidget *stack) { // Change GtkStack to GtkWidget

	/* Create a box container & a grid */
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 15);
	
	/* Set label and button -- Implement better GUI in Part 2 */
	GtkWidget *label = gtk_label_new("This is the create user page!");
	GtkWidget *create_user_button = gtk_button_new_with_label("Create User");
	
	/* Connect to callback function */
	g_signal_connect(create_user_button, "clicked", G_CALLBACK(on_create_user_button_clicked), stack);
	
	/* Attach button and label to grid */
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), create_user_button, 1, 5, 1, 1);

	/* pack the grid into the center of the box */
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
	gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	
	/* Add a stack title to this page */ 
	gtk_stack_add_titled(GTK_STACK(stack), vbox, "create_user", "Register Page");
}
