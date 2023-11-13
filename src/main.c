// main.c

#include <gtk/gtk.h>
#include "../include/myapp.h"
#include "../include/loginwindow.h"
#include "../include/authenticatedwindow.h"


int main(int argc, char *argv[]) {
    /* Initialize GTK */
    gtk_init(&argc, &argv);

    /* Create the application instance */
    MyApp *app = my_app_new();

    /* Connect signals */
    g_signal_connect(app, "activate", G_CALLBACK(my_app_activate), NULL);
    g_signal_connect(app, "startup", G_CALLBACK(my_app_startup), NULL);

    /* Run the application */
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    /* Clean up */
    g_object_unref(app);

    return status;
}



























