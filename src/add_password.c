/* add_password.c */
#include <stdbool.h>
#include "../include/add_password.h"
#include "../include/database.h"
#include "../include/mainwindow.h"

/* Declare instance of add password page */
AddPasswordPage add_password_page;

/* Handle click on add password button */
void on_add_password_button_clicked(GtkButton *button, gpointer data)
{
	const char *username = gtk_entry_get_text(GTK_ENTRY(add_password_page.entry_username));
	const char *email = gtk_entry_get_text(GTK_ENTRY(add_password_page.entry_email));
	const char *password = gtk_entry_get_text(GTK_ENTRY(add_password_page.entry_password));
	const char *password_check = gtk_entry_get_text(GTK_ENTRY(add_password_page.entry_password_check));
	const char *service_name = gtk_entry_get_text(GTK_ENTRY(add_password_page.entry_service_name));
	const char *service_link = gtk_entry_get_text(GTK_ENTRY(add_password_page.entry_service_link));
	GtkWidget *stack = add_password_page.stack;
	GtkWidget *error_label = add_password_page.error_label;
	
	/* Perform a basic form validation */
	if(strlen(username) == 0 ||strlen(email) == 0||strlen(password) == 0||strlen(password_check) == 0){
		gtk_label_set_text(GTK_LABEL(error_label), "All fields must be filled");
		return;
	}
	
	/* Check passwords */
	if(strcmp(password, password_check) != 0){
		gtk_label_set_text(GTK_LABEL(error_label), "Passwords do not match");
		return;
	}
	
	/* Insert password */
	if (insert_password(username, email, password, service_name, service_link)) {
		
		/* Handle success */ 
		g_print("Add password to database\n");
		
		// Update the password list
		update_passwords_list(main_page.list_box);
		

		/* Go to main page & clear error message */
		gtk_stack_set_visible_child_name(GTK_STACK(stack), "main");
		gtk_label_set_text(GTK_LABEL(error_label), "");

	}else{
		/* Handle error */
		gtk_label_set_text(GTK_LABEL(error_label), "Fail to insert password");
	}
}

/* 
    const char *passwords_table = "CREATE TABLE IF NOT EXISTS passwords ("
                                  "password_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "username TEXT NOT NULL,"
                                  "email TEXT NOT NULL,"
                                  "service_name TEXT NOT NULL,"
                                  "service_link TEXT NOT NULL,"
                                  "password TEXT NOT NULL,"
                                  "creation_date TEXT NOT NULL,"
                                  "update_date TEXT NOT NULL,"
                                  "user_id INTEGER REFERENCES users(user_id) ON DELETE CASCADE);";


*/

/* Initialization of add password page */
void add_password_init(GtkWidget *stack) { // Change GtkStack to GtkWidget

	/* Init the AddPasswordPage structure */
	add_password_page.stack = stack;

	/* Create a box container */
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	/* Create a grid */
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 15);

	/* Create or initialize all widgets */
	GtkWidget *label = gtk_label_new("Add password to database");
	
	GtkWidget *label_email = gtk_label_new("Email:");
	add_password_page.entry_email = gtk_entry_new();
	
	GtkWidget *label_username = gtk_label_new("Username:");
	add_password_page.entry_username = gtk_entry_new();

	GtkWidget *label_service_name = gtk_label_new("Service name:");
	add_password_page.entry_service_name = gtk_entry_new();
	
	GtkWidget *label_service_link = gtk_label_new("Service link:");
	add_password_page.entry_service_link = gtk_entry_new();
	
	GtkWidget *label_password = gtk_label_new("Password:");
	add_password_page.entry_password = gtk_entry_new();
	
	GtkWidget *label_password_check = gtk_label_new("Password check:");
	add_password_page.entry_password_check = gtk_entry_new();
	
	gtk_entry_set_visibility(GTK_ENTRY(add_password_page.entry_password), FALSE); /* Hide the password */
	gtk_entry_set_visibility(GTK_ENTRY(add_password_page.entry_password_check), FALSE); /* Hide the password check also */
	add_password_page.error_label = gtk_label_new("");
	
	/* Create and connect button to callback function */
	GtkWidget *add_password_button = gtk_button_new_with_label("Add password");
	g_signal_connect(add_password_button, "clicked", G_CALLBACK(on_add_password_button_clicked), NULL);
	
	/* Attach widget to grid */
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), label_email, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), add_password_page.entry_email, 1, 1, 1, 1);
	
	
	gtk_grid_attach(GTK_GRID(grid), label_username, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), add_password_page.entry_username, 1, 2, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_password, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), add_password_page.entry_password, 1, 3, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_password_check, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), add_password_page.entry_password_check, 1, 4, 1, 1);

	gtk_grid_attach(GTK_GRID(grid), label_service_name, 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), add_password_page.entry_service_name, 1, 5, 1, 1);

	gtk_grid_attach(GTK_GRID(grid), label_service_link, 0, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), add_password_page.entry_service_link, 1, 6, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), add_password_button, 1, 7, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), add_password_page.error_label, 0, 8, 2, 1);

	/* Pack the grid at the container box and center it */
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
	gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	
	/* Set stack title and box as stack child */
	gtk_stack_add_titled(GTK_STACK(stack), vbox, "add_password", "Add Password Page");
}
