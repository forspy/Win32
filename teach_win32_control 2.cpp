// teach_win32_control 2.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "teach_win32_control 2.h"

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
//---对话框模块
INT_PTR CALLBACK    dlgProc(HWND, UINT, WPARAM, LPARAM);//前向声明，回调函数
void createContorl(HWND hParentWnd);//创建一个控件
//----
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
    LoadStringW(hInstance, IDC_TEACH_WIN32_CONTROL2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_CONTROL2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_CONTROL2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_CONTROL2);
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
//控件：组合框
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_RBUTTONDOWN:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, dlgProc);//阻塞式对话框
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
TCHAR strArr[1024] = { 0 };
TCHAR Arr[1024] = { 0 };
INT_PTR CALLBACK dlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		createContorl(hDlg);//对话框初始化控件
		return (INT_PTR)TRUE;

	case WM_COMMAND://操作控件时启用
		switch (LOWORD(wParam))
		{
		case 7001://操作“添加数据”按钮时
			//获取文本框内容
			GetDlgItemText(hDlg, 6001, strArr, 1023);
			SetDlgItemText(hDlg, 8001, strArr);//往组合框显示部分设置文本
			//往组合框下拉列表部分投递文本，以尾部添加的方式CB_ADDSTRING，文本以LPARAM的方式传递
			//SendMessage(GetDlgItem(hDlg, 8001), CB_ADDSTRING, 0, (LPARAM)strArr);
			SendMessage(GetDlgItem(hDlg, 8001), CB_INSERTSTRING, 0, (LPARAM)strArr);//头部插入列表
			break;
		case 7002://操作“删除数据”按钮时
			//GetDlgItemText(hDlg, 8001, strArr, 1023);//获得组合框的文本
			//MessageBox(0, strArr, 0, 0);
			SendMessage(GetDlgItem(hDlg, 8001), CB_DELETESTRING, 0, (LPARAM)strArr);//删除组合框列表部分的第一项内容 CB_RESETCONTENT将删除列表中的所有元素
			break;
		case 7003://操作“得到工作路径”按钮时
			GetCurrentDirectory(1023,Arr);//得到绝对路径,在后面链接上名字形成路径也行
			SetDlgItemText(hDlg, 6002, Arr);//往文本框设置文本
			//MessageBox(0, Arr, L"工作路径", 0);
			break;
		case 7004:
			GetTempPath(1023, Arr);//得到临时路径
			SetDlgItemText(hDlg, 6002, Arr);//往文本框设置文本
			break;
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			//win32中实现文件操作
			//1.定义用于文件操作的句柄
			HANDLE hFile = nullptr;
			//2.创建文件
			hFile = CreateFile(_T("file.txt"), GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,nullptr, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);//类似于fopen和.open()为什么OPEN_ALWAYS会清空原有的字符 待解决 已解决
			//GENERIC_READ | GENERIC_WRITE表示可读可写
			/*
HANDLE CreateFileA(
  LPCSTR                lpFileName,//路径文件名（尽量使用相对路径名）
  DWORD                 dwDesiredAccess,//文件的访问属性
  DWORD                 dwShareMode,//共享读模式
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,//安全属性
  DWORD                 dwCreationDisposition,//文件创建方式
  DWORD                 dwFlagsAndAttributes,//文件属性，正常显示或者隐藏
  HANDLE                hTemplateFile
);
			*/
			//3.读写
			char s[1024] = "hello world!!你好ss";
			DWORD len = 0;
			//WriteFile(hFile,s,strlen(s),&len,nullptr);//写入文件的时候是以多字节写入的，而TCHAR是unicode款字节，即一个字符占两个字节所以只能写入一半，
			//所以推荐使用多字节写入文件，即s的类型为char
			char s1[1024] = { 0 };
			ReadFile(hFile, s1, 1023, &len, nullptr);//读入文件
			strcat_s(s, "连接");
			MessageBoxA(0, s1, 0, 0);//使用多字节显示
			WriteFile(hFile, s, strlen(s), &len, nullptr);
			/*
	BOOL WriteFile(
  HANDLE       hFile,//操作的文件句柄
  LPCVOID      lpBuffer,//写入的内容,字符串buff
  DWORD        nNumberOfBytesToWrite,//写入多少个字节
  LPDWORD      lpNumberOfBytesWritten,//写入的具体个数(准备输出)
  LPOVERLAPPED lpOverlapped
);
			*/
			//4.关闭文件句柄
			CloseHandle(hFile);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//创建一个控件
void createContorl(HWND hParentWnd)
{
	//创建单个控件
	CreateWindow(_T("static"), _T("请输入内容："), WS_CHILD | WS_VISIBLE, 10, 20, 100, 30, hParentWnd, (HMENU)5001, hInst, nullptr);//创建一个静态文本
	CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE|WS_BORDER | ES_MULTILINE, 120, 15, 300, 30, hParentWnd, (HMENU)6001, hInst, nullptr);//创建一个文本框
	CreateWindow(_T("button"), _T("添加数据"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 50, 100, 30, hParentWnd, (HMENU)7001, hInst, nullptr);//创建一个按钮
	CreateWindow(_T("button"), _T("删除数据"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 50, 100, 30, hParentWnd, (HMENU)7002, hInst, nullptr);//创建一个按钮
	//创建组合框，类名combobox  分为简单组合框CBS_SIMPLE 下拉式组合框CBS_DROPDOWN 下拉式列表组合框CBS_DROPDOWNLIST
	CreateWindow(_T("combobox"), _T("下拉式组合框"), WS_CHILD | WS_VISIBLE | WS_BORDER|CBS_DROPDOWN, 120, 100, 300, 200, hParentWnd, (HMENU)8001, hInst, nullptr);//注：下拉列表的高度要足够

	CreateWindow(_T("button"), _T("得到绝对路径"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 150, 100, 30, hParentWnd, (HMENU)7003, hInst, nullptr);//创建一个按钮
	CreateWindow(_T("button"), _T("得到临时路径"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 200, 100, 30, hParentWnd, (HMENU)7004, hInst, nullptr);//创建一个按钮
	CreateWindow(_T("edit"), _T("路径显示"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 120, 150, 300, 80, hParentWnd, (HMENU)6002, hInst, nullptr);//创建一个文本框

}
