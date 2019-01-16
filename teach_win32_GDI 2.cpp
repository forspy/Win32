// teach_win32_GDI 2.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "teach_win32_GDI 2.h"

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
	LoadStringW(hInstance, IDC_TEACH_WIN32_GDI2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_GDI2));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_GDI2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TEACH_WIN32_GDI2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
//GDI2 --画刷、文字、位图bmp
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONDBLCLK://右键双击
	{
		//GDI-位图
		//位图：二维数组存放一个图片的像素 每一个像素都有值 
		/*
		位图包含：文件头、信息头、彩色表、图像数据库阵列
		*/
		//png为矢量图 记录一个起点 终点 然后这个区间内颜色变化的规律，画的时候以计算 然后渲染 一般可压缩 缩放不失真
		//位图按照一层一层画上去比如有10张图就有10层
		HDC hdc = GetDC(hWnd);//设备环境句柄
		HDC srcDc1 = CreateCompatibleDC(hdc);//创建一个辅助DC把资源加载进来，因为要一层一层的画
											 //添加资源：在资源视图里面添加 方法：右键项目 添加资源 bitmap 选择新建 查看属性优先设置为24位以上
											 //然后使用照片查看器打开 ctrl c 然后在资源位图里面ctrl v
											 //左键点击图片就可以看到属性，需要在选择状态下
		HBITMAP srcBitmap1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));//从资源加载一张位图,会把位图的内容写入exe中，虽然生成exe较小 但不利于后期的修改
		SelectObject(srcDc1, srcBitmap1);//把srcBitmap1关联进srcDc1里面
		BitBlt(hdc, 0, 0, 1024, 768, srcDc1, 0, 0, SRCCOPY);//层次绘图 为什么一放大就没了 在WM_PAINT里面放大不会变白
		DeleteObject(srcBitmap1);//释放位图对象
		DeleteDC(srcDc1);//释放辅助DC
		ReleaseDC(hWnd, hdc);
		/*
		BOOL BitBlt(
		_In_ HDC   hdcDest,
		_In_ int   nXDest,
		_In_ int   nYDest,
		_In_ int   nWidth,
		_In_ int   nHeight,
		_In_ HDC   hdcSrc,
		_In_ int   nXSrc,
		_In_ int   nYSrc,
		_In_ DWORD dwRop
		);
		*/

	}
	break;
	case WM_LBUTTONDBLCLK://左键双击  在注册窗口类 需要加上CS_DBCLKS才能响应双击的操作
	{
		//GDI-字体
		HDC hdc = GetDC(hWnd);
		HFONT hfont = nullptr;//字体句柄
							  //hfont = (HFONT)GetStockObject(SYSTEM_FONT);//SYSTEM_FONT表示字体,GetStockObject表示使用系统字体
		hfont = CreateFont(40,/*高度用于拉伸*/
			0, /*宽度用于拉伸*/
			100, /*文字的倾斜角度*/
			0, /*单个字体的倾斜角度*/
			700,/*笔画的粗细*/
			0,/*true表示斜体*/
			0,/*true表示下划线*/
			0,/*删除线*/
			GB2312_CHARSET,/*字符集*/
			0, 0, 0, 0, _T("黑体")/*某些特定的字样只在特定字符集中有*/);//自定义字体
													  /*
													  点阵字体：用二维数组存储点阵，读取速度快，不容易缩放
													  矢量字体：填充直线和曲线的轮廓形成，缩放不失真
													  给一个值去字体库取出图片打印
													  用户输入一个消息一个值，字体安装软件截获这个消息，并引导windows系统去外接字体库寻找
													  */
		SelectObject(hdc, hfont);//把字体句柄关联进hdc设备环境句柄
		SetTextColor(hdc, 0xff00);//设置文字颜色
		SetBkMode(hdc, TRANSPARENT);//设置文字背景模式 OPAQUE为白色，TRANSPARENT为文字背景透明
									//SetBkColor(hdc, 0xff0000);//设置文字背景颜色
		TextOut(hdc, 300, 100, _T("hell world!"), 11);//锚点默认在矩形左上角

		DeleteObject(hfont);
		ReleaseDC(hWnd, hdc);

	}
	break;
	case WM_LBUTTONDOWN:
	{
		//GDI-画刷
		HDC hdc = GetDC(hWnd);
		HBRUSH hbr;//画刷句柄
				   //hbr = (HBRUSH)GetStockObject(BLACK_BRUSH);//使用系统定义的颜色
		hbr = CreateSolidBrush(0xff);//类似于hpen的自定义颜色
		SelectObject(hdc, hbr);//把画刷关联进hdc设备环境句柄
							   //---改变边框画笔
		HPEN hpen = CreatePen(PS_SOLID, 1, 0xff);
		SelectObject(hdc, hpen);
		//-----------
		Rectangle(hdc, 100, 100, 400, 400);//画矩形,默认白色画刷填充，黑色画笔画边框
		DeleteObject(hpen);
		DeleteObject(hbr);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		//GDI-画刷
		HDC hdc = GetDC(hWnd);
		HBRUSH hbr;//画刷句柄
				   //hbr = (HBRUSH)GetStockObject(BLACK_BRUSH);//使用系统定义的颜色
				   //hbr = CreateSolidBrush(0xff);//类似于hpen的自定义颜色,纯色画刷
		hbr = CreateHatchBrush(HS_HORIZONTAL, 0xff);//阴影画刷
		SelectObject(hdc, hbr);//把画刷关联进hdc设备环境句柄
							   //---改变边框画笔
		HPEN hpen = CreatePen(PS_SOLID, 1, 0xff);
		SelectObject(hdc, hpen);
		//-----------
		Rectangle(hdc, 100, 100, 400, 400);//画矩形,默认白色画刷填充，黑色画笔画边框
		DeleteObject(hpen);
		DeleteObject(hbr);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_KEYDOWN:
	{
		//GDI-画刷
		HDC hdc = GetDC(hWnd);//设备环境句柄
		HBRUSH hbr;//画刷句柄
				   //hbr = (HBRUSH)GetStockObject(BLACK_BRUSH);//使用系统定义的颜色
				   //hbr = CreateSolidBrush(0xff);//类似于hpen的自定义颜色,A.纯色画刷
				   //hbr = CreateHatchBrush(HS_HORIZONTAL, 0xff);//B.阴影画刷
		HBITMAP hbt = (HBITMAP)LoadImage(hInst, _T("girl.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//加载图片GDI支持bmp 不支持jpg 注意jpg改后缀不行 因为位图bmp包含：文件头、信息头、彩色表、图像数据库阵列与jpg不一样 可以使用 画图 另存为bmp
		hbr = CreatePatternBrush(hbt);//C.位图画刷
		SelectObject(hdc, hbr);//把画刷关联进hdc设备环境句柄

							   //---改变边框画笔
		HPEN hpen = CreatePen(PS_SOLID, 1, 0xff);
		SelectObject(hdc, hpen);
		//---边框选择
		//Ellipse(hdc, 100, 100, 600, 400);//圆或椭圆 坐标为外接矩形
		//Rectangle(hdc, 100, 100, 400, 400);//画矩形,默认白色画刷填充，黑色画笔画边框
		//RoundRect(hdc, 100, 100, 600, 400, 300, 200);//画圆角矩形，最后两个参数为圆角弧
		//Pie(hdc,100,100,400,400,0,0,250,400);//画饼图 外接矩形定位，弧的画法和圆弧画法一样为点到圆心的连线的延长线于圆的交点 方向为逆时针画法
		Chord(hdc, 100, 100, 400, 400, 0, 0, 250, 400);//画弦图，参数与饼图一样
													   /*
													   BOOL Pie(
													   HDC hdc,
													   int left,外接矩形区域
													   int top,外接矩形区域
													   int right,外接矩形区域
													   int bottom,外接矩形区域
													   int xr1,
													   int yr1,
													   int xr2,
													   int yr2
													   );
													   */
													   //------
		DeleteObject(hpen);//释放画笔对象
		DeleteObject(hbr);//释放画刷对象
		ReleaseDC(hWnd, hdc);//释放设备环境句柄
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