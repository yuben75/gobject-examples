g_main_loop_new (NULL, FALSE) 原理分析
https://blog.csdn.net/arag2009/article/details/17095361

g_main_loop_new创建一个main loop对象，一个main loop对象只能被一个线程使用，但一个线程可以有多个main loop对象。在GTK+应用中，一个线程使用多个main loop的主要用途是实现模态对话框，它在gtk_dialog_run函数里创建一个新的main loop，通过该main loop分发消息，直到对话框关闭为止。 g_main_loop_run则是进入主循环，它会一直阻塞在这里，直到让它退出为止。有事件时，它就处理事件，没事件时就睡眠。 g_main_loop_quit则是用于退出主循环，相当于Win32下的PostQuitMessage函数。 Glib main loop的最大特点就是支持多事件源，使用非常方便。来自用户的键盘和鼠标事件、来自系统的定时事件和socket事件等等，还支持一个称为idle的事件源，其主要用途是实现异步事件。
