// teach_win32_GDI 3.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "teach_win32_GDI 3.h"
#pragma comment (lib,"Msimg32.lib")//用于TransparentBlt函数
#pragma comment (lib,"Winmm.lib")//用于timeGetTime函数
#include <TimeAPI.h>//用于timeGetTime函数
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

//因为需要在消息循环中有一个窗口句柄，所以需要一个全局的窗口句柄
HWND g_hWnd;//全局变量 在窗口初始化里面BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)赋值
int heroFrame = 0;//表示当前英雄动画的哪一个帧
//英雄起始位置
int heroX ;
int heroY ;
//英雄的朝向
int heroDir;
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
    LoadStringW(hInstance, IDC_TEACH_WIN32_GDI3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_GDI3));

    MSG msg;

    // 主消息循环: 
   /* while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
	//资源的初始化 为啥选择这个位置？因为这里窗口已经初始化了，可以使用全局的窗口句柄了g_hWnd
	//资源部分-----
	//[总]创建一个主设备环境句柄
	HDC hdc = GetDC(g_hWnd);
	//为了解决闪屏的问题，准备一个辅助DC形成双缓冲
	HDC buffDc = CreateCompatibleDC(hdc);//创建一个和主DC兼容的缓冲DC
	HBITMAP buffBitmap = CreateCompatibleBitmap(hdc, 1024, 768);//创建一个缓冲位图，和主DC兼容
	SelectObject(buffDc, buffBitmap);//将缓冲位图关联进缓冲DC
	
	//加载背景位图---------------
	//1.先创建一个辅助设备环境，作用是加载背景图片
	HDC bkDc = CreateCompatibleDC(hdc);//参数需要主dc，主设备环境，因此上面先要创建一个主设备环境句柄
	//2.加载位图 LoadImage 加载位图，光标，图标
	HBITMAP bkBitmap = (HBITMAP)LoadImage(hInst,_T("bk.bmp"), IMAGE_BITMAP,
		0,0,//加载图像的宽度和高度，如果为0则默认设为图像的原始宽度
		LR_LOADFROMFILE//表示从文件加载
	);//hinst也是在窗口初始化以后赋了值，因此很多逻辑和渲染的操作都要放在初始化窗口之后,因为LoadImage返回的是一个HANDLE，是一个句柄，相当于void，所以可以进行强转
	//3关联bkbitmap位图
	SelectObject(bkDc,bkBitmap);//从bkDc中关联bkbitmap位图
	//------------------
	//加载英雄位图------------
	//1.先创建一个英雄辅助设备环境
	HDC heroDc = CreateCompatibleDC(hdc);
	//2.加载位图
	HBITMAP heroBitmap = (HBITMAP)LoadImage(hInst, _T("hero.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//3.关联heroBitmap位图
	SelectObject(heroDc, heroBitmap);

	ReleaseDC(g_hWnd, hdc);//先释放这个主设备环境 
	//英雄起始位置
	heroX = 200;
	heroY = 400;
	//资源部分-----------------
	memset(&msg, 0, sizeof(msg));
	//改为非阻塞接收消息
	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//是不是快捷消息
			{
				TranslateMessage(&msg);//翻译消息，比如键盘按下
				DispatchMessage(&msg);//往窗口内部投递消息
			}
		}
	//因为非阻塞在一直接收消息这里进行逻辑和渲染
		//绘制部分--------
		//1.重新获得设备环境句柄
		HDC hdc = GetDC(g_hWnd);
		//----------为了解决缓存区域中的图片残留问题，使用黑色画刷刷一下
		RECT r = { 0,0,1024,768 };
		HBRUSH hr = CreateSolidBrush(0x00);//生成一个画刷对象
		FillRect(buffDc, &r, hr);//填充r所表示的矩形区域
		DeleteObject(hr);//释放画刷
		//----------
		//2.绘制部分,绘制背景
		//BitBlt(hdc,//目标DC
		//	0, 0,//目标的左上角xy坐标，相当于视窗的位置
		//	1024, 768, //目标视窗的宽高
		//	bkDc,//资源DC 
		//	0, 0,//资源的左上角xy坐标，贴图的位置
		//	SRCCOPY//把资源从资源DC拷贝到目标DC
		//);
		////绘制部分，绘制英雄
		//BitBlt(hdc, 0, 0, 1024, 768, heroDc, 0, 0, SRCCOPY);
		////问题：会出现闪屏 由于不是一起画出来的原因会出现先后画(刷新率不一致)，因此会出现闪屏，所以一起画出来能解决闪屏的问题，也就是双缓冲机制
		//防止闪频的双缓冲机制
		//2.绘制部分，新
		BitBlt(buffDc, 0, 0, 1024, 768, bkDc, 0, 0, SRCCOPY);//把bkDc的内容画入缓冲buffdc里面
		//BitBlt(buffDc, 0, 0, 1024, 768, heroDc, 0, 0, SRCCOPY); //把heroDc的内容画入缓冲buffdc里面,但是会出现覆盖
		TransparentBlt(buffDc, 
			heroX, heroY, //目标区域 xy坐标位置
			90, 88,//目标区域的范围
			heroDc, 
			heroFrame*90, heroDir*88,//表示资源显示到目标区域的位置
			90, 88, //表示选取帧动画的里的大小，如果与目标区域的大小不一致，则会缩放
			RGB(255,255,255));//注意这里面要写帧动画的实际大小，RGB(255,255,255)表示透明的部分为白色
		BitBlt(hdc, 0, 0, 1024, 768, buffDc, 0, 0, SRCCOPY);//把buffDc的内容画入缓冲hdc里面
		
		//进行计时操作
		static float beginTimer = timeGetTime() / 1000.0f;//1.静态的开始时间,除以1000后得到秒 2.该beginTimer只初始化一次
		float endTimer = timeGetTime() / 1000.0f;
		if (endTimer - beginTimer >= 0.5)//如果大于0.5秒，相当于一个计时器，但计时器是开了线程的
		{
			//让heroFrame在0-3之间循环-----
			heroFrame++;
			if (heroFrame == 4)
				heroFrame = 0;
			//-------------
			beginTimer = endTimer;
			//注意sleep是多线程用的不建议在单线程使用
			
		}
		//3.释放设备环境
		ReleaseDC(g_hWnd, hdc);
		//绘制部分------------
	}
	//释放hero位图和hero辅助设备环境
	DeleteObject(heroBitmap);
	DeleteDC(heroDc);
	//释放bk位图和bk辅助设备环境
	DeleteObject(bkBitmap);
	DeleteDC(bkDc);
	//释放缓存位图和缓存辅助设备环境
	DeleteObject(buffBitmap);
	DeleteDC(buffDc);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_GDI3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_GDI3);
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
      CW_USEDEFAULT, 0, 960, 640, nullptr, nullptr, hInstance, nullptr);//调整窗口大小设置成背景图像大小
   g_hWnd = hWnd;//用于对全局变量赋值
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
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'W':
		case VK_UP:
		{
			if (heroX > 0 && heroY > 0)
			{
				heroX--;
				heroY--;
				heroDir = 3;
			}
		}
		break;
		case 'S':
		case VK_DOWN:
		{
			if (heroX < 880 && heroY < 500)
			{
				heroX++;
				heroY++;
				heroDir = 0;
			}
		}
		break;
		case 'A':
		case VK_LEFT:
		{
			if (heroX > 0 && heroY < 500)
			{
				heroX--;
				heroY++;
				heroDir = 1;
			}
		}
		break;
		case 'D':
		case VK_RIGHT:
		{
			if (heroX < 880 && heroY >0)
			{
				heroX++;
				heroY--;
				heroDir = 2;
			}
		}
		break;
		}
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
