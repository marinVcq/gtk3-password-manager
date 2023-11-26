/* mainwindow.c */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtk/gtk.h>

/* MainPage structure */
typedef struct {
	GtkWidget *stack;
} MainPage;

extern MainPage main_page;

void on_logout_button_clicked(GtkButton *button, gpointer data);
void on_add_button_clicked(GtkButton *button, gpointer data);
void mainwindow_init(GtkWidget *stack);

#endif // MAINWINDOW_H

