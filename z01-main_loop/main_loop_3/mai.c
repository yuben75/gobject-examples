#include <glib.h>
gboolean callback(gpointer data)
{
    static int i = 0;
    i++;
    g_print ("timeout_callback called %d times\n",i);
    if (10 == i)
    {
        g_main_loop_quit((GMainLoop*)data);
        return FALSE;
    }

    return TRUE;
}

gboolean prepare(GSource *source,gint *timeout_)
{
    *timeout_ = -1;
    g_print ("[%s]\n", __func__);
    return TRUE;
}

gboolean check(GSource *source)
{
    g_print ("[%s]\n", __func__);
    return TRUE;
}

gboolean dispatch(GSource *source,GSourceFunc callback,gpointer user_data)
{
    g_print ("[%s]\n", __func__);
    if (callback(user_data))
        return TRUE;
    else
        return FALSE;
}

gboolean finalize(GSource *source)
{
    g_print ("[%s]\n", __func__);
    return TRUE;
}

int main()
{
    GMainLoop *loop = NULL;
    GMainContext *context;
    GSource *source;
    int id;

    #if 0
    ---------------------
    作者：Smith先生
    来源：CSDN
    原文：https://blog.csdn.net/acs713/article/details/7641592
    版权声明：本文为博主原创文章，转载请附上博文链接！
    gboolean (*prepare) (GSource *source, gint *timeout_);  //进入睡眠之前，在g_main_context_prepare里，mainloop调用所有Source的prepare函数，计算最小的timeout时间，该时间决定下一次睡眠的时间。
    gboolean (*check) (GSource *source);                    //poll被唤醒后，在 g_main_context_check里，mainloop调用所有Source的check函数，检查是否有Source已经准备好了。如果poll是由于错误或者超时等原因唤醒的，就不必进行dispatch了。
    gboolean (*dispatch) (GSource*source, GSourceFunc callback,gpointer user_data); //当有Source准备好了，在 g_main_context_dispatch里，mainloop调用所有Source的dispatch函数，去分发消息。
    void (*finalize) (GSource *source);                     //在Source被移出时，mainloop调用该函数去销毁Source。
    #endif

    //create a variable of type GSourceFuncs
    GSourceFuncs SourceFuncs =
    {
        prepare,
        check,
        dispatch,
        //finalize,
        NULL
    };

    //create a new source
    source = g_source_new (&SourceFuncs, sizeof(GSource));

    //create a context
    context = g_main_context_new ();

    //attach source to context
    id = g_source_attach (source,context);

    //create a main loop with context
    loop = g_main_loop_new (context,FALSE);

    //set the callback for this source
    g_source_set_callback (source,callback,loop,NULL);

    g_main_loop_run (loop);
    g_main_loop_unref (loop);

    return 0;
}
