/* login.h */
#ifndef LOGIN_H
#define LOGIN_H

#include <gtk/gtk.h>

/* LoginPage structure */
typedef struct {
	GtkWidget *entry_username;
	GtkWidget *entry_password;
	GtkWidget *error_label;
	GtkWidget *stack;
} LoginPage;

/* Declare the loginPage */ 
extern LoginPage login_page;

void on_login_button_clicked(GtkButton *button, gpointer data);
void create_user_page_button_clicked(GtkButton *button, gpointer data);
void login_init(GtkWidget *stack);

#endif // LOGIN_H

