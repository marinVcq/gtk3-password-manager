/* mainwindow.c */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtk/gtk.h>
#include "../include/database.h"

/* MainPage structure */
typedef struct {
	GtkWidget *stack;
	GtkWidget *list_box;
	GtkWidget *entry_search;
	PasswordInfo *passwords;
	int user_id;
} MainPage;

extern MainPage main_page;
extern GtkWidget *passwords_list_box;

void on_logout_button_clicked(GtkButton *button, gpointer data);
void on_add_button_clicked(GtkButton *button, gpointer data);
void mainwindow_init(GtkWidget *stack);
GtkWidget *create_header_row();
void display_passwords_in_terminal(PasswordInfo *passwords, int num_passwords);
void populate_passwords_list(GtkWidget *list_box); 
GtkWidget *create_password_box(const PasswordInfo *password);
void add_header_row(GtkWidget *list_box);
void update_and_populate_passwords_list(GtkWidget *list_box, int user_id);
void populate_passwords_list_filter_by(GtkWidget *list_box);
void set_user_id(int user_id);
void restart_application();


#endif // MAINWINDOW_H

