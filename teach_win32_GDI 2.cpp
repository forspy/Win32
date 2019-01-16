// teach_win32_GDI 2.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "teach_win32_GDI 2.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

												// �˴���ģ���а����ĺ�����ǰ������: 
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

	// TODO: �ڴ˷��ô��롣

	// ��ʼ��ȫ���ַ���
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TEACH_WIN32_GDI2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_GDI2));

	MSG msg;

	// ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//GDI2 --��ˢ�����֡�λͼbmp
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONDBLCLK://�Ҽ�˫��
	{
		//GDI-λͼ
		//λͼ����ά������һ��ͼƬ������ ÿһ�����ض���ֵ 
		/*
		λͼ�������ļ�ͷ����Ϣͷ����ɫ��ͼ�����ݿ�����
		*/
		//pngΪʸ��ͼ ��¼һ����� �յ� Ȼ�������������ɫ�仯�Ĺ��ɣ�����ʱ���Լ��� Ȼ����Ⱦ һ���ѹ�� ���Ų�ʧ��
		//λͼ����һ��һ�㻭��ȥ������10��ͼ����10��
		HDC hdc = GetDC(hWnd);//�豸�������
		HDC srcDc1 = CreateCompatibleDC(hdc);//����һ������DC����Դ���ؽ�������ΪҪһ��һ��Ļ�
											 //�����Դ������Դ��ͼ������� �������Ҽ���Ŀ �����Դ bitmap ѡ���½� �鿴������������Ϊ24λ����
											 //Ȼ��ʹ����Ƭ�鿴���� ctrl c Ȼ������Դλͼ����ctrl v
											 //������ͼƬ�Ϳ��Կ������ԣ���Ҫ��ѡ��״̬��
		HBITMAP srcBitmap1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));//����Դ����һ��λͼ,���λͼ������д��exe�У���Ȼ����exe��С �������ں��ڵ��޸�
		SelectObject(srcDc1, srcBitmap1);//��srcBitmap1������srcDc1����
		BitBlt(hdc, 0, 0, 1024, 768, srcDc1, 0, 0, SRCCOPY);//��λ�ͼ Ϊʲôһ�Ŵ��û�� ��WM_PAINT����Ŵ󲻻���
		DeleteObject(srcBitmap1);//�ͷ�λͼ����
		DeleteDC(srcDc1);//�ͷŸ���DC
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
	case WM_LBUTTONDBLCLK://���˫��  ��ע�ᴰ���� ��Ҫ����CS_DBCLKS������Ӧ˫���Ĳ���
	{
		//GDI-����
		HDC hdc = GetDC(hWnd);
		HFONT hfont = nullptr;//������
							  //hfont = (HFONT)GetStockObject(SYSTEM_FONT);//SYSTEM_FONT��ʾ����,GetStockObject��ʾʹ��ϵͳ����
		hfont = CreateFont(40,/*�߶���������*/
			0, /*�����������*/
			100, /*���ֵ���б�Ƕ�*/
			0, /*�����������б�Ƕ�*/
			700,/*�ʻ��Ĵ�ϸ*/
			0,/*true��ʾб��*/
			0,/*true��ʾ�»���*/
			0,/*ɾ����*/
			GB2312_CHARSET,/*�ַ���*/
			0, 0, 0, 0, _T("����")/*ĳЩ�ض�������ֻ���ض��ַ�������*/);//�Զ�������
													  /*
													  �������壺�ö�ά����洢���󣬶�ȡ�ٶȿ죬����������
													  ʸ�����壺���ֱ�ߺ����ߵ������γɣ����Ų�ʧ��
													  ��һ��ֵȥ�����ȡ��ͼƬ��ӡ
													  �û�����һ����Ϣһ��ֵ�����尲װ����ػ������Ϣ��������windowsϵͳȥ��������Ѱ��
													  */
		SelectObject(hdc, hfont);//��������������hdc�豸�������
		SetTextColor(hdc, 0xff00);//����������ɫ
		SetBkMode(hdc, TRANSPARENT);//�������ֱ���ģʽ OPAQUEΪ��ɫ��TRANSPARENTΪ���ֱ���͸��
									//SetBkColor(hdc, 0xff0000);//�������ֱ�����ɫ
		TextOut(hdc, 300, 100, _T("hell world!"), 11);//ê��Ĭ���ھ������Ͻ�

		DeleteObject(hfont);
		ReleaseDC(hWnd, hdc);

	}
	break;
	case WM_LBUTTONDOWN:
	{
		//GDI-��ˢ
		HDC hdc = GetDC(hWnd);
		HBRUSH hbr;//��ˢ���
				   //hbr = (HBRUSH)GetStockObject(BLACK_BRUSH);//ʹ��ϵͳ�������ɫ
		hbr = CreateSolidBrush(0xff);//������hpen���Զ�����ɫ
		SelectObject(hdc, hbr);//�ѻ�ˢ������hdc�豸�������
							   //---�ı�߿򻭱�
		HPEN hpen = CreatePen(PS_SOLID, 1, 0xff);
		SelectObject(hdc, hpen);
		//-----------
		Rectangle(hdc, 100, 100, 400, 400);//������,Ĭ�ϰ�ɫ��ˢ��䣬��ɫ���ʻ��߿�
		DeleteObject(hpen);
		DeleteObject(hbr);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		//GDI-��ˢ
		HDC hdc = GetDC(hWnd);
		HBRUSH hbr;//��ˢ���
				   //hbr = (HBRUSH)GetStockObject(BLACK_BRUSH);//ʹ��ϵͳ�������ɫ
				   //hbr = CreateSolidBrush(0xff);//������hpen���Զ�����ɫ,��ɫ��ˢ
		hbr = CreateHatchBrush(HS_HORIZONTAL, 0xff);//��Ӱ��ˢ
		SelectObject(hdc, hbr);//�ѻ�ˢ������hdc�豸�������
							   //---�ı�߿򻭱�
		HPEN hpen = CreatePen(PS_SOLID, 1, 0xff);
		SelectObject(hdc, hpen);
		//-----------
		Rectangle(hdc, 100, 100, 400, 400);//������,Ĭ�ϰ�ɫ��ˢ��䣬��ɫ���ʻ��߿�
		DeleteObject(hpen);
		DeleteObject(hbr);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_KEYDOWN:
	{
		//GDI-��ˢ
		HDC hdc = GetDC(hWnd);//�豸�������
		HBRUSH hbr;//��ˢ���
				   //hbr = (HBRUSH)GetStockObject(BLACK_BRUSH);//ʹ��ϵͳ�������ɫ
				   //hbr = CreateSolidBrush(0xff);//������hpen���Զ�����ɫ,A.��ɫ��ˢ
				   //hbr = CreateHatchBrush(HS_HORIZONTAL, 0xff);//B.��Ӱ��ˢ
		HBITMAP hbt = (HBITMAP)LoadImage(hInst, _T("girl.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//����ͼƬGDI֧��bmp ��֧��jpg ע��jpg�ĺ�׺���� ��Ϊλͼbmp�������ļ�ͷ����Ϣͷ����ɫ��ͼ�����ݿ�������jpg��һ�� ����ʹ�� ��ͼ ���Ϊbmp
		hbr = CreatePatternBrush(hbt);//C.λͼ��ˢ
		SelectObject(hdc, hbr);//�ѻ�ˢ������hdc�豸�������

							   //---�ı�߿򻭱�
		HPEN hpen = CreatePen(PS_SOLID, 1, 0xff);
		SelectObject(hdc, hpen);
		//---�߿�ѡ��
		//Ellipse(hdc, 100, 100, 600, 400);//Բ����Բ ����Ϊ��Ӿ���
		//Rectangle(hdc, 100, 100, 400, 400);//������,Ĭ�ϰ�ɫ��ˢ��䣬��ɫ���ʻ��߿�
		//RoundRect(hdc, 100, 100, 600, 400, 300, 200);//��Բ�Ǿ��Σ������������ΪԲ�ǻ�
		//Pie(hdc,100,100,400,400,0,0,250,400);//����ͼ ��Ӿ��ζ�λ�����Ļ�����Բ������һ��Ϊ�㵽Բ�ĵ����ߵ��ӳ�����Բ�Ľ��� ����Ϊ��ʱ�뻭��
		Chord(hdc, 100, 100, 400, 400, 0, 0, 250, 400);//����ͼ���������ͼһ��
													   /*
													   BOOL Pie(
													   HDC hdc,
													   int left,��Ӿ�������
													   int top,��Ӿ�������
													   int right,��Ӿ�������
													   int bottom,��Ӿ�������
													   int xr1,
													   int yr1,
													   int xr2,
													   int yr2
													   );
													   */
													   //------
		DeleteObject(hpen);//�ͷŻ��ʶ���
		DeleteObject(hbr);//�ͷŻ�ˢ����
		ReleaseDC(hWnd, hdc);//�ͷ��豸�������
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �����˵�ѡ��: 
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
		// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...

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

// �����ڡ������Ϣ�������
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