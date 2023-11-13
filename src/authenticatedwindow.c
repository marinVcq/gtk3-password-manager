// authenticatedwindow.c

#include "../include/authenticatedwindow.h"
#include "../include/loginwindow.h"

struct _AuthenticatedWindow {
  GtkApplicationWindow parent;
};

G_DEFINE_TYPE(AuthenticatedWindow, authenticated_window, GTK_TYPE_APPLICATION_WINDOW)

static void preferences_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

	/* Acces MyApp instance */	
	MyApp *my_app = MY_APP(app);
	/* Open a preferences dialog */
	open_preferences_dialog(my_app);
}

static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {
    g_application_quit(G_APPLICATION(app));
}

static GActionEntry app_entries[] = {
    { "preferences", preferences_activated, NULL, NULL, NULL },
    { "quit", quit_activated, NULL, NULL, NULL }
};

void authenticated_window_startup(GApplication *app) {
    G_APPLICATION_CLASS(authenticated_window_parent_class)->startup(app);

    g_action_map_add_action_entries(G_ACTION_MAP(app),
                                    app_entries, G_N_ELEMENTS(app_entries),
                                    app);

    const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };
    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.quit", quit_accels);
}



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

// Function to open a preferences dialog (to be implemented)
void open_preferences_dialog(MyApp *app) {
    // Create a new dialog
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Preferences",
                                                     GTK_WINDOW(app->authenticated_window),
                                                     GTK_DIALOG_MODAL,
                                                     "OK",
                                                     GTK_RESPONSE_OK,
                                                     "Cancel",
                                                     GTK_RESPONSE_CANCEL,
                                                     NULL);

    // Add widgets to the dialog (customize this according to your preferences)
    GtkWidget *label = gtk_label_new("Preferences content goes here.");
    GtkWidget *entry = gtk_entry_new();

    // Pack widgets into the content area of the dialog
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), entry);

    // Show all widgets in the dialog
    gtk_widget_show_all(dialog);

    // Run the dialog and handle the response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_OK) {
        // Handle OK button click
        // You can retrieve values from widgets and update preferences here
    } else if (response == GTK_RESPONSE_CANCEL) {
        // Handle Cancel button click or dialog closure
    }

    // Destroy the dialog after use
    gtk_widget_destroy(dialog);
}
