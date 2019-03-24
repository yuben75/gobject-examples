#include <stdio.h>
#include <glib.h>

gboolean showme(gpointer user_data)
{
   printf("BAD!\n");

   /* TRUE 就繼續每秒跑一次；若是 return FALSE，則不再繼續執行 */
   return TRUE;
}

int main(int argc, char **argv)
{
   GMainContext *main_context;

   /* 每秒跑一次 show() */
   g_timeout_add(1000, showme, NULL);

   /* 進入程式 Loop，例如：gtk_main() */
   g_main_loop_run(g_main_loop_new (main_context, FALSE));
}
