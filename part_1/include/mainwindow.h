#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtk/gtk.h>

void on_logout_button_clicked(GtkButton *button, gpointer data);
void mainwindow_init(GtkWidget *stack); // Change GtkStack to GtkWidget

#endif // MAINWINDOW_H

