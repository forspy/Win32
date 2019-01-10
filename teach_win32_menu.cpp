// teach_win32_menu.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "teach_win32_menu.h"

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
    LoadStringW(hInstance, IDC_TEACH_WIN32_MENU, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_MENU));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_MENU));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_MENU);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
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
HMENU hMenu;//定义一个菜单句柄
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
	//第2种创建静态菜单的方式
   /*HMENU hMenu;
   hMenu=LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));*/
	//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); MAKEINTRESOURCE(IDI_SMALL)是LPCWSTR类型的是一个字符串指针类型
	   /*
	   LoadMenuW(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCWSTR lpMenuName);
	   */
   //动态菜单的创建方式
  
   hMenu = CreateMenu();//创建一个空的菜单，并且返回这个菜单的句柄 理解为一个二级指针
   //尾部添加菜单项
   AppendMenu(hMenu,//指明在哪一个菜单的尾部进行追加
	   0,//风格
	   5001,//菜单项ID，不进资源但是在消息菜单命令中能够使用
	   _T("测试文件"));
	   /*
	   AppendMenuW 
    _In_ HMENU hMenu,
    _In_ UINT uFlags,
    _In_ UINT_PTR uIDNewItem,
    _In_opt_ LPCWSTR lpNewItem);
	   */ 
   AppendMenu(hMenu,0,5002,_T("新建"));
   
   //子菜单的添加方法
   HMENU hMenu1= CreateMenu();
   AppendMenu(hMenu1, 0, 5003, _T("文件"));
   AppendMenu(hMenu1, 0, 5004, _T("保存"));
   //在把新的菜单追加到后面去,风格为MF_POPUP 表示能弹出菜单
   AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu1, _T("新建下拉(&F)"));

   //在指定位置插入菜单的方法  (前插)
   HMENU hMenu2 = CreateMenu();
   InsertMenu(hMenu, 1, MF_BYPOSITION, 6001, _T("插入基于位置"));//基于位置的插入
   InsertMenu(hMenu, 5002, MF_BYCOMMAND, 6002, _T("插入基于命令"));//插入基于命令

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, /*nullptr*/hMenu, hInstance, nullptr);//将倒数第三个参数改为hMenu
   /*
   #define CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y,\
   nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\
   */
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
//菜单：对象
//静态菜单（构造的时候就创建）、动态菜单(在后面运行过程中赋值)、快捷菜单(预先编译好，响应右键消息时出现) 
//菜单是允许嵌套的 
/*
1.创建静态菜单 视图-其他窗口-资源视图 在menu文件夹下点击默认注册主窗口类名 进入修改
a.例如：保存(&S) 就可以设置快捷键
b.- 表示分割线
c.menu下面右键 插入menu创建新的menu
d.在注册窗口类里面 wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
e.静态菜单只能有一个
f.case ID_NEWFILE://在WM_COMMAND菜单消息  ID_NEWFILE是可以自己对菜单命名的
g.若要创建快捷键消息 需要在资源视图Accelerator里面设置
h.属性中enable为fasle则为非激活(变灰)
*/
HMENU g_hMenu;//右键菜单快捷键
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		//右键弹出菜单
	case WM_CREATE:
		g_hMenu = LoadMenu(hInst, MAKEINTRESOURCEW(IDR_MENU2));
		break;
	case WM_LBUTTONDOWN:
		EnableMenuItem(hMenu, 5003, MF_GRAYED);//点击左键变灰
		break;
	case WM_RBUTTONDOWN:
	{
		POINT point;
		point.x = LOWORD(lParam);//相对坐标
		point.y = HIWORD(lParam);
		//客户区坐标转换成屏幕坐标 相对坐标转化为绝对坐标
		ClientToScreen(hWnd, &point);
		//得到子菜单句柄
		HMENU h1 = GetSubMenu(g_hMenu, 0);
			/*
			ClientToScreen(
    _In_ HWND hWnd,
    _Inout_ LPPOINT lpPoint);//LPPOINT是一个指向POINT类型的指针
			*/
		//EnableMenuItem(hMenu, 5003, MF_ENABLED);//点击右键激活
		TrackPopupMenu(h1,//显示哪一个菜单
			TPM_LEFTALIGN,//右对齐显示 菜单的对其方式
			point.x,//x绝对坐标
			point.y,//y绝对坐标
			0,//必须为0
			hWnd,//当前窗口
			nullptr//默认
		);
	}
		break;
    case WM_COMMAND://菜单消息
        {
            int wmId = LOWORD(wParam);//在低位两字节保存着菜单项的ID
            // 分析菜单选择:  
            switch (wmId)
            {
			case ID_NEWFILE://响应菜单消息
				MessageBox(0, 0, 0, 0);
				break;
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
