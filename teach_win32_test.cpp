// teach_win32_test.cpp : 定义应用程序的入口点。
//win32框架
//1.入口函数
//2.注册窗口(开辟空间)
//3.初始化创建窗口(初始化)
//4.显示窗口
//5.更新窗口（逻辑部分和绘图部分）
//6.消息循环(操作)
//7.结束入口函数(胜利条件)
#include "stdafx.h"//
#include "teach_win32_test.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例  定义为全局方便下面的函数调用
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);//[重要]我的注册类
BOOL                InitInstance(HINSTANCE, int);// 执行应用程序初始化: 
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);//CALLBACK就是_stdcall表示这个函数可以作为回调函数 只需要msg结构里面的部分成员
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//安全等级类似于scanf() 不防止越界 scanf_s() 防止越界 去掉下面两句不影响
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串 加载字符串 作用是：把项目的名字作为窗口类名和标题名
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEACH_WIN32_TEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);//[重要]窗口注册类，先注册，后初始化窗口 相当于先为变量开辟空间 后对这个变量初始化
	//这里可以做数据的加载0
    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	//这里可以做数据的加载2
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_TEST));//快捷键句柄
	//Windows消息机制
	//Windows把所有的事件当成了消息
	//产生消息：Windows封装了，调用就行
	//传递消息：windows为每一个正在运行的应用程序维护了一个消息队列，Windows往应用程序传递消息已封装，应用程序往内部传递消息是可操作的
	//处理消息
    MSG msg;//消息 结构变量 该结构从线程的消息队列接收消息信息
	/*
	typedef struct tagMSG {
    HWND        hwnd; 把消息传给哪个窗口句柄
    UINT        message; windows把消息理解为编号，消息ID，消息编号WM_开头（无符号整型）
    WPARAM      wParam;消息的辅助信息 把消息归类为某一类，这一类的具体信息 比如鼠标点击类消息里面的x坐标y坐标，相对于这个窗口的坐标
    LPARAM      lParam;消息的辅助信息
    DWORD       time;时间记录
    POINT       pt;鼠标坐标，绝对坐标，较少用
} MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;
	*/
    // 主消息循环: 相当于东西寄到家，去取，应用程序从消息队列取消息
	//1.GetMessage是阻塞函数，会等着消息，如果得到了消息，分析消息类别是不是WM_QUIT（关闭），如果是返回FALSE
	//2.while（GetMessage）是等待用户操作的模型
	//3..while（GetMessage）是阻塞函数模型，更省资源
	/*
    while (GetMessage(&msg, nullptr, 0, 0))//使用GetMessage从消息队列里面获得消息
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//是不是快捷键消息
        {
            TranslateMessage(&msg);//翻译消息，比如键盘按下
            DispatchMessage(&msg);//投递消息，应用程序往内部传递消息使用，投递给窗口消息处理函数WndProc进行处理，重要！
			//比如关闭窗口这个动作首先在消息队列产生(windows封装)，接着GetMessage()取出，然后DispatchMessage()进行投递处理消息
        }
    }
	*/
	/*
	BOOL GetMessage(
  LPMSG lpMsg, 指向MSG结构的指针，该结构体从线程的消息队列接收消息信息。
  HWND  hWnd,//哪个窗口的消息，因为是自己窗口，所以为null
  UINT  wMsgFilterMin,过滤函数 消息是有值的WM_开头（如：0x0200）   数值的给0 接受任何消息
  UINT  wMsgFilterMax 过滤函数
);
	*/
	//测试：--------------------------
	//3.对于游戏而言不需要阻塞
	//peekMessage不停的返回，不分析消息类别 得到消息返回true,没有得到消息返回FALSE 非阻塞
	//实例：
	memset(&msg, 0, sizeof(msg));
	while (msg.message!=WM_QUIT)//因为peekMessage是非阻塞函数没有得到消息返回FALSE，所以采用这样的模型
	{
		if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))//PeekMessage实际上是从队列里面拷贝，所以需要参数PM_REMOVE让消息从队列里面移除
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//是不是快捷键消息
			{
				TranslateMessage(&msg);//翻译消息，比如键盘按下
				DispatchMessage(&msg);//投递消息，应用程序往内部传递消息使用，投递给窗口消息处理函数WndProc进行处理，重要！
									  //比如关闭窗口这个动作首先在消息队列产生(windows封装)，接着GetMessage()取出，然后DispatchMessage()进行投递处理消息
			}
		}
	}
	//-------------------如果是做游戏开发的话，不需要快捷键、菜单对话框，可以取资源视图对应的文件夹下删除，图标可以在资源视图或者注册窗口时的 wcex.hIconSm下面修改
    return (int) msg.wParam;//这里为什么只需要return msg.wParam
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。 先注册QQ号再使用QQ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;//WNDCLASS EXW为unicode扩展类型  wcex窗口类对象

    wcex.cbSize = sizeof(WNDCLASSEX);//类前索引

    wcex.style          = CS_HREDRAW | CS_VREDRAW;//类风格 screen垂直刷新，水平刷新   另外鼠标双击需要CS_DBLCLKS风格支持 
    wcex.lpfnWndProc    = WndProc;//1.WndProc是一个函数指针 把它赋值给wcex.lpfnWndProc  当使用wcex.lpfnWndProc相当于使用WndProc 2.WndProc是回调函数 
	//3.在注册类信息的时候告诉操作系统，如果窗口发生事件，交给WndProc操作
    wcex.cbClsExtra     = 0;//窗口类的额外信息
    wcex.cbWndExtra     = 0;//窗口的额外信息
    wcex.hInstance      = hInstance;//当前实例写入注册
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_TEST));//1.图标修改  2.MAKEINTRESOURCE把IDI_TEACH_WIN32_TEST=107转化成字符串
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);//当前光标形状
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);//默认背景窗口颜色
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_TEST);
    wcex.lpszClassName  = szWindowClass;//1.窗口类名 2.函数指针 3.相当于使用szWindowClass这个函数
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));//1.图标修改 更方便

    return RegisterClassExW(&wcex);//真正的系统函数，注册窗口类  相当于类里面的内部private函数 把窗口类对象传入API进行注册 若注册成功返回ATOM类型的值(unsigned short)
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   HWND hWnd;
	//测试：不让窗口双开-----------
   hWnd = FindWindow(szWindowClass, szTitle);//如果已经找到了窗口就return FALSE，因此不会绘制第二个窗口
   if (hWnd)
   {
	   return FALSE;
   }
   //-----------------------
   
   //窗口句柄
   hWnd = CreateWindowW(szWindowClass,//已注册窗口类名 相当于类有一个名字
	   szTitle,//窗口标题栏
	   WS_OVERLAPPEDWINDOW,//窗口的风格
       CW_USEDEFAULT, //起始创建X位置（窗口的左上角坐标）(x,y)1920*1080表示，若为CW_USEDEFAULT，后面的y会随着横纵比自动匹配
	   0, //Y轴位置
	   CW_USEDEFAULT,//窗口的宽度x方向
	   0,//窗口的高度，y方向
	   nullptr,//父窗口句柄在A窗口打开了B窗口
	   nullptr,//窗口的菜单句柄，如果NULL会用注册的菜单句柄，如果不为null会用这个参数表示的菜单句柄HMENU hmenu=CreateMenu();如果CreateMenu()里面没有传入参数，那么窗口没有菜单
	   hInstance,//实例句柄
	   nullptr//窗口辅助信息，一般null
   );
   //测试：隐藏光标---
  // ShowCursor(false);
   //----------------
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);//API函数 显示窗口
   UpdateWindow(hWnd);//更新窗口

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//WndProcess 窗口过程/加工函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//处理消息，因为是进队列，然后从队列里面取，所以msg里面的消息产生的时间和产生的绝对位置不需要
{
    switch (message)//消息ID匹配
    {
	//测试：----------------
	case WM_ACTIVATE://激活窗口消息，1.鼠标激活2.非鼠标激活 3.取消窗口激活
	{
		switch (wParam)//基本是wParam用的多，表示鼠标的位置
		{

		case WA_CLICKACTIVE://WA为取窗口激活的前两个字母
		{
			HDC hdc = GetDC(hWnd);
			static int j1 = 20;//声明一个函数内部的静态变量，生命周期为进程周期，作用域为函数，j这个函数下次用到的时候还是上次那个j
							  //MessageBox(0, _T("鼠标按下"), _T("标题"), 0);
			TextOut(hdc, 300, j1, _T("鼠标激活"), 4);//表示在窗口的(0,j)位置显示文字,4表示字符的个数，1.过短显示不全 2.过长尾部乱码 3.对应字符个数
			ReleaseDC(hWnd, hdc);
			j1 += 20;
		}
		break;
		case WA_ACTIVE://非鼠标激活
		{
			HDC hdc = GetDC(hWnd);
			static int j2 = 20;//声明一个函数内部的静态变量，生命周期为进程周期，作用域为函数，j这个函数下次用到的时候还是上次那个j
							  //MessageBox(0, _T("鼠标按下"), _T("标题"), 0);
			TextOut(hdc, 450, j2, _T("非鼠标激活"), 5);//表示在窗口的(0,j)位置显示文字,4表示字符的个数，1.过短显示不全 2.过长尾部乱码 3.对应字符个数
			ReleaseDC(hWnd, hdc);
			j2 += 20;
		}
		break;
		case WA_INACTIVE://取消窗口激活
		{
			HDC hdc = GetDC(hWnd);
			static int j3 = 20;//声明一个函数内部的静态变量，生命周期为进程周期，作用域为函数，j这个函数下次用到的时候还是上次那个j
							  //MessageBox(0, _T("鼠标按下"), _T("标题"), 0);
			TextOut(hdc, 550, j3, _T("取消窗口激活"), 6);//表示在窗口的(0,j)位置显示文字,4表示字符的个数，1.过短显示不全 2.过长尾部乱码 3.对应字符个数
			ReleaseDC(hWnd, hdc);
			j3 += 20;
		}
		break;

		}
	}
	break;
	//测试：--------------
	//WM开头的是windows消息，有人为产生的消息也有系统产生的消息 比如WM_CREATE就是系统产生的消息
	case WM_CREATE: //相当于类的构造函数，不给出时，系统会给你默认的函数 窗口初始化模块的hWnd = CreateWindowW()执行后会调转到这里进行窗口的创建，只会进入一次
	{
		//表示窗口创建成功，在显示之前
		//所以这里可以做数据的加载1
	}
	break;
	//测试：鼠标移动显示坐标位置---
	case WM_MOUSEMOVE:
	{
		HDC hdc = GetDC(hWnd);
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		TCHAR arr[128] = { 0 };
		_stprintf_s(arr, L"x=%d,y=%d", x, y);
		
		TextOut(hdc, 0, 0,arr,_tcslen(arr));//通配_tcslen能求TCHAR字符的长度,重要 
		ReleaseDC(hWnd, hdc); 
		//下面为_tcslen以及wchar_t的测试
		const wchar_t* a=L"sss";
		_tcslen(a);
		//待解决：为什么y的值是相反的
	}
		break;
		//------------
		//测试：按键和点鼠标产生消息-----
	case WM_LBUTTONDOWN:
	{
		//测试：同步阻塞
		//SendMessage(hWnd, WM_KEYDOWN, 0, 0);//发送消息函数,介绍：1.以递归的方式进行该消息的处理2.发送给hWnd当前窗口一个WM_KEYDOWN的消息3.没有辅助信息4.效果：相当于键盘按下
		//测试：异步非阻塞
		PostMessage(hWnd, WM_KEYDOWN, 0, 0);//发送消息函数,介绍：1.向队列发送一个WM_KEYDOWN消息2.由当前窗口从队列中按顺序获得WM_KEYDOWN的消息3.没有辅助信息4.效果：排队进入队列等待被获取
		Sleep(2000);
		HDC hdc = GetDC(hWnd);
		static int j = 20;//声明一个函数内部的静态变量，生命周期为进程周期，作用域为函数，j这个函数下次用到的时候还是上次那个j
		//MessageBox(0, _T("鼠标按下"), _T("标题"), 0);
		TextOut(hdc, 0, j, _T("鼠标按下"), 4);//表示在窗口的(0,j)位置显示文字,4表示字符的个数，1.过短显示不全 2.过长尾部乱码 3.对应字符个数
		ReleaseDC(hWnd, hdc);
		j += 20;
	}
	break;
	case WM_KEYDOWN:
	{
		HDC hdc = GetDC(hWnd);
		static int k = 20;//声明一个函数内部的静态变量，生命周期为进程周期，作用域为函数，j这个函数下次用到的时候还是上次那个j
						  //MessageBox(0, _T("鼠标按下"), _T("标题"), 0);
		TextOut(hdc, 200, k, _T("键盘按下"), 4);//表示在窗口的(0,j)位置显示文字,4表示字符的个数，1.过短显示不全 2.过长尾部乱码 3.对应字符个数
		ReleaseDC(hWnd, hdc);
		k += 20;
		//MessageBox(0, _T("键盘按下"), _T("标题"), 0);
	}
	break;
	//------------------
	//作业：弹出一个对话框，需要点击10次，程序才能结束---------
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		static int i = 1;//声明一个函数内部的静态变量，生命周期为进程周期，作用域为函数，j这个函数下次用到的时候还是上次那个j
						  //MessageBox(0, _T("鼠标按下"), _T("标题"), 0);
		TCHAR str[100] = { 0 };//临时字符串数组  char为多字节  TCHAR为宽字节类型
								  //格式化字符串
		_stprintf_s(str, _T("鼠标按下%d次"), i);//1.swprintf_s适用于宽字节buff对象 2.一般用spirntf就行 3._stprintf_s为通配
		TextOut(hdc, 0, 20, str, _tcslen(str));//表示在窗口的(0,j)位置显示文字,4表示字符的个数，1.过短显示不全 2.过长尾部乱码 3.对应字符个数 通配_tcslen能求TCHAR字符的长度4.同一位置会覆盖原来的字
		ReleaseDC(hWnd, hdc);
		if (i == 10)
		{
			MessageBox(hWnd, TEXT("鼠标已经点击了10次"), L"标题", 0);
		}
		i++;
	}
	break;
	//-----------------
    case WM_COMMAND://命令消息，比如点击菜单就是命令消息
        {
            int wmId = LOWORD(wParam);//得到是哪个菜单/哪个命令
            // 分析菜单选择: 
            switch (wmId)
            {
				/*
				附录：资源视图的查看(需要在Resource.h关闭的情况下)，视图--其他窗口--资源视图
				进入Menu文件夹 双击下面的文件 打开菜单类视图
				对准菜单项点击右键就可以看到该菜单的所有属性
				*/
            case IDM_ABOUT: //关于
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT: //退出
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);//系统给出的windows窗口消息处理函数，比如窗口的最大化、最小化
            }
        }
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY: //IDM_EXIT消息匹配后会调用PostQuitMessage函数销毁消息
        PostQuitMessage(0);//往队列里面post一个WM_QUIT消息使得GetMessage/PeekMessage得到该消息后退出
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
