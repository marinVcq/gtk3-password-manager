/* mainwindow.c */
#include <gtk/gtk.h>
#include "../include/mainwindow.h"

/* Handle click on logout button */
void on_logout_button_clicked(GtkButton *button, gpointer data) {
	
	/* Logout logic here soon */
	GtkWidget *stack = GTK_WIDGET(data);
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "login");
}

/* Initialize the main page */
void mainwindow_init(GtkWidget *stack) {

	/* Create a box container & logout button */
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *logout_button = gtk_button_new_with_label("Logout");
	
	/* Connect button to signal */
	g_signal_connect(logout_button, "clicked", G_CALLBACK(on_logout_button_clicked), stack);
	
	/* Pack widget into box container */
	gtk_box_pack_start(GTK_BOX(main_box), gtk_label_new("Welcome to the Main Page!"), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), logout_button, FALSE, FALSE, 0);

	gtk_stack_add_titled(GTK_STACK(stack), main_box, "main", "Main Page");
}

