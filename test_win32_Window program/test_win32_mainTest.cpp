/*
Win32程序设计

// 导入包含文件windows.h，此文件包含其它的windows头文件

WINDEF.H       基本类型定义
WINNT.H		   支持Unicode类型定义
WINBASE.H      内核函数
WINGDI.H       图形设备接口函数
WINUSER.H      用户接口函数
*/
#include<Windows.h>
/*
窗口对象过程的处理函数
LRESULT      定义为LONG(long)
CALLBACK     __stdcall，指在windows本身和用户的应用程序之间发生的函数调用的特殊调用序列
HWND         窗口句柄 32位数字，该参数为接受消息的窗口句柄（CreateWindoww函数返回值）
UINT         unsigned int 无符号整型32位
WPARAM       UINT，32位消息参数
LPARAM       LONG，32位消息参数
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Windows应用程序的入口函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance/*一般为NULL*/, PSTR lpszCmdLine, int iCmdShow)
{
	/*
	定义窗口类
	TCHAR:char
	_T和TEXT宏，功能一致通常没有，在Unicode系统中，
	自动把后面的字符串转换为宽字符串
	*/
	TCHAR tcClassName[] = TEXT("MySeondProgramming");   // 窗口类名字符

	//定义一个窗口类结构，这个结构体中有多个窗口的属性对象，通过对这些对象赋值来改变窗口的属性
	WNDCLASS wndclass;//
	//窗口属性描述
	wndclass.lpszClassName = tcClassName;//窗口类名
	wndclass.lpszMenuName = nullptr;//窗口类菜单资源名称
	wndclass.hInstance = hInstance;//当前进程对象句柄，接受WinMain参数
	wndclass.lpfnWndProc = WndProc;                                 // 窗口对象的过程处理函数，指向函数的指针
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//窗口背景刷子对象
	wndclass.hIcon=(HICON)::LoadImage(NULL, L"CaptionICO.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); 
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                 // 光标对象
	wndclass.cbClsExtra = 0;                                        // 同类窗口对象公共数据区大小
	wndclass.cbWndExtra = 0;                                        // 当前窗口对象私有数据区大小
	wndclass.style = CS_HREDRAW | CS_VREDRAW;                       // 窗口类风格，水平或垂直尺寸改变后刷新

	// 注册窗口类  参数为指向WNDCLASS结构的指针
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("RegisterClass ERROR."), TEXT("ERROR"), MB_ICONERROR);

		return 0;                                                   //  如果注册失败，返回并终止程序
	}

	// 定义窗口对象属性  指定有关窗口参数详细介绍
	TCHAR tcWindowCaptionName[] = TEXT("Windows窗口设计");    // 窗口对象标题名称
	CREATESTRUCT cs;//// 窗口对象属性描述结构
	cs.lpszClass = tcClassName;// 窗口类名
	cs.lpszName = tcWindowCaptionName; // 窗口对象标题名称，显示在标题栏
	cs.style = WS_OVERLAPPEDWINDOW;// 窗口对象风格
	cs.x = 100;// 窗口对象在屏幕上的x坐标
	cs.y = 200;// 窗口对象在屏幕上的y坐标
	cs.cx = 500;// 窗口对象的宽度
	cs.cy = 400;// 窗口对象的高度
	cs.hwndParent = NULL; // 窗口对象的父窗口句柄 
	cs.hMenu = NULL;  // 窗口对象菜单句柄或子窗口编号
	cs.hInstance = hInstance; // 当前进程 实例句柄，WinMain参数
	cs.lpCreateParams = NULL;   // 创建参数指针，可以访问以后想要引用的程序中的数据

	/*
	创建窗口对象
	定义窗口句柄hWnd，值为CreateWindow函数的返回值
	创建成功返回窗口句柄，否则返回NULL
	*/
	HWND hWnd = CreateWindow(cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy, 
		cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
	// 判断窗口创建是否成功
	if (hWnd == NULL)
	{
		MessageBox(NULL, TEXT("CreateWindow ERROR."), TEXT("ERROR"), MB_ICONERROR);

		return 0;
	}
	// 显示窗口
	ShowWindow(hWnd, iCmdShow);//iCmdShow指明窗口如何显示，假如SW_HIDE 隐藏窗口并且激活另外一个窗口
	// 更新窗口
	UpdateWindow(hWnd);
	// 消息循环，有了这个窗口才不会一闪而过
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);  // 将msg结构传递给windows，进行虚拟键盘消息的转换
		DispatchMessage(&msg);   // 发送消息，由此操作系统调用 相应的窗口过程处理消息
	}
	// 主窗口返回
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		/*
		PAINTSTRUCT  绘图结构，定义在WINUSER.H中
		HDC 矩形结构
		RECT 设备描述表句柄
		*/
		PAINTSTRUCT ps;
		HDC hDC;
		RECT rect;

		hDC = BeginPaint(hWnd, &ps);        // 获取显示设备对象及绘制描述属性
		GetClientRect(hWnd, &rect);         //  获取当前窗口对象客户区矩形
		SetBkMode(hDC, TRANSPARENT);        // 设置背景方式 
		SetTextColor(hDC, RGB(255, 0, 0));  // 设置文件颜色

											// 绘制文件
		DrawText(hDC, TEXT("Windows窗口设计"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hWnd, &ps);                // 客户区绘制结束，归还显示设备对象

		return 0;
	}
	case WM_DESTROY:
	{
		// 发送WM_QUIT消息，通知线程消息检索循环，清除窗口主程序可以退出
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
