/*1、windows程序头文件说明
(1)stdafx.h是一个预编译头文件，Windows包含进程序的头文件很 多，在程序开发过程中需要不断地编译,如果每次全部重新编译非常浪费时间；
(2)stdafx的目的就是将前面编译的结果储存起来，下一次编译时从 磁盘取出来，对未修改部分不再重新编译,这样可大大节省编译时间；
(3)stdafx.cpp中主要有包含windows.h一条指令，windows.h，
windows.h是windows程序最基本的头文件，它们定义了windows 的所有数据类型、数据结构、符号常量和API函数原型声明
*/
/*
2、WinMain函数是windows程序的入口函数，包含4 个参数：
(1)hInstance是唯一标识本程序的实例句柄，系统和其它应用 程序通过该句柄与本程序通讯。
(2)hPrevInstance是本程序的前一个实例句柄，由32位windows采用 进程－线程模式，每一线程拥有自己的句柄，因此该参数始终为空。
(3)lpCmdLine是一个字符串指针，指向命令行参数   字符串，没有命令行参数时为空。
(4)nCmdShow指明程序最初运行时窗口打开方式，如正常方式、最大 化或最小化运行。
(5)WinMain返回一个整数值，作为退出代码。APIENTRY表示函数调用约定，函数调用时参数按从左至右的顺序压入栈，由被调用者将参数弹出栈。
例如：
int WINAPI WinMain(HINSTANCE hInstance, //应用程序当前实例句柄
HINSTANCE hPrevInstance,  //应用程序先前实例句柄
LPSTR lpCmdLine,//指向应用程序命令行的字符串指针，不包括执行文件名
int nCmdShow)//指明窗口如何显示，假如SW_HIDE 隐藏窗口并且激活另外一个窗口
*/
/*
剖析Windows核心技术1
1.WinMain---在WinMain中主要完成以下工作：       
(1)定义一个窗口类，包括定义窗口对象并对它的相关成员赋值； 
(2)注册窗口类，调用RegisterClass注册窗口类，并判断是否注册成功。其参数是WNDCLASS结构类型指针，用需要注册的窗口对象地址进行调用；  
(3)创建窗口，定义注册窗口后，可以创建一个或多个同类型的窗口；由API函数CreateWindow创建窗口，并返回所创建窗口的句柄； 
(4)调用API函数ShowWindow和UpdateWindow显示并更新窗口，它们的参数相同，第一个参数是要显示的窗口句柄，第二个参数是窗口显示的方式；
(5)程序运行的准备工作完成，进入消息循环(while循环)，GetMessage函数从应用程序消息队列中读取消息，TranslateMessage函数进行键盘消息转换，
然后由DispatchMessag将消息派送给相应的窗口函数进行处理，当消息队列为空时，应用程序进入等待状态,等待用户输入。
*/
/*
a.GetMessage函数原型如下：       
BOOL WINAPI GetMessage (LPMSG, HWND, UINT, UINT );

其中第一个参数为存放消息的MSG结构指针，  第二个参数表示接收消息的窗口句柄，  第三、四个参数分别表示要获取的最大和最小消息值。
当后三个参数值设为NULL或0时,表示应用程序接收它 所创建的所有窗口的所有消息。
当GetMessage获取到WM_QUIT消息时，返回FALSE，结束消息循环。 

b.TranslateMessage函数负责键盘消息转换。
TranslateMessage完成的工作 :
击键消息除字符键消息外，其它击键操作产生虚拟键消息，包括   
WM_KEYDOWN，   
WM_SYSKEYDOWN，   
WM_KEYUP，   
WM_SYSKEYUP， 
这些虚拟键消息必须通过转换成字符消息程序才能响应，这就是 TranslateMessage完成的工作。

c.DispatchMessage函数     负责将消息派送到相应的窗口函数
*/
/*
2.WndProc函数   -----是一个消息处理函数，应用程序的表现完全取决于窗口函数 的定义。
WndProc的原型如下：   
LRESULT CALLBACK  WndProc (HWND hwnd,UINT message,WPARAM wParam, LPARAM lParam);                    
第一个参数表示对应窗口的句柄，       
第二个参数是需要处理的消息的消息值，        
第三、四个参数包含了相应消息的某些信息，如消息发生时鼠标位置等等。 
WndProc函数的结构是一个switch语句，根据消息值不同，选择不同的case子句执行 。
*/
/*
3.进队消息和不进队消息
窗口函数一般由系统调用，应用程序不直接调用它，而是通 过SendMessage()函数发送消息来间接调用窗口函数。      
消息分为进队消息和不进队消息。
(⑴)进队消息      -----是由windows放入应用程序消息队列、由应用程序消 息循环从消息队列中取出并派送到窗口函数的消息。
调用API函数PostMessage可以派送(dispatch)一条消   息到指定窗口的消息队列，其原型如下：
BOOL WINAPI PostMessage(HWND hWnd,UINT Msg,WPARAM wParam, LPARAM lParam) ;            
其中Msg参数指定了要发送的消息值(名)。

(2)不进队消息            -----不进入消息队列，直接发送(send)给指定窗口的 窗口函数进行处理。
调用CreateWindow()创建窗口时发送的WM_CREATE消息， 调用UpdateWindow()更新窗口时发送的WM_PAINT消息, 
调用DestroyWindow()时发送的WM_DESTROY消息, 都是不进队消息。
可以通过调用SendMessage函数直接发送消息给窗口：
LRESULT WINAPI SendMessage((HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
*/
/*
4.设备描述表  WM_PAINT是重画窗口客户区消息，当窗口内容被改变、移动或窗口被覆盖后，需要对窗口进行重画，
一般应用程序都需要处 理这个消息，处理这一消息需要获取设备描述表句柄。
• Windows的图形设备接口GDI(Graphics Device Interface) 是一组API函数，它提供与设备无关的 图形功能，
使应用程序在不同图形设备(如打印机)上进行相同的操作(调用GDI函 数)，而无需考虑设备的硬件差异，
设备无关性是通过设备描 述表实现的。

设备描述表DC(Device Context)    -----也称为设备上下文，是GDI内部定义的一个有图形对象、 图形方式及其属性的一个数据结构，
与特定设备相关，描述了硬件 设备的具体特征信息。 
与具体设备相关的操作交给DC，  将应用程序的设备无关图形功能调用转换为在设备驱动程序下执行的设备相关操作。
应用程序不能直接访问设备描述表，为了进行图形输出，必须先获取设备描述表句柄，  
然后以设备描述表句柄为参数调用GDI函数，实现图形功能。
*/
/*
5.应用程序的退出
当用户选择File菜单的退出菜单项时，windows会产生一系列消息，如键盘或鼠标消息，       
WM_SYSCOMMAND消息，       
WM_CLOSE消息，       
WM_CLOSE是一条进队消息，      
被放入应用程序消息队列中。
GetMessage函数从消息队列中取得WM_CLOSE消息，由 DispatchMessage派送给窗口函数，窗口函数中没有对WM_CLOSE处理 的代码,
转由缺省窗口函数处理，缺省窗口函数调用DestroyWindow函 数撤销窗口,并将不进队消息WM_DESTROY直接发送给窗口函数，
窗口 函数处理WM_DESTROY时调用函数void PostQuitMessage(int nExitCode);并产生WM_QUIT消息放入消息队列中，
其中参数 nExitCode是应用程序退出代码。
GetMessage函数取得WM_QUIT消息后，返回FALSE，  结束消息 循环，此时msg.wParam中存放的是调用PostQuitMessage时的参数， 
应用程序执行下面语句返回此参数并退出程序。      
return msg.wParam；

使用API函数开发Windows应用程序，程序有大致相同的结构， 在WinMain中完成定义、注册、创建、显示窗口的任务，启动消息 循环，
派送不同消息到各个窗口函数处理；在WndProc函数中，根 据消息参数判断类型，转到相应的代码断进行处理，各种操作都 借助API函数完成。
因此，熟悉掌握Windows程序结构、API函数的功能和参数、 各类消息的一般处理方法及参数的含义，都非常重要。
*/
