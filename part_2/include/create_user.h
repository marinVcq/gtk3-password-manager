/* create_user.h */
#ifndef CREATE_USER_H
#define CREATE_USER_H

#include <gtk/gtk.h>
#include <string.h>

/* RegisterPage structure */
typedef struct {
	GtkWidget *entry_username;
	GtkWidget *entry_email;
	GtkWidget *entry_password;
	GtkWidget *entry_password_check;
	GtkWidget *error_label;
	GtkWidget *stack;
} RegisterPage;

/* Declare the regsiter_page */ 
extern RegisterPage register_page;

void create_user_init(GtkWidget *stack);
void on_create_user_button_clicked(GtkButton *button, gpointer data);

#endif
