/* main.c */
#include <gtk/gtk.h>
#include "../include/create_user.h"
#include "../include/login.h"
#include "../include/mainwindow.h"

int main(int argc, char *argv[]) {

	/* Initialize GTK */
	gtk_init(&argc, &argv);

	/* Create the main window */
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "GTK Password Manager");
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Create the Stack Object */
	GtkWidget *stack = gtk_stack_new();
	gtk_container_add(GTK_CONTAINER(window), stack);

	/* Initialize each page */ 
	login_init(stack);
	create_user_init(stack);
	mainwindow_init(stack);

	/* Show the main window && start the App */
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

