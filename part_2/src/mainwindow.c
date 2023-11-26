/* mainwindow.c */
#include <gtk/gtk.h>
#include "../include/mainwindow.h"
#include "../include/database.h"

MainPage main_page;

/* Callback function: Handle logout button click */
void on_logout_button_clicked(GtkButton *button, gpointer data) {
	GtkWidget *stack = main_page.stack;
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "login");
}

/* Callback function: Handle add password button click */
void on_add_button_clicked(GtkButton *button, gpointer data) {
	GtkWidget *stack = main_page.stack;
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "add_password");
}

/* Test function to get all passwords */
void display_passwords(PasswordInfo *passwords, int num_passwords) {
    for (int i = 0; i < num_passwords; i++) {
        printf("Password ID: %d\n", passwords[i].password_id);
        printf("Username: %s\n", passwords[i].username);
        printf("Email: %s\n", passwords[i].email);
        printf("Service Name: %s\n", passwords[i].service_name);
        printf("Service Link: %s\n", passwords[i].service_link);
        printf("Password: %s\n", passwords[i].password);
        printf("Creation Date: %s\n", passwords[i].creation_date);
        printf("Update Date: %s\n", passwords[i].update_date);
        printf("User ID: %d\n", passwords[i].user_id);
        printf("------------------------\n");
    }
}

/* Initialize the main application page */
void mainwindow_init(GtkWidget *stack) {

	/* Init the MainPage structure */
	main_page.stack = stack;
	int num_passwords;
    	PasswordInfo *passwords = fetch_passwords(&num_passwords);
	
	if (passwords) {
		// Display passwords
		display_passwords(passwords, num_passwords);

		// Free the allocated memory
		free(passwords);
	} else {
		fprintf(stderr, "Failed to fetch passwords\n");
	}

	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	
	GtkWidget *logout_button = gtk_button_new_with_label("Logout");
	GtkWidget *add_password_button = gtk_button_new_with_label("Add password");
	
	g_signal_connect(logout_button, "clicked", G_CALLBACK(on_logout_button_clicked), stack);
	g_signal_connect(add_password_button, "clicked", G_CALLBACK(on_add_button_clicked), stack);

	gtk_box_pack_start(GTK_BOX(main_box), gtk_label_new("Welcome to the Main Page!"), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), add_password_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), logout_button, FALSE, FALSE, 0);

	gtk_stack_add_titled(GTK_STACK(stack), main_box, "main", "Main Page");
}

