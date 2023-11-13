// authenticatedwindow.h

#ifndef AUTHENTICATEDWINDOW_H
#define AUTHENTICATEDWINDOW_H

#include <gtk/gtk.h>
#include "myapp.h"  // Include myapp.h after the forward declaration

#define AUTHENTICATED_WINDOW_TYPE (authenticated_window_get_type())

// Forward declaration of MyApp to resolve circular dependency
typedef struct _MyApp MyApp;

G_DECLARE_FINAL_TYPE(AuthenticatedWindow, authenticated_window, AUTHENTICATED, WINDOW, GtkApplicationWindow)

AuthenticatedWindow *authenticated_window_new(MyApp *app);
void logout_button_clicked(GtkButton *button, AuthState *auth_state);
void open_preferences_dialog(MyApp *app);
void authenticated_window_startup(GApplication *app);

#endif /* AUTHENTICATEDWINDOW_H */

