#ifndef LOGIN_H
#define LOGIN_H

#include <gtk/gtk.h>

void on_login_button_clicked(GtkButton *button, gpointer data);
void create_user_page_button_clicked(GtkButton *button, gpointer data);
void login_init(GtkWidget *stack);

#endif // LOGIN_H

