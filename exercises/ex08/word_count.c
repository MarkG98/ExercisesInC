#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gmodule.h>
#include <glib/gstdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gio/gio.h>
#include <string.h>

void iterator(gpointer key, gpointer value, gpointer user_data)
{
  g_print(user_data, key, *(gint*)value);
}

int main(int argc, char** argv)
{
    GHashTable *map = g_hash_table_new(g_str_hash, g_str_equal);

    int *current_val;
    int temp_int = 0;
    int unit = 1;
    gpointer p_unit = (gpointer) &unit;

    GError *err = NULL;
    gchar *contents = "";
    gchar *fin_contents = "";

    gchar **word_array = NULL;
    gchar *tmp = "";

    if(!g_file_get_contents(argv[1], &contents, NULL, &err))
    {
        g_print("%s\n", err->message);
    }

    fin_contents = g_strconcat(contents, " NULL", NULL);

    word_array = g_strsplit(fin_contents, " ", -1);

    int i = 0;
    while(g_strcmp0(word_array[i], "NULL"))
    {
      i++;

      tmp = g_strstrip(word_array[i]);

      current_val = g_hash_table_lookup(map, tmp);
      if (current_val == NULL)
      {
          g_hash_table_insert(map, tmp, p_unit);
      }
      else
      {
          temp_int = *current_val;
          temp_int++;
          g_hash_table_insert(map, tmp, (gpointer) &temp_int);
      }
    }

    g_hash_table_foreach(map, (GHFunc)iterator, "%s: %d\n");

  }
