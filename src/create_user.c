/* create_user.c */
#include <stdbool.h>
#include "../include/create_user.h"
#include "../include/database.h"

/* Declare instance of register page */
RegisterPage register_page;

/* Handle click on create user button */
void on_create_user_button_clicked(GtkButton *button, gpointer data)
{
	const char *username = gtk_entry_get_text(GTK_ENTRY(register_page.entry_username));
	const char *email = gtk_entry_get_text(GTK_ENTRY(register_page.entry_email));
	const char *password = gtk_entry_get_text(GTK_ENTRY(register_page.entry_password));
	const char *password_check = gtk_entry_get_text(GTK_ENTRY(register_page.entry_password_check));
	GtkWidget *stack = register_page.stack;
	GtkWidget *error_label = register_page.error_label;
	
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
	
	/* Check if user exists */
	if (insert_user(username, email, password)) {
		
		/* Handle success */ 
		g_print("Add user to database\n");
		
		/* Go to login page & clear error message */
		gtk_stack_set_visible_child_name(GTK_STACK(stack), "login");
		gtk_label_set_text(GTK_LABEL(error_label), "");

	}else{
		/* Handle error */
		gtk_label_set_text(GTK_LABEL(error_label), "Fail to create user");
	}
}

/* Initialization of register page */
void create_user_init(GtkWidget *stack) { // Change GtkStack to GtkWidget

	/* Init the RegisterPage structure */
	register_page.stack = stack;

	/* Create a box container */
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	/* Create a grid */
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 15);

	/* Create or initialize all widgets */
	GtkWidget *label = gtk_label_new("Welcome to the Register page!");
	GtkWidget *label_email = gtk_label_new("Email:");
	register_page.entry_email = gtk_entry_new();
	GtkWidget *label_username = gtk_label_new("Username:");
	register_page.entry_username = gtk_entry_new();
	GtkWidget *label_password = gtk_label_new("Password:");
	register_page.entry_password = gtk_entry_new();
	GtkWidget *label_password_check = gtk_label_new("Password check:");
	register_page.entry_password_check = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(register_page.entry_password), FALSE); /* Hide the password */
	gtk_entry_set_visibility(GTK_ENTRY(register_page.entry_password_check), FALSE); /* Hide the password check also */
	register_page.error_label = gtk_label_new("");
	
	/* Create and connect button to callback function */
	GtkWidget *create_user_button = gtk_button_new_with_label("Create User");
	g_signal_connect(create_user_button, "clicked", G_CALLBACK(on_create_user_button_clicked), NULL);
	
	/* Attach widget to grid */
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), label_email, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), register_page.entry_email, 1, 1, 1, 1);
	
	
	gtk_grid_attach(GTK_GRID(grid), label_username, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), register_page.entry_username, 1, 2, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_password, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), register_page.entry_password, 1, 3, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_password_check, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), register_page.entry_password_check, 1, 4, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), create_user_button, 1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), register_page.error_label, 0, 6, 2, 1);

	/* Pack the grid at the container box and center it */
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
	gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
	
	/* Set stack title and box as stack child */
	gtk_stack_add_titled(GTK_STACK(stack), vbox, "create_user", "Register Page");
}
