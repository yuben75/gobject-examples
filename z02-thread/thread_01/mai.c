#include <glib.h>
#include <glib/gprintf.h>
#include <unistd.h>
#include <sys/syscall.h>
/* 
--------------------- 
作者：andylauren 
来源：CSDN 
原文：https://blog.csdn.net/andylauren/article/details/79307483 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
gpointer thread_func1 (gpointer data)
{
	g_printf("%s %ld in\n", __func__, syscall(__NR_gettid));
	g_printf("%s %ld data is : %d\n", __func__, syscall(__NR_gettid), *((gint *)data));
	g_usleep (2000000);
	g_printf("%s %ld out\n", __func__, syscall(__NR_gettid));
 
	g_thread_exit ((gpointer)20);//等价于return
	//return (gpointer)20;
}
 
int main(int argc, char **argv)
{
	g_printf ("main in\n");
 
	gint func1_data = 11;
	GThread *gthread = NULL;
	gthread = g_thread_new ("func1", thread_func1, &func1_data);
	//gthread = g_thread_try_new ("func1", thread_func1, &func1_data);
	//if(gthread == NULL) g_printf ("g_thread_try_new fail\n");
 
	g_printf ("g_thread_join %ld\n", (gint64)g_thread_join (gthread));
	g_usleep (5000000);
	
	g_printf ("main out\n");
    return 0;

}
