
#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

GtkListStore *list_store;
GtkWidget *tree_view;
GtkWidget *entry;
GtkWidget *vbox;
GtkWidget *window;
GtkWidget *container_box;

#define COUNTRY_SIZE 50
#define ROW_SIZE 50

char **array = NULL;

void on_entry_changed(GtkEditable *editable, gpointer data);
gboolean on_entry_in_out_focus(GtkWidget *_widget_, GdkEvent *_event_, gpointer _data_);
void on_row_selected(GtkTreeView *tree_view, gpointer user_data);
static void on_exit_window_signal(GtkWidget *widget, gpointer ptr);

int main(int argc, char *argv[])
{
  // Allocate memory for array
  array = (char **)calloc(ROW_SIZE, sizeof(char *));

  for (int i = 0; i < ROW_SIZE; i++)
  {
    array[i] = (char *)calloc(COUNTRY_SIZE, sizeof(char));
    memset(array[i], 0x00, sizeof(char) * COUNTRY_SIZE);
  }

  // Fill the array
  strcpy(array[0], "Indonesia");
  strcpy(array[1], "United States");
  strcpy(array[2], "China");
  strcpy(array[3], "India");
  strcpy(array[4], "Brazil");
  strcpy(array[5], "Russia");
  strcpy(array[6], "Japan");
  strcpy(array[7], "Mexico");
  strcpy(array[8], "Germany");
  strcpy(array[9], "France");
  strcpy(array[10], "United Kingdom");
  strcpy(array[11], "Canada");
  strcpy(array[12], "Australia");
  strcpy(array[13], "South Korea");
  strcpy(array[14], "Italy");
  strcpy(array[15], "Spain");
  strcpy(array[16], "Netherlands");
  strcpy(array[17], "Switzerland");
  strcpy(array[18], "Sweden");
  strcpy(array[19], "Norway");
  strcpy(array[20], "Argentina");
  strcpy(array[21], "Chile");
  strcpy(array[22], "Colombia");
  strcpy(array[23], "Peru");
  strcpy(array[24], "South Africa");
  strcpy(array[25], "Nigeria");
  strcpy(array[26], "Egypt");
  strcpy(array[27], "Kenya");
  strcpy(array[28], "Morocco");
  strcpy(array[29], "Saudi Arabia");
  strcpy(array[30], "Turkey");
  strcpy(array[31], "Iran");
  strcpy(array[32], "Pakistan");
  strcpy(array[33], "Bangladesh");
  strcpy(array[34], "Vietnam");
  strcpy(array[35], "Thailand");
  strcpy(array[36], "Malaysia");
  strcpy(array[37], "Singapore");
  strcpy(array[38], "Philippines");
  strcpy(array[39], "New Zealand");
  strcpy(array[40], "Greece");
  strcpy(array[41], "Poland");
  strcpy(array[42], "Czech Republic");
  strcpy(array[43], "Hungary");
  strcpy(array[44], "Austria");
  strcpy(array[45], "Portugal");
  strcpy(array[46], "Ireland");
  strcpy(array[47], "Belgium");
  strcpy(array[48], "Netherlands");
  strcpy(array[49], "Denmark");
  // Add more countries as needed

  // Init GTK
  gtk_init(&argc, &argv);

  // Create a window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Entry Country Name");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_exit_window_signal), NULL);

  // Create an entry
  entry = gtk_entry_new();

  // Connect a callback to handle entry changes
  g_signal_connect(G_OBJECT(entry), "changed", G_CALLBACK(on_entry_changed), NULL);
  g_signal_connect(G_OBJECT(entry), "focus-in-event", G_CALLBACK(on_entry_in_out_focus), NULL);
  g_signal_connect(G_OBJECT(entry), "focus-out-event", G_CALLBACK(on_entry_in_out_focus), NULL);

  // Create a vertical box and pack the entry
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

  // Create a container that gonna contained with tree view (list of country)
  container_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), container_box, FALSE, FALSE, 0);

  // Add the vertical box to the window
  gtk_container_add(GTK_CONTAINER(window), vbox);

  // Show all widgets
  gtk_widget_show_all(window);

  // Start the GTK main loop
  gtk_main();

  return 0;
}

static void on_exit_window_signal(GtkWidget *widget, gpointer ptr)
{
  // free the array
  for (int i = 0; i < ROW_SIZE; i++)
    free(array[i]);
  free(array);
  gtk_main_quit();
}

// Callback function for handling entry changes
void on_entry_changed(GtkEditable *editable, gpointer data)
{
  // Get Entry Text
  const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));

  // clear the list store
  gtk_list_store_clear(list_store);
  GtkTreeIter iter;

  /* IDK what happen, but when i try to fill the list after clear it, only 1 item got shown, even the list already have 2 or more item on it */
  /* i though its because i try to clear the empty list, but when i make the code like dont clear the list if there is no row on it, its still the same */
  /* but when i using this code, its work just fine, just comment this code if u want to see the bug */
  gtk_list_store_append(list_store, &iter);
  gtk_list_store_set(list_store, &iter, 0, "", -1);
  gtk_list_store_clear(list_store);
  /* ------------------------------- end of code -------------------------------*/

  for (int i = 0; i < ROW_SIZE; i++)
  {
    // compare text with array
    if (strlen(text) == 0)
      continue;

    if (array[i] != NULL)
    {
      if (strncasecmp(array[i], text, strlen(text)) == 0)
      {
        // add to drop-down list
        gtk_list_store_append(list_store, &iter);
        gtk_list_store_set(list_store, &iter, 0, array[i], -1);
      }
    }
  }
}

gboolean on_entry_in_out_focus(GtkWidget *_widget_, GdkEvent *_event_, gpointer _data_)
{
  printf("entry focus\n");
  // show the drop-down if entry get active
  if (_event_->focus_change.in)
  {
    printf("create new list store\n");
    if (gtk_container_get_children(GTK_CONTAINER(container_box)) != NULL)
    {
      gtk_container_remove(GTK_CONTAINER(container_box), tree_view);
      gtk_widget_show_all(window);
    }
    // Create a list store
    list_store = gtk_list_store_new(1, G_TYPE_STRING);

    // Create a tree view
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_view), FALSE);

    // Create a column for the data
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Country", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    gtk_container_add(GTK_CONTAINER(container_box), tree_view);
    g_signal_connect(G_OBJECT(tree_view), "row-activated", G_CALLBACK(on_row_selected), NULL);
    gtk_widget_show_all(window);
  }
  return GDK_EVENT_PROPAGATE;
}

void on_row_selected(GtkTreeView *tree_view_buff, gpointer user_data)
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  GtkTreeSelection *selection = gtk_tree_view_get_selection(tree_view_buff);

  if (gtk_tree_selection_get_selected(selection, &model, &iter))
  {
    // Retrieve data from the selected row
    gchar *country;
    gtk_tree_model_get(model, &iter, 0, &country, -1);

    gtk_entry_set_text(GTK_ENTRY(entry), country);

    // Free allocated memory
    g_free(country);

    if (gtk_container_get_children(GTK_CONTAINER(container_box)) != NULL)
    {
      gtk_container_remove(GTK_CONTAINER(container_box), tree_view);
      gtk_widget_show_all(window);
    }
  }
}