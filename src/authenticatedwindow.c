// authenticatedwindow.c

#include "../include/authenticatedwindow.h"
#include "../include/loginwindow.h"

struct _AuthenticatedWindow {
  GtkApplicationWindow parent;
};

G_DEFINE_TYPE(AuthenticatedWindow, authenticated_window, GTK_TYPE_APPLICATION_WINDOW)

static void authenticated_window_init(AuthenticatedWindow *win) {

	/* Initialization code for the login window */
	gtk_window_set_default_size(GTK_WINDOW(win), 740, 480);
	  
}

static void authenticated_window_class_init(AuthenticatedWindowClass *class) {
  // Class initialization code for the authenticated window
}

AuthenticatedWindow *authenticated_window_new(MyApp *app) {
  return g_object_new(AUTHENTICATED_WINDOW_TYPE, "application", app, NULL);
}

/* Signal Handler for logout button click */
void logout_button_clicked(GtkButton *button, AuthState *auth_state)
{
	/* Reset authentication state */
	auth_state->authenticated = FALSE;
	
	/* This time the authenticated window is hide and the login window is showed again */
	gtk_widget_hide(GTK_WIDGET(button));
	MyApp *app = MY_APP(g_application_get_default());
	LoginWindow *login_win = login_window_new(app);
	gtk_widget_show_all(GTK_WIDGET(login_win));
}

