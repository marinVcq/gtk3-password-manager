/* mainwindow.c */
#include <gtk/gtk.h>
#include "../include/mainwindow.h"

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

/* Function to create a box widget for the header row */
GtkWidget *create_header_row() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *username_label = gtk_label_new("Username");
    GtkWidget *email_label = gtk_label_new("Email");
    GtkWidget *service_label = gtk_label_new("Service Name");
    GtkWidget *link_label = gtk_label_new("Service Link");

    gtk_box_pack_start(GTK_BOX(box), username_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), email_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), service_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), link_label, FALSE, FALSE, 0);

    return box;
}

/* Function to create a box widget for displaying a password */
GtkWidget *create_password_box(const PasswordInfo *password) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *username_label = gtk_label_new(password->username);
    GtkWidget *email_label = gtk_label_new(password->email);
    GtkWidget *service_label = gtk_label_new(password->service_name);
    GtkWidget *link_label = gtk_label_new(password->service_link);

    gtk_box_pack_start(GTK_BOX(box), username_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), email_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), service_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), link_label, FALSE, FALSE, 0);

    return box;
}


/* Function to populate the list box with passwords */
void populate_passwords_list(GtkWidget *list_box) {
    // Fetch all passwords from the database
    PasswordInfo *passwords = fetch_all_passwords();

    // Clear existing rows in the list box
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(list_box));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
    
    int result_count = get_result_count();

    // Add each password to the list box
    for (int i = 0; i < result_count; i++) { // Use result_count instead of num_passwords
        GtkWidget *password_box = create_password_box(&passwords[i]);
        gtk_list_box_insert(GTK_LIST_BOX(list_box), password_box, -1);
    }

    // Free the memory allocated for the passwords
    for (int i = 0; i < result_count; i++) {
        free(passwords[i].username);
        free(passwords[i].email);
        free(passwords[i].service_name);
        free(passwords[i].service_link);
        free(passwords[i].password);
        free(passwords[i].creation_date);
        free(passwords[i].update_date);
    }
    free(passwords);
}


/* Initialize the main application page */
void mainwindow_init(GtkWidget *stack) {

	/* TEST */
	printf("mainwindow_init() is called\n");
	
	/* END TEST */

	/* Init the MainPage structure */
	main_page.stack = stack;
	main_page.list_box = gtk_list_box_new();
 		
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	
	// Populate the list box with passwords
    	populate_passwords_list(main_page.list_box);
	
	GtkWidget *logout_button = gtk_button_new_with_label("Logout");
	GtkWidget *add_password_button = gtk_button_new_with_label("Add password");
	
	g_signal_connect(logout_button, "clicked", G_CALLBACK(on_logout_button_clicked), stack);
	g_signal_connect(add_password_button, "clicked", G_CALLBACK(on_add_button_clicked), stack);

	gtk_box_pack_start(GTK_BOX(main_box), gtk_label_new("Welcome to the Main Page!"), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), main_page.list_box, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), add_password_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), logout_button, FALSE, FALSE, 0);
	

	gtk_stack_add_titled(GTK_STACK(stack), main_box, "main", "Main Page");
}

