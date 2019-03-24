#include <glib.h>
#include <glib/gprintf.h>

typedef struct _MySource MySource;
struct _MySource
{
    GSource source;
    gchar text[256];
};

static gboolean prepare(GSource *source, gint *timeout)
{
    *timeout = 0;

    return TRUE;
}

static gboolean check(GSource *source)
{
    return TRUE;
}

static gboolean dispatch(GSource *source, GSourceFunc callback, gpointer user_data)
{
    MySource *mysource = (MySource *)source;

    g_print("%s\n", mysource->text);

    return TRUE;
}

int main(void)
{
    GMainLoop *loop = g_main_loop_new(NULL, TRUE);

    GMainContext *context[2];
    context[0]= g_main_loop_get_context(loop);
    //context[1]= g_main_loop_get_context(loop);
    GSourceFuncs source_funcs = {prepare, check, dispatch, NULL};

    GSource *source[2];
    source[0]= g_source_new(&source_funcs, sizeof(MySource));
    source[1]= g_source_new(&source_funcs, sizeof(MySource));

    g_sprintf(((MySource *)source[0])->text, "source[0]");
    g_sprintf(((MySource *)source[1])->text, "source[1]");

    g_source_attach(source[0], context[0]);
    g_source_attach(source[1], context[1]);

    g_source_unref(source[0]);
    g_source_unref(source[1]);

    g_main_loop_run(loop);

    g_main_context_unref(context[0]);
    g_main_context_unref(context[1]);
    g_main_loop_unref(loop);

    return 0;
}