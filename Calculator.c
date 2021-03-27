#include <gtk/gtk.h>
#include <string.h>
#include "ArbreExpression/evaluerresultat.c"
#include "InfixTpos/hi.c"

GtkWidget *entry;
GtkWidget *Label;
gint pos = 1;

static void appendToEntry(GtkWidget *button, gpointer data)
{
    gtk_editable_insert_text(GTK_EDITABLE(entry), gtk_button_get_label(GTK_BUTTON(button)), sizeof(gtk_button_get_label(GTK_BUTTON(button))), &pos);
    pos += 1;
}

static void deleteValue(GtkWidget *button, gpointer data)
{
    gtk_editable_delete_text(GTK_EDITABLE(entry), pos, pos-1);
    pos -= 1;
}


static void EvaluerExpression(GtkWidget *button, gpointer data)
{
    char * buffer;
    int size = strlen(gtk_entry_get_text(GTK_ENTRY(entry)));
    buffer = (char*)malloc(size);
    strcpy(buffer, gtk_entry_get_text(GTK_ENTRY(entry)));

    printf("%s\n", buffer);
    

    /*Tester l'arbre*/


    //arbre final
    Noeud *Arbre = NULL; 

    infixeToPostfixe(buffer);
    
    //problem here so we need to take the expression and converte it 
    //affichage d'expression
    printf("\n%s\n", buffer);

    //creation d'arbre
    Arbre = creerArbreExpression(buffer); 

    printf("\n");
    //affichage de l'arbre obtenu
    affichage_infixe_expresseion(Arbre);

    float val = evaluer(Arbre);
    //affichage de le resultat obtenu 
    printf("\nle resultat est : %g \n",val);
    char buff[20];
    sprintf(buff, "%g", val);
    /*Fin de teste*/
    gtk_entry_set_text(GTK_ENTRY(entry), buff);
}

static void showExpression(GtkWidget *button, gpointer data)
{
    char *buffer = NULL;
    long sizeStr = strlen(gtk_entry_get_text(GTK_ENTRY(entry)));

    buffer = (char *)malloc(sizeStr);
    strcpy(buffer, gtk_entry_get_text(GTK_ENTRY(entry)));

    gtk_label_set_text(GTK_LABEL(Label), buffer);

}

char CalcDesign[][4] = {
    {'D', '/', '*', '-'},
    {'7', '8', '9', '+'},
    {'4', '5', '6', 'n'},
    {'1', '2', '3', '='},
    {'0', '.', 'n', 'n'}
};

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    
    GtkWidget *button;
    GtkWidget *hbox, *vbox;
    
    GdkRGBA *color = (GdkRGBA*)malloc(sizeof(GdkRGBA));
    color->red = 60000;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    // gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    //le box vertical qui contient les lignes des buttons 
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(vbox), entry);
    gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE); //setting the entry to not be editable
    gtk_widget_set_direction(entry, GTK_TEXT_DIR_LTR); //and inserting text from Left to Right Direction 
    
    for(int i = 0; i < 5; i++){
        //box horizontal qui contient les buttons 
        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
        gtk_container_add(GTK_CONTAINER(vbox), hbox);

        for(int j = 0; j < 4; j++)
        {
            
            char str[2];
            str[0] = CalcDesign[i][j];
            str[1] = '\0';
            if(CalcDesign[i][j] != 'n')
            {
                button = gtk_button_new_with_label(str);
                gtk_container_add(GTK_CONTAINER(hbox), button);

                if(CalcDesign[i][j] == '=')
                {
                    // You need an object to store css information: the CSS Provider
                    GtkCssProvider * cssProvider = gtk_css_provider_new();
                    // Load CSS into the object ("-1" says, that the css string is \0-terminated)
                    gtk_css_provider_load_from_data(cssProvider, "* { background-image:none; background-color:green;}",-1,NULL); 

                    // The "Style context" manages CSS providers (as there can be more of them)            
                    GtkStyleContext * context = gtk_widget_get_style_context(button);   
                    // So we want to add our CSS provider (that contains the CSS) to that "style manager".
                    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);

                    g_signal_connect(button, "clicked", G_CALLBACK(EvaluerExpression), NULL);
                }
                    
                
                else if(CalcDesign[i][j] == 'D')
                    g_signal_connect(button, "clicked", G_CALLBACK(deleteValue), NULL);

                else
                    g_signal_connect(button, "clicked", G_CALLBACK(appendToEntry), NULL);

            }       
        }
    }
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}