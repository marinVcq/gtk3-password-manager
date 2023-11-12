// loginwindow.h

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <gtk/gtk.h>
#include "myapp.h"

#define LOGIN_WINDOW_TYPE (login_window_get_type())

G_DECLARE_FINAL_TYPE(LoginWindow, login_window, LOGIN, WINDOW, GtkApplicationWindow);

LoginWindow *login_window_new(MyApp *app);
void on_login_window_dispose(GObject *object);
void on_login_button_clicked(GtkButton *button, LoginWindow *login_win);

#endif // LOGINWINDOW_H
