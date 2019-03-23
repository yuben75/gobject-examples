#if 1

#include <stdio.h>
#include <glib.h>
int main(int argc, char** argv) {
     GList* list = NULL;
     list = g_list_append(list, "Hello world!");
     printf("The first item is '%s'\n", (char *)g_list_first(list)->data);
     return 0;
}

#else


#include <stdio.h>
#include <string.h>
#include <glib.h>
gchar *current_animal_noise = NULL;
static void start(GMarkupParseContext *context,
        const gchar *element_name,
        const gchar **attribute_names,
        const gchar **attribute_values,
        gpointer user_data,
        GError **error)
{
        const gchar **name_cursor = attribute_names;
        const gchar **value_cursor = attribute_values;
        while (*name_cursor) {
                if (strcmp (*name_cursor, "noise") == 0)
                current_animal_noise = g_strdup (*value_cursor);
                name_cursor++;
                value_cursor++;
        }
}
static void end(GMarkupParseContext *context,
        const gchar *element_name,
        gpointer user_data,
        GError **error)
{
        if (current_animal_noise)
        {
                g_free (current_animal_noise);
                current_animal_noise = NULL;
        }
}
static void text(GMarkupParseContext *context,
        const gchar *text,
        gsize text_len,
        gpointer user_data,
        GError **error)
{
        if (current_animal_noise)
                printf("I am a %*s and I go %s. Can you do it?/n",
                    text_len, text, current_animal_noise);
        printf("test text/n");
}
GMarkupParser parser = {
        .start_element = start,
        .end_element = end,
        .text = text,
        .passthrough = NULL,
        .error = NULL
};
int main()
{
        char *buf;
        gsize length;
        GMarkupParseContext *context;
        g_file_get_contents("test.xml", &buf, &length,NULL);
        //g_printf("%s/n",buf);
        context = g_markup_parse_context_new(&parser, 0, NULL, NULL);
        if (g_markup_parse_context_parse(context, buf, length, NULL) == FALSE)
        {
                printf("Couldn't load xml/n");
                g_markup_parse_context_free(context);
                return 0;
        }
}

#endif

