// teach_win32_GDI 1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "teach_win32_GDI 1.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEACH_WIN32_GDI1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_GDI1));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_GDI1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);//客户区背景
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_GDI1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
//GDI图形设备接口（图形库） Graphics Device Interface  
//GDI的主要任务是负责系统与绘图程序之间的信息交换
//GDI是一个工具箱子，里面有很多函数
/*
1.取得和释放设备上下文的函数，设备上下文也叫做设备环境DC 给WINDOWS一个绘制指令，执行这个指令有关的硬件、软件驱动、内存都叫设备上下文
2.取得有关设备内容信息的函数
3.绘图函数
4.设定和取得设备上下文参数的函数
5.调用GDI对象的函数
*/
//GDI可以操作的图形
/*
1.画线
2.填充区域
3.显示文字
4.显示图片
*/
//GDI画图形的步骤：
//不需要知道使用显卡的哪个驱动，也不需要知道需要给驱动穿那个参数，只需要给Windows下指令，让windows系统函数来完成就行
/*
1.得到设备环境句柄 HDC
2.修改设备属性 比如：红色的线、绿色的线
3.绘图
4.释放设备环境句柄
*/
//win32里面有两种方法得到设备环境句柄(指的是客户区的设备环境句柄）
/*
1.在WN_PAINT消息里面 HDC hdc = BeginPaint(hWnd, &ps);得到设备环境的句柄，通过EndPaint(hWnd, &ps);来释放设备环境句柄
	应用程序接受WN_PAINT消息有两种情况：1、窗口最初创建时绘制 2.窗口出现无效区域时绘制-->a.窗口移动或大小发生改变 窗口隐藏后重新显示 b.invalidateRect(使矩形区域失效)invalidateRgn（使区域失效）以画图程序为例 c.ScrollWindow（滚动窗口）ScrollDC（滚动设备客户区）
	有4中情况不会产生WN_PAINT消息 ：1.光标穿越客户区2.图标拖过客户区3.显示对话框4.显示菜单后释放  其实客户区内有多个叠层
2.在WM_PAINT消息之外，通过GetDC来得到设备环境句柄，通过releaseDC来释放设备环境句柄 比如说在WM_LBUTTONDOW中响应绘图消息 或者计时器消息里面WM_TIMER绘图
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	//----GDI测试
	case WM_LBUTTONDOWN:
	{
		//GDI画笔
		//WM_PAINT消息之外
		HDC hdc = GetDC(hWnd);//得到设备环境句柄
		//A.修改设备属性 这里选择不修改设用设备默认的属性
		//B.--选择修改画笔---
		//HPEN hpen = nullptr;
		//hpen = (HPEN)GetStockObject(WHITE_PEN);//得到系统预设的GDI对象  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);//客户区背景调为灰
		//SelectObject(hdc, hpen);//修改设备属性
		//----------
		//C.---选择自定义画笔
		HPEN hpen = CreatePen(PS_SOLID,//画笔的风格
		2,//画笔的宽度，如果画笔的宽度大于1不管什么线条风格都会变为实线风格
		//win32用32位来表示颜色4个char（颜色通道argb，a表示透明，透明的意思是前景色和背景色一致）	
			RGB(255, 0, 0));//WINGDIAPI HPEN    WINAPI CreatePen( _In_ int iStyle, _In_ int cWidth, _In_ COLORREF color); COLORREF为4字节的整数
		//RGB(r, g, b);//#define RGB(r,g,b) 带参宏         ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))) 形成BGR的位置 所以红色也可以使用0xff来表示同理绿色0xff00 蓝色0xff0000
		SelectObject(hdc, hpen);//修改设备属性
		MoveToEx(hdc,50,50,nullptr);//把画笔移动到某个点，用于设置画笔的起点
		/*
		BOOL MoveToEx(
  HDC     hdc,
  int     x,
  int     y,
  LPPOINT lppt
);
		*/
		LineTo(hdc, 100, 100);//表示画线到hdc客户区的100，100位置处，如果没有指定起点，默认从0，0开始画
		//--释放
		DeleteObject(hpen);//释放修改的设备属性，释放掉hpen在SelectObject的占用内存

		//如果选择不同颜色的线段/不同粗细需要在GDI里面重新创建画笔对象
		HPEN hpen1 = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
		SelectObject(hdc, hpen1);//修改设备属性
		LineTo(hdc, 200, 300);
		DeleteObject(hpen1);


		ReleaseDC(hWnd, hdc);//释放设备环境句柄

	}
	break;
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);//得到设备环境句柄
		HPEN hpen = CreatePen(PS_SOLID, 2, 0xff0000);
		SelectObject(hdc, hpen);
		//在程序中画圆需要指定外接矩形的大小
		Arc(hdc,100,100,400,400,0,0,250,600);//画圆弧（逆时针绘制）
		/*
		BOOL Arc(
		HDC hdc,
		int x1,//矩形
		int y1,//矩形
		int x2,//矩形
		int y2,//矩形
		int x3,//圆弧的起点 可以在圆外（内），从这个点到圆心的连线（延长线）与圆的交点为起点
		int y3,//圆弧的起点
		int x4,//圆弧的终点  可以在圆外（内），从这个点到圆心的连线（延长线）与圆的交点为终点
		int y4//圆弧的终点
		);

		*/
		DeleteObject(hpen);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_KEYDOWN:
	{
		//画点
		HDC hdc = GetDC(hWnd);
		HPEN hpen = CreatePen(PS_SOLID, 2, 0xff);
		SelectObject(hdc, hpen);
		for (int i = 0; i < 100; ++i)
			SetPixel(hdc, 500 + i, 500, 0xff);//设置像素点
		for (int j = 0; j < 100; ++j)
			SetPixel(hdc, 500 + j, 600, GetPixel(hdc, 500 + j, 500));//复制像素点->复制图片->放大镜也行
		/*
		COLORREF SetPixel(
  HDC      hdc,
  int      x,
  int      y,
  COLORREF color
);
		*/
		DeleteObject(hpen);
		ReleaseDC(hWnd, hdc);
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
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
    case WM_DESTROY:
        PostQuitMessage(0);
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
