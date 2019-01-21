// teach_win32_Control1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "teach_win32_Control1.h"

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
HWND g_hDlogWnd;//全局对话框句柄
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
    LoadStringW(hInstance, IDC_TEACH_WIN32_CONTROL1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_CONTROL1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_CONTROL1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_CONTROL1);
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
//
//控件表示的是用户输入（缩小用户的输出范围）
//可以使用对话框承载控件
//可以在资源视图Dialog属性caption里面修改控件显示内容
//对话框是用于用户输入，进行控件布局
//对话框分为两种：
/*
1.模态对话框： 阻塞（同步）模式
2.非模态对话框 非阻塞(异步)模式
*/
//对话框的创建步骤：
/*
1.添加对话框资源（在资源中于添加对话框）
2.调用函数创建对话框（非阻塞对话框创建：CreateDialog()，阻塞对话框创建：DialogBox()）
3.对话框回调处理函数
4.释放对话框
*/
INT_PTR CALLBACK myDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);//前向对话框声明
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_RBUTTONDOWN:
	{
		//对话框创建方法 对话框有没有动态创建的方法，待解决
		g_hDlogWnd=CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1),hWnd,myDialogProc );//创建一个非阻塞的对话框，返回HWMD
		ShowWindow(g_hDlogWnd, SW_SHOWNORMAL);//创建非阻塞对话框之后要用showWindow显示
		/*
		BOOL ShowWindow(
  HWND hWnd,
  int  nCmdShow显示方式
);
		*/
	}
	break;
	case WM_LBUTTONDOWN:
	{
		//MessageBox(hWnd, 0, 0, 0);//阻塞/同步模式，表示只有在当前对话框操作完成后才能操作主窗口
		//静态对话框创建方法
		DialogBox(hInst,//应用程序实例句柄
			MAKEINTRESOURCE(IDD_DIALOG1),//控件名：通过对话框的ID利用MAKEINTRESOURCE()函数制造一个名字
			hWnd,//父创就句柄
			About//对话框的消息处理函数，回调函数
		);//弹出一个阻塞菜单
		/*
		INT_PTR WINAPI DialogBox(
  _In_opt_ HINSTANCE hInstance,
  _In_     LPCTSTR   lpTemplate,
  _In_opt_ HWND      hWndParent,
  _In_opt_ DLGPROC   lpDialogFunc
);
		*/
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)//响应菜单ID
            {
            case IDM_ABOUT: //关于菜单
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);//弹出一个阻塞对话框，返回INT
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
    UNREFERENCED_PARAMETER(lParam);//安全等级
    switch (message)
    {
    case WM_INITDIALOG://初始化对话框（对比WM_CREATE）
        return (INT_PTR)TRUE;

    case WM_COMMAND://控件命令消息
        if (LOWORD(wParam) == IDOK /*确定*/|| LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));//结束对话框，阻塞对话框释放方式
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;//没有操作返回FALSE
}
TCHAR str[1024] = { 0 };
//自己的对话框处理函数
INT_PTR CALLBACK myDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);//安全等级
	switch (message)
	{
	case WM_INITDIALOG://初始化对话框时(参照WM_CREATE)，动态控件创建方法
	{
		//控件也是一个窗口
		//下压式按钮
		CreateWindow(_T("Button"),//是控件类名,其中Button是一个基类
			_T("生成"),//控件窗口名
			WS_CHILD | WS_VISIBLE|BS_PUSHBUTTON,//子窗口|可见|使用基类button的一个风格
			10, 10,//控件位置
			100, 30,//宽x，高y
			hDlg,//控件的父窗口句柄
			(HMENU)5001,//系统设置的控件ID号,对比静态控件里面的控件ID号
			hInst,//实例句柄
			nullptr//辅助信息 
		);
		//组框：显示信息 组框的基类也是Button，可以f12查看派生类类型
		CreateWindow(_T("Button"),_T("调察问卷"),WS_CHILD | WS_VISIBLE | BS_GROUPBOX,10, 50,650, 200,hDlg,(HMENU)5002,hInst,nullptr);
		//一栏：成员
		//静态文本：给用户显示信息 基类Static，基类名可以在控件工具箱中查看
		CreateWindow(_T("Static"), _T("家庭成员"), WS_CHILD | WS_VISIBLE , 20, 70, 60, 20, hDlg, (HMENU)5003, hInst, nullptr);
		//单选框，基类Button，派生选BS_AUTORADIOBUTTON 分组为WS_GROUP 直到下个WS_GROUP前这些单选框为一组
		CreateWindow(_T("Button"), _T("宝宝"), WS_CHILD | WS_VISIBLE| BS_AUTORADIOBUTTON|WS_GROUP, 20, 90, 50, 30, hDlg, (HMENU)6001, hInst, nullptr);
		CreateWindow(_T("Button"), _T("爸爸"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 120, 50, 30, hDlg, (HMENU)6002, hInst, nullptr);
		CreateWindow(_T("Button"), _T("妈妈"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 150, 50, 30, hDlg, (HMENU)6003, hInst, nullptr);
		//二栏：学历
		//静态文本：给用户显示信息 基类Static，基类名可以在控件工具箱中查看
		CreateWindow(_T("Static"), _T("学历"), WS_CHILD | WS_VISIBLE, 300, 70, 60, 20, hDlg, (HMENU)5004, hInst, nullptr);
		//单选框，基类Button，派生选BS_AUTORADIOBUTTON 分组为WS_GROUP 直到下个WS_GROUP前这些单选框为一组
		CreateWindow(_T("Button"), _T("大专"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 300, 90, 50, 30, hDlg, (HMENU)6004, hInst, nullptr);
		CreateWindow(_T("Button"), _T("本科"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 300, 120, 50, 30, hDlg, (HMENU)6005, hInst, nullptr);
		CreateWindow(_T("Button"), _T("研究生"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 300, 150, 70, 30, hDlg, (HMENU)6006, hInst, nullptr);
		//三栏：兴趣爱好
		//静态文本：给用户显示信息 基类Static，基类名可以在控件工具箱中查看
		CreateWindow(_T("Static"), _T("兴趣爱好"), WS_CHILD | WS_VISIBLE, 560, 70, 60, 20, hDlg, (HMENU)5005, hInst, nullptr);
		//复选框，基类Button，派生选BS_AUTOCHECKBOX 
		CreateWindow(_T("Button"), _T("画画"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX , 560, 90, 50, 30, hDlg, (HMENU)6007, hInst, nullptr);
		CreateWindow(_T("Button"), _T("看书"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 560, 120, 50, 30, hDlg, (HMENU)6008, hInst, nullptr);
		CreateWindow(_T("Button"), _T("写代码"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 560, 150, 70, 30, hDlg, (HMENU)6009, hInst, nullptr);

		//编辑框，输入文字，基类：edit  风格WS_BORDER为边框 多行怎么改风格 multiline设置多行 待解决已解决ES_MULTILINE
		CreateWindow(_T("Edit"), _T("统计结果"), WS_CHILD | WS_VISIBLE|WS_BORDER| ES_MULTILINE, 10, 260, 200, 100, hDlg, (HMENU)6010, hInst, nullptr);
		//调察问卷的结果怎么保存或着说是录入，待解决

		//设置默认的控件
		//可以通过向系统投递消息来完成SendMessage()递归  PostMessage()同步
		//上面并没有主动地设置变量来保存子控件的窗口句柄，因为子控件很多，仅仅通过窗口句柄很烦
		//使用GetDlgItem来获得控件的句柄，投递BM_SETCHECK消息来设置默认的选项
		SendMessage(GetDlgItem(hDlg, 6001), BM_SETCHECK, 1, 0);
			/*获得控件的句柄
			HWND GetDlgItem(
			HWND hDlg,//哪一个对话框
			int  nIDDlgItem//控件ID
			);
			*/
		/*向系统投递消息
		LRESULT SendMessage(
		HWND   hWnd,
		UINT   Msg,
		WPARAM wParam,//一般的消息辅助鼠标消息放在wParam里面 ，1表示点击
		LPARAM lParam
		);
		*/
		SendMessage(GetDlgItem(hDlg, 6004), BM_SETCHECK, 1, 0);
	}
	return (INT_PTR)TRUE;

	case WM_COMMAND://控件命令消息
		switch (LOWORD(wParam))//响应鼠标点击消息,对应控件ID号
		{
		case 5001://选中这个控件时执行
			
			//---第一栏统计
			_tcscpy_s(str, _T("家庭成员:"));//向字符串中拷贝一行文字
			if (IsDlgButtonChecked(hDlg, 6001))//IsDlgButtonChecked()判断某一个按钮是否被选中
				_tcscat(str, _T("宝宝"));
			else if (IsDlgButtonChecked(hDlg, 6002))
				_tcscat(str, _T("爸爸"));
			else if (IsDlgButtonChecked(hDlg, 6003))
				_tcscat(str, _T("妈妈"));
			//---第二栏统计
			_tcscat(str, _T("  学历："));
			if (IsDlgButtonChecked(hDlg, 6004))
				_tcscat(str, _T("大专"));
			else if (IsDlgButtonChecked(hDlg, 6005))
				_tcscat(str, _T("本科"));
			else if (IsDlgButtonChecked(hDlg, 6006))
				_tcscat(str, _T("研究生"));
			//---第三栏统计
			_tcscat(str, _T("  兴趣爱好："));
			if (IsDlgButtonChecked(hDlg, 6007))
				_tcscat(str, _T("画画 "));
			if (IsDlgButtonChecked(hDlg, 6008))
				_tcscat(str, _T("看书 "));
			if (IsDlgButtonChecked(hDlg, 6009))
				_tcscat(str, _T("写代码 "));

			//把统计出来的消息发送到对话框中
			SetDlgItemText(hDlg, 6010, str);
			//成功生成
			MessageBox(0, _T("成功生成"), 0, 0);
			SetDlgItemText(hDlg, 6005, _T("更改"));//通过点一下生成后某个控件的名字标签改动
			break;
		}

		if (LOWORD(wParam) == IDOK /*确定*/ || LOWORD(wParam) == IDCANCEL)
		{
			DestroyWindow(g_hDlogWnd);//非阻塞对话框释放方式
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;//没有操作返回FALSE
}
//控件也是一个窗口(子窗口，必须有一个父窗口)
//控件也可以有消息
//控件的窗口类已经在系统中定义害了，直接用
//多种控件按钮在视图--工具箱中有（有对齐操作） 静态添加方式