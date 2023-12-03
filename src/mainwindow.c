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

/* Callback function: Handle search button click */
void on_search_button_clicked(GtkButton *button, gpointer data) {
	/* Not implemented yet */ 
}

/* Callback function: Handle export button click */
void on_export_button_clicked(GtkButton *button, gpointer data) {
	/* Not implemented yet */ 
}


/* Function to update the list box with passwords */
void update_passwords_list(GtkWidget *list_box) {
    // Fetch all passwords from the database
    PasswordInfo *passwords = fetch_all_passwords();
    printf("update passwords function called\n");

    // Clear existing rows in the list box
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(list_box));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    int result_count = get_result_count();
    printf("Result count updated: %d  \n", result_count);
    
    // Add the header row to the list box
    GtkWidget *header_row = create_header_row();
    gtk_container_add(GTK_CONTAINER(list_box), header_row);

    // Add each password to the list box
    for (int i = 0; i < result_count; i++) {
        GtkWidget *password_box = create_password_box(&passwords[i]);
        gtk_container_add(GTK_CONTAINER(list_box), password_box);
        gtk_widget_show_all(password_box);
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

/* Function to create and add the header row to the list box */
void add_header_row(GtkWidget *list_box) {
    GtkWidget *header_row = create_header_row();
    gtk_list_box_insert(GTK_LIST_BOX(list_box), header_row, -1);
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
    
    // Add the header row to the list box
    add_header_row(list_box);

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
	
	/* Encapsulate the list box inside a scrolled window */
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 300);
	gtk_container_add(GTK_CONTAINER(scrolled_window), main_page.list_box);

 		
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
	/* Add the search box at the top */
	GtkWidget *search_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	GtkWidget *search_label = gtk_label_new("Service Name: ");
	GtkWidget *search_entry = gtk_entry_new();
	GtkWidget *search_button = gtk_button_new_with_label("Search");
	GtkWidget *export_button = gtk_button_new_with_label("Export");
	
	gtk_box_pack_end(GTK_BOX(search_box), export_button, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(search_box), search_button, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(search_box), search_entry, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(search_box), search_label, FALSE, FALSE, 0);

	/* Connect the search and export button click signal to a callback function */
	g_signal_connect(search_button, "clicked", G_CALLBACK(on_search_button_clicked), NULL);
	g_signal_connect(export_button, "clicked", G_CALLBACK(on_export_button_clicked), NULL);
	
	/* Populate the list box with passwords */
    	populate_passwords_list(main_page.list_box);
	
	GtkWidget *logout_button = gtk_button_new_with_label("Logout");
	GtkWidget *add_password_button = gtk_button_new_with_label("Add password");
	
	g_signal_connect(logout_button, "clicked", G_CALLBACK(on_logout_button_clicked), NULL);
	g_signal_connect(add_password_button, "clicked", G_CALLBACK(on_add_button_clicked), NULL);


	gtk_box_pack_start(GTK_BOX(main_box), gtk_label_new("Password Manager Version 1.0"), TRUE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(main_box), search_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), scrolled_window, TRUE, TRUE, 0);
	
	gtk_box_pack_start(GTK_BOX(main_box), add_password_button, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), logout_button, FALSE, FALSE, 0);

	

	gtk_stack_add_titled(GTK_STACK(stack), main_box, "main", "Main Page");
}

