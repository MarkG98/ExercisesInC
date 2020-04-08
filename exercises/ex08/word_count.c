/*
    Program to create a word -> frequency hash table.
    To run type 'make word_count' to compile and then
    type './word_count Moby.txt' to run on the text file
    in the directory.

    Author: Mark Goldwater
*/


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


/*
    Iterates through the map of words and frequencies and prints
    the key and value in the format specified by user_data.

    key: key for hash table
    value: value in hash table
    user_data: format in which to print key and value.
*/
void iterator(gpointer key, gpointer value, gpointer user_data)
{
  g_print(user_data, key, *(gint*)value);
}

int main(int argc, char** argv)
{
    // Initialize hash table
    GHashTable *map = g_hash_table_new(g_str_hash, g_str_equal);

    // Variables for hash table
    int *current_val;
    int temp_int = 0;
    int unit = 1;
    gpointer p_unit = (gpointer) &unit;

    // Variables for getting contents of file
    GError *err = NULL;
    gchar *contents = "";
    gchar *fin_contents = "";

    // Variable for splitting text
    gchar **word_array = NULL;

    // Variable for key
    gchar *tmp = "";

    // Get file contents and check for error
    if(!g_file_get_contents(argv[1], &contents, NULL, &err))
    {
        g_print("%s\n", err->message);
    }

    // Add "NULL" to end to know here to stop.
    fin_contents = g_strconcat(contents, " NULL", NULL);

    // Split by spaces
    word_array = g_strsplit(fin_contents, " ", -1);


    int i = 0;
    while(g_strcmp0(word_array[i], "NULL"))
    {
      i++;

      // Strip punctuation
      g_strdelimit(word_array[i], ";.:?()[],", ' ');
      tmp = g_strstrip(word_array[i]);

      // Logic for building hash table
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

    // Print out key-value pairs
    g_hash_table_foreach(map, (GHFunc)iterator, "%s: %d\n");
  }
