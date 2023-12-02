/* mainwindow.c */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtk/gtk.h>
#include "../include/database.h"

/* MainPage structure */
typedef struct {
	GtkWidget *stack;
	GtkWidget *list_box;
} MainPage;

extern MainPage main_page;
extern GtkWidget *passwords_list_box;

void on_logout_button_clicked(GtkButton *button, gpointer data);
void on_add_button_clicked(GtkButton *button, gpointer data);
void mainwindow_init(GtkWidget *stack);
GtkWidget *create_header_row();
void display_passwords_in_terminal(PasswordInfo *passwords, int num_passwords);
void populate_passwords_list(GtkWidget *list_box);     


#endif // MAINWINDOW_H

