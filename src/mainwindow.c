/* mainwindow.c */
#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/mainwindow.h"
#include <pango/pangocairo.h>

MainPage main_page;

void restart_application() {
    // Get the current executable path
    char executable_path[1024];
    ssize_t len = readlink("/proc/self/exe", executable_path, sizeof(executable_path) - 1);
    if (len != -1) {
        executable_path[len] = '\0';

        // Execute the application with the same arguments
        execl(executable_path, executable_path, (char *)NULL);
    } else {
        fprintf(stderr, "Error getting executable path\n");
    }
}

/* Callback function: Handle logout button click */
void on_logout_button_clicked(GtkButton *button, gpointer data) {
	 restart_application();
}

/* Function to set the user ID in the MainPage structure */
void set_user_id(int user_id) {
    main_page.user_id = user_id;
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

/* Function to update and populate the lisat box with passwords */
void update_and_populate_passwords_list(GtkWidget *list_box, int user_id) {
	
	/* Fetch paswords from database */
	PasswordInfo *passwords = fetch_all_passwords(user_id);

	if (passwords == NULL) {
	fprintf(stderr, "Error fetching passwords from the database.\n");
	return;
	}

	printf("update and populate passwords function called\n");

	/* Clear existing rows */
	GList *children, *iter;
	children = gtk_container_get_children(GTK_CONTAINER(list_box));
	for (iter = children; iter != NULL; iter = g_list_next(iter)) {
		gtk_widget_destroy(GTK_WIDGET(iter->data));
	}
	g_list_free(children);
	
	/* TEST */
	int result_count = get_result_count(user_id);
	printf("Result count updated: %d  \n", result_count);

	/* Centering box to hold the header row and password boxes */
	GtkWidget *centering_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(centering_box, GTK_ALIGN_CENTER);

	GtkWidget *header_row = create_header_row();
	gtk_box_pack_start(GTK_BOX(centering_box), header_row, FALSE, FALSE, 0);

	for (int i = 0; i < result_count; i++) {
		GtkWidget *password_box = create_password_box(&passwords[i]);
		gtk_box_pack_start(GTK_BOX(centering_box), password_box, FALSE, FALSE, 0);
	}

	/* Insert the centering box into the list box */
	gtk_container_add(GTK_CONTAINER(list_box), centering_box);

	/* Show all widgets after update */
	gtk_widget_show_all(list_box);

	/* Free the memory allocated for the passwords */
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
	printf("end populate function\n");
}



/* Function to populate the list box with passwords */
void populate_passwords_list(GtkWidget *list_box) {
    // Call the update_and_populate_passwords_list function
    update_and_populate_passwords_list(list_box, main_page.user_id);
}



/* Function to create a box widget for the header row */
GtkWidget *create_header_row() {
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    GtkWidget *username_label = gtk_label_new("Username");
    GtkWidget *email_label = gtk_label_new("Email");
    GtkWidget *service_label = gtk_label_new("Service Name");
    GtkWidget *password_label = gtk_label_new("Password");
    GtkWidget *update_label = gtk_label_new("Last Update");

    /* Define a fixed width for labels */
    const int username_label_width = 150;
    const int email_label_width = 225;
    const int service_label_width = 150;
    const int password_label_width = 150;
    const int update_label_width = 150;
    
    /* Assign unique IDs to the labels */
    gtk_widget_set_name(username_label, "username_label");
    gtk_widget_set_name(email_label, "email_label");
    gtk_widget_set_name(service_label, "service_label");
    gtk_widget_set_name(password_label, "password_label");
    gtk_widget_set_name(update_label, "update_label");

    /* Set properties */
    gtk_widget_set_hexpand(username_label, FALSE);
    gtk_widget_set_size_request(username_label, username_label_width, -1);
    gtk_label_set_xalign(GTK_LABEL(username_label), 0.0);

    gtk_widget_set_hexpand(email_label, FALSE);
    gtk_widget_set_size_request(email_label, email_label_width, -1);
    gtk_label_set_xalign(GTK_LABEL(email_label), 0.0);

    gtk_widget_set_hexpand(service_label, FALSE);
    gtk_widget_set_size_request(service_label, service_label_width, -1);
    gtk_label_set_xalign(GTK_LABEL(service_label), 0.0);

    gtk_widget_set_hexpand(password_label, FALSE);
    gtk_widget_set_size_request(password_label, password_label_width, -1);
    gtk_label_set_xalign(GTK_LABEL(password_label), 0.0);
    
    gtk_widget_set_hexpand(update_label, FALSE);
    gtk_widget_set_size_request(update_label, update_label_width, -1);
    gtk_label_set_xalign(GTK_LABEL(update_label), 0.0);
    
    /* Set padding for the header row */
    gtk_container_set_border_width(GTK_CONTAINER(grid), 5); // Adjust the padding as needed


    /* Attach to the grid */
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), email_label, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), service_label, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), update_label, 4, 0, 1, 1);


    return grid;
}

/* Function to create and add the header row to the list box */
void add_header_row(GtkWidget *list_box) {
	GtkWidget *header_row = create_header_row();
	gtk_list_box_insert(GTK_LIST_BOX(list_box), header_row, -1);
}

/* Function to create a box widget for displaying a password */
GtkWidget *create_password_box(const PasswordInfo *password) {
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

	/* Define a fixed width for labels */
	const int username_label_width = 150;
	const int email_label_width = 225;
	const int service_label_width = 150;
	const int password_label_width = 150;
	const int update_label_width = 150;

	GtkWidget *username_label = gtk_label_new(password->username);
	GtkWidget *email_label = gtk_label_new(password->email);
	GtkWidget *service_label = gtk_label_new(password->service_name);
	GtkWidget *password_label = gtk_label_new(password->password);
	GtkWidget *update_label = gtk_label_new(password->update_date);

	// Set properties to make each label take a fixed width
	gtk_widget_set_hexpand(username_label, FALSE);
	gtk_widget_set_size_request(username_label, username_label_width, -1);
	gtk_label_set_xalign(GTK_LABEL(username_label), 0.0); // Align text to the left

	gtk_widget_set_hexpand(email_label, FALSE);
	gtk_widget_set_size_request(email_label, email_label_width, -1);
	gtk_label_set_xalign(GTK_LABEL(email_label), 0.0); // Align text to the left

	gtk_widget_set_hexpand(service_label, FALSE);
	gtk_widget_set_size_request(service_label, service_label_width, -1);
	gtk_label_set_xalign(GTK_LABEL(service_label), 0.0); // Align text to the left

	gtk_widget_set_hexpand(password_label, FALSE);
	gtk_widget_set_size_request(password_label, password_label_width, -1);
	gtk_label_set_xalign(GTK_LABEL(password_label), 0.0); // Align text to the left

	gtk_widget_set_hexpand(update_label, FALSE);
	gtk_widget_set_size_request(update_label, update_label_width, -1);
	gtk_label_set_xalign(GTK_LABEL(update_label), 0.0); // Align text to the left

	// Attach labels to the grid
	gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), email_label, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), service_label, 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), password_label, 3, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), update_label, 4, 0, 1, 1);
	
	
	/* Set padding for the password box */
	gtk_container_set_border_width(GTK_CONTAINER(grid), 5); // Adjust the padding as needed


	return grid;
}


/* Initialize the main application page */
void mainwindow_init(GtkWidget *stack) {

	/* TEST */
	printf("mainwindow_init() is called\n");
	
	/* END TEST */

	/* Init the MainPage structure */
	main_page.stack = stack;
	main_page.list_box = gtk_list_box_new();
	main_page.user_id = -1;

	/* Encapsulate the list box inside a scrolled window */
	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window), 300);
	gtk_container_add(GTK_CONTAINER(scrolled_window), main_page.list_box);
	
	/* Set padding for the scrolled window */
	gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 10); // Adjust the padding as needed


 		
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    	gtk_container_set_border_width(GTK_CONTAINER(main_box), 50);
    	
    	/* Load and apply CSS */
	GtkCssProvider *cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, "./style.css", NULL);
	GtkStyleContext *styleContext = gtk_widget_get_style_context(main_box);
	gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	
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
	if(main_page.user_id != -1){
		populate_passwords_list(main_page.list_box);
	}else{
		printf("User not authenticated\n");
	}


	
	GtkWidget *logout_button = gtk_button_new_with_label("Logout");
	GtkWidget *add_password_button = gtk_button_new_with_label("Add password");
	
	g_signal_connect(logout_button, "clicked", G_CALLBACK(on_logout_button_clicked), NULL);
	g_signal_connect(add_password_button, "clicked", G_CALLBACK(on_add_button_clicked), NULL);


	gtk_box_pack_start(GTK_BOX(main_box), gtk_label_new("Password Manager Version 1.0"), TRUE, TRUE, 0);

	gtk_box_pack_start(GTK_BOX(main_box), search_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), scrolled_window, TRUE, TRUE, 0);
	
	/* Create a box for "Logout" and "Add Password" buttons */
	GtkWidget *logout_add_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_box_pack_end(GTK_BOX(logout_add_box), add_password_button, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(logout_add_box), logout_button, FALSE, FALSE, 0);
	
	/* Pack the "Logout" and "Add Password" box at the end of main_box */
	gtk_box_pack_end(GTK_BOX(main_box), logout_add_box, FALSE, FALSE, 0);


	
/*	gtk_box_pack_start(GTK_BOX(main_box), add_password_button, FALSE, FALSE, 0);*/
/*	gtk_box_pack_start(GTK_BOX(main_box), logout_button, FALSE, FALSE, 0);*/

	gtk_stack_add_titled(GTK_STACK(stack), main_box, "main", "Main Page");
}

