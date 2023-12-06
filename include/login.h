/* login.h */
#ifndef LOGIN_H
#define LOGIN_H

#include <gtk/gtk.h>
#include "../include/auth_context.h"
#include "../include/mainwindow.h"
/* LoginPage structure */
typedef struct {
	GtkWidget *entry_username;
	GtkWidget *entry_password;
	GtkWidget *error_label;
	GtkWidget *stack;
	int user_id;
} LoginPage;

/* Declare the login_page */ 
extern LoginPage login_page;

void on_login_button_clicked(GtkButton *button, gpointer data);
void create_user_page_button_clicked(GtkButton *button, gpointer data);
void login_init(GtkWidget *stack);
int get_user_id(const char *username);

#endif // LOGIN_H

