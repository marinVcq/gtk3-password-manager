/* add_password.h */
#ifndef ADD_PASSWORD_H
#define ADD_PASSWORD_H

#include <gtk/gtk.h>

/* AddPasswordPage structure */
typedef struct {
	GtkWidget *entry_username;
	GtkWidget *entry_service_name;
	GtkWidget *entry_service_link;
	GtkWidget *entry_email;
	GtkWidget *entry_password;
	GtkWidget *entry_password_check;
	GtkWidget *error_label;
	GtkWidget *stack;
} AddPasswordPage;

/* Declare the add_password_page */ 
extern AddPasswordPage add_password_page;

void on_add_password_button_clicked(GtkButton *button, gpointer data);
void add_password_init(GtkWidget *stack);

#endif // ADD_PASSWORD_H
