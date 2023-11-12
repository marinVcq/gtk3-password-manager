// authenticatedwindow.h

#ifndef AUTHENTICATEDWINDOW_H
#define AUTHENTICATEDWINDOW_H

#include <gtk/gtk.h>
#include "myapp.h"

#define AUTHENTICATED_WINDOW_TYPE (authenticated_window_get_type())

G_DECLARE_FINAL_TYPE(AuthenticatedWindow, authenticated_window, AUTHENTICATED, WINDOW, GtkApplicationWindow)

AuthenticatedWindow *authenticated_window_new(MyApp *app);
void logout_button_clicked(GtkButton *button, AuthState *auth_state);

#endif /* AUTHENTICATEDWINDOW_H */

