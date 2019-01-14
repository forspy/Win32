// teach_win32_GDI 1.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "teach_win32_GDI 1.h"

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
    LoadStringW(hInstance, IDC_TEACH_WIN32_GDI1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_GDI1));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_GDI1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);//�ͻ�������
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_GDI1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
//GDIͼ���豸�ӿڣ�ͼ�ο⣩ Graphics Device Interface  
//GDI����Ҫ�����Ǹ���ϵͳ���ͼ����֮�����Ϣ����
//GDI��һ���������ӣ������кܶຯ��
/*
1.ȡ�ú��ͷ��豸�����ĵĺ������豸������Ҳ�����豸����DC ��WINDOWSһ������ָ�ִ�����ָ���йص�Ӳ��������������ڴ涼���豸������
2.ȡ���й��豸������Ϣ�ĺ���
3.��ͼ����
4.�趨��ȡ���豸�����Ĳ����ĺ���
5.����GDI����ĺ���
*/
//GDI���Բ�����ͼ��
/*
1.����
2.�������
3.��ʾ����
4.��ʾͼƬ
*/
//GDI��ͼ�εĲ��裺
//����Ҫ֪��ʹ���Կ����ĸ�������Ҳ����Ҫ֪����Ҫ���������Ǹ�������ֻ��Ҫ��Windows��ָ���windowsϵͳ��������ɾ���
/*
1.�õ��豸������� HDC
2.�޸��豸���� ���磺��ɫ���ߡ���ɫ����
3.��ͼ
4.�ͷ��豸�������
*/
//win32���������ַ����õ��豸�������(ָ���ǿͻ������豸���������
/*
1.��WN_PAINT��Ϣ���� HDC hdc = BeginPaint(hWnd, &ps);�õ��豸�����ľ����ͨ��EndPaint(hWnd, &ps);���ͷ��豸�������
	Ӧ�ó������WN_PAINT��Ϣ�����������1�������������ʱ���� 2.���ڳ�����Ч����ʱ����-->a.�����ƶ����С�����ı� �������غ�������ʾ b.invalidateRect(ʹ��������ʧЧ)invalidateRgn��ʹ����ʧЧ���Ի�ͼ����Ϊ�� c.ScrollWindow���������ڣ�ScrollDC�������豸�ͻ�����
	��4������������WN_PAINT��Ϣ ��1.��괩Խ�ͻ���2.ͼ���Ϲ��ͻ���3.��ʾ�Ի���4.��ʾ�˵����ͷ�  ��ʵ�ͻ������ж������
2.��WM_PAINT��Ϣ֮�⣬ͨ��GetDC���õ��豸���������ͨ��releaseDC���ͷ��豸������� ����˵��WM_LBUTTONDOW����Ӧ��ͼ��Ϣ ���߼�ʱ����Ϣ����WM_TIMER��ͼ
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	//----GDI����
	case WM_LBUTTONDOWN:
	{
		//GDI����
		//WM_PAINT��Ϣ֮��
		HDC hdc = GetDC(hWnd);//�õ��豸�������
		//A.�޸��豸���� ����ѡ���޸������豸Ĭ�ϵ�����
		//B.--ѡ���޸Ļ���---
		//HPEN hpen = nullptr;
		//hpen = (HPEN)GetStockObject(WHITE_PEN);//�õ�ϵͳԤ���GDI����  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);//�ͻ���������Ϊ��
		//SelectObject(hdc, hpen);//�޸��豸����
		//----------
		//C.---ѡ���Զ��廭��
		HPEN hpen = CreatePen(PS_SOLID,//���ʵķ��
		2,//���ʵĿ�ȣ�������ʵĿ�ȴ���1����ʲô������񶼻��Ϊʵ�߷��
		//win32��32λ����ʾ��ɫ4��char����ɫͨ��argb��a��ʾ͸����͸������˼��ǰ��ɫ�ͱ���ɫһ�£�	
			RGB(255, 0, 0));//WINGDIAPI HPEN    WINAPI CreatePen( _In_ int iStyle, _In_ int cWidth, _In_ COLORREF color); COLORREFΪ4�ֽڵ�����
		//RGB(r, g, b);//#define RGB(r,g,b) ���κ�         ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))) �γ�BGR��λ�� ���Ժ�ɫҲ����ʹ��0xff����ʾͬ����ɫ0xff00 ��ɫ0xff0000
		SelectObject(hdc, hpen);//�޸��豸����
		MoveToEx(hdc,50,50,nullptr);//�ѻ����ƶ���ĳ���㣬�������û��ʵ����
		/*
		BOOL MoveToEx(
  HDC     hdc,
  int     x,
  int     y,
  LPPOINT lppt
);
		*/
		LineTo(hdc, 100, 100);//��ʾ���ߵ�hdc�ͻ�����100��100λ�ô������û��ָ����㣬Ĭ�ϴ�0��0��ʼ��
		//--�ͷ�
		DeleteObject(hpen);//�ͷ��޸ĵ��豸���ԣ��ͷŵ�hpen��SelectObject��ռ���ڴ�

		//���ѡ��ͬ��ɫ���߶�/��ͬ��ϸ��Ҫ��GDI�������´������ʶ���
		HPEN hpen1 = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
		SelectObject(hdc, hpen1);//�޸��豸����
		LineTo(hdc, 200, 300);
		DeleteObject(hpen1);


		ReleaseDC(hWnd, hdc);//�ͷ��豸�������

	}
	break;
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);//�õ��豸�������
		HPEN hpen = CreatePen(PS_SOLID, 2, 0xff0000);
		SelectObject(hdc, hpen);
		//�ڳ����л�Բ��Ҫָ����Ӿ��εĴ�С
		Arc(hdc,100,100,400,400,0,0,250,600);//��Բ������ʱ����ƣ�
		/*
		BOOL Arc(
		HDC hdc,
		int x1,//����
		int y1,//����
		int x2,//����
		int y2,//����
		int x3,//Բ������� ������Բ�⣨�ڣ���������㵽Բ�ĵ����ߣ��ӳ��ߣ���Բ�Ľ���Ϊ���
		int y3,//Բ�������
		int x4,//Բ�����յ�  ������Բ�⣨�ڣ���������㵽Բ�ĵ����ߣ��ӳ��ߣ���Բ�Ľ���Ϊ�յ�
		int y4//Բ�����յ�
		);

		*/
		DeleteObject(hpen);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_KEYDOWN:
	{
		//����
		HDC hdc = GetDC(hWnd);
		HPEN hpen = CreatePen(PS_SOLID, 2, 0xff);
		SelectObject(hdc, hpen);
		for (int i = 0; i < 100; ++i)
			SetPixel(hdc, 500 + i, 500, 0xff);//�������ص�
		for (int j = 0; j < 100; ++j)
			SetPixel(hdc, 500 + j, 600, GetPixel(hdc, 500 + j, 500));//�������ص�->����ͼƬ->�Ŵ�Ҳ��
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
