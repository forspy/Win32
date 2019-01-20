// teach_win32_Control1.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "teach_win32_Control1.h"

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
HWND g_hDlogWnd;//ȫ�ֶԻ�����
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
    LoadStringW(hInstance, IDC_TEACH_WIN32_CONTROL1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_CONTROL1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_CONTROL1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_CONTROL1);
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
//
//�ؼ���ʾ�����û����루��С�û��������Χ��
//����ʹ�öԻ�����ؿؼ�
//��������Դ��ͼDialog����caption�����޸Ŀؼ���ʾ����
//�Ի����������û����룬���пؼ�����
//�Ի����Ϊ���֣�
/*
1.ģ̬�Ի��� ������ͬ����ģʽ
2.��ģ̬�Ի��� ������(�첽)ģʽ
*/
//�Ի���Ĵ������裺
/*
1.��ӶԻ�����Դ������Դ������ӶԻ���
2.���ú��������Ի��򣨷������Ի��򴴽���CreateDialog()�������Ի��򴴽���DialogBox()��
3.�Ի���ص�������
4.�ͷŶԻ���
*/
INT_PTR CALLBACK myDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);//ǰ��Ի�������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_RBUTTONDOWN:
	{
		g_hDlogWnd=CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1),hWnd,myDialogProc );//����һ���������ĶԻ��򣬷���HWMD
		ShowWindow(g_hDlogWnd, SW_SHOWNORMAL);//�����������Ի���֮��Ҫ��showWindow��ʾ
		/*
		BOOL ShowWindow(
  HWND hWnd,
  int  nCmdShow��ʾ��ʽ
);
		*/
	}
	break;
	case WM_LBUTTONDOWN:
	{
		//MessageBox(hWnd, 0, 0, 0);//����/ͬ��ģʽ����ʾֻ���ڵ�ǰ�Ի��������ɺ���ܲ���������
		DialogBox(hInst,//Ӧ�ó���ʵ�����
			MAKEINTRESOURCE(IDD_DIALOG1),//�ؼ�����ͨ���Ի����ID����MAKEINTRESOURCE()��������һ������
			hWnd,//�����;��
			myDialogProc//�Ի������Ϣ���������ص�����
		);//����һ�������˵�
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
            // �����˵�ѡ��: 
            switch (wmId)//��Ӧ�˵�ID
            {
            case IDM_ABOUT: //���ڲ˵�
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);//����һ�������Ի��򣬷���INT
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
    UNREFERENCED_PARAMETER(lParam);//��ȫ�ȼ�
    switch (message)
    {
    case WM_INITDIALOG://��ʼ���Ի��򣨶Ա�WM_CREATE��
        return (INT_PTR)TRUE;

    case WM_COMMAND://�ؼ�������Ϣ
        if (LOWORD(wParam) == IDOK /*ȷ��*/|| LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));//�����Ի��������Ի����ͷŷ�ʽ
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;//û�в�������FALSE
}
//�Լ��ĶԻ�������
INT_PTR CALLBACK myDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);//��ȫ�ȼ�
	switch (message)
	{
	case WM_INITDIALOG://��ʼ���Ի��򣨶Ա�WM_CREATE��
		return (INT_PTR)TRUE;

	case WM_COMMAND://�ؼ�������Ϣ
		if (LOWORD(wParam) == IDOK /*ȷ��*/ || LOWORD(wParam) == IDCANCEL)
		{
			DestroyWindow(g_hDlogWnd);//�������Ի����ͷŷ�ʽ
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;//û�в�������FALSE
}
//�ؼ�Ҳ��һ������(�Ӵ��ڣ�������һ��������)
//�ؼ�Ҳ��������Ϣ
//�ؼ��Ĵ������Ѿ���ϵͳ�ж��度�ˣ�ֱ����
//���ֿؼ���ť����ͼ--���������У��ж��������