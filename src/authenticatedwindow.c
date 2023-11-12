// authenticatedwindow.c

#include "../include/authenticatedwindow.h"

struct _AuthenticatedWindow {
  GtkApplicationWindow parent;
};

G_DEFINE_TYPE(AuthenticatedWindow, authenticated_window, GTK_TYPE_APPLICATION_WINDOW)

static void authenticated_window_init(AuthenticatedWindow *win) {
  // Initialization code for the authenticated window
}

static void authenticated_window_class_init(AuthenticatedWindowClass *class) {
  // Class initialization code for the authenticated window
}

AuthenticatedWindow *authenticated_window_new(MyApp *app) {
  return g_object_new(AUTHENTICATED_WINDOW_TYPE, "application", app, NULL);
}

