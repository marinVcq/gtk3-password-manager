// main.c

#include <gtk/gtk.h>
#include "../include/myapp.h"
#include "../include/loginwindow.h"
#include "../include/authenticatedwindow.h"


/* Signal handler for login button click */
static void login_button_clicked(GtkButton *button, AuthState *auth_state)
{
	/* Here we perform the authentication logic: for convenience set it directly to TRUE */
	auth_state->authenticated = TRUE;
	
	/* Then Hide the login window and show the authenticated window */
	gtk_widget_hide(GTK_WIDGET(button));
	MyApp *app = MY_APP(g_application_get_default());
	AuthenticatedWindow *auth_win = authenticated_window_new(app);
	gtk_widget_show_all(GTK_WIDGET(auth_win)); 
}

/* Signal Handler for logout button click */
static void logout_button_clicked(GtkButton *button, AuthState *auth_state)
{
	/* Reset authentication state */
	auth_state->authenticated = FALSE;
	
	/* This time the authenticated window is hide and the login window is showed again */
	gtk_widget_hide(GTK_WIDGET(button));
	MyApp *app = MY_APP(g_application_get_default());
	LoginWindow *login_win = login_window_new(app);
	gtk_widget_show_all(GTK_WIDGET(login_win));
}

int main(int argc, char *argv[]) {
    /* Initialize GTK */
    gtk_init(&argc, &argv);

    /* Create the application instance */
    MyApp *app = my_app_new();

    /* Create the authentication state */
    AuthState auth_state = { .authenticated = FALSE };

    /* Connect signals */
    g_signal_connect(app, "activate", G_CALLBACK(my_app_activate), NULL);
    g_signal_connect(app, "startup", G_CALLBACK(my_app_startup), NULL);

    /* Run the application */
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    /* Clean up */
    g_object_unref(app);

    return status;
}



























