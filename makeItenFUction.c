#include <gtk/gtk.h>
#include <cairo/cairo.h>

static GtkWidget* number1;
static GtkWidget* number2;
static GtkWidget* result;

void do_calculate_somme(GtkWidget* calculate, gpointer data)
{
    int num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(number1)));
    int num2 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(number2)));

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "hello: %d", num1 + num2);
    gtk_label_set_text(GTK_LABEL(result), buffer);
}



static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window, *grid, *calculate;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Test hi");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    
    number1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), number1, 0, 0, 1, 1);

    number2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), number2, 0, 1, 1, 1);

    calculate = gtk_button_new_with_label("calculate");
    g_signal_connect(calculate, "clicked", G_CALLBACK(do_calculate_somme), NULL);
    gtk_grid_attach(GTK_GRID(grid), calculate, 0, 3, 1, 1);

    result = gtk_label_new("result:");
    gtk_grid_attach(GTK_GRID(grid), result, 1, 3, 1, 1);

    

    gtk_widget_show_all(window);
    gtk_main();

}



int main(int argc, char const *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

  return status;
}
