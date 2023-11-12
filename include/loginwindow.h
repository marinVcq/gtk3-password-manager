// loginwindow.h

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <gtk/gtk.h>
#include "myapp.h"

#define LOGIN_WINDOW_TYPE (login_window_get_type())

G_DECLARE_FINAL_TYPE(LoginWindow, login_window, LOGIN, WINDOW, GtkApplicationWindow);

LoginWindow *login_window_new(MyApp *app);
static void on_login_window_dispose(GObject *object);

#endif // LOGINWINDOW_H
