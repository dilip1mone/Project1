#include <gtk/gtk.h>
#include<stdio.h>
#include<string.h>

#define LENGTH 9

static void print_hello (GtkWidget *widget,
             gpointer   data)
{

  g_print ("Valid IP Address\n");
}
static void print_not (GtkWidget *widget,
             gpointer   data)
{

  g_print ("Not a Valid IP Address\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;
  char revbuf[LENGTH];
   int fr_block_sz = 0;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);
  char ch[9];
  printf("The IP Address\n");
  //gets(ch);
  scanf("%s", ch);

  button = gtk_button_new_with_label ("Check The IP Address Valid Or Not");
  if(strcmp(ch, "127.0.0.1") == 0)
  {
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  FILE *f;
  f = fopen ("/home/kiit/Desktop/ipfile.txt", "w");
  fprintf (f, "%s", ch);
  fclose (f);
  }
  else
    {
      g_signal_connect (button, "clicked", G_CALLBACK (print_not), NULL);
    }
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  //gtk_container_add() ;
/*  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);
*/

  gtk_widget_show_all (window);

}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
   int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);


  return status;
}
