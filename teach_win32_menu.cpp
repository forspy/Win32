// teach_win32_menu.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "teach_win32_menu.h"

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
    LoadStringW(hInstance, IDC_TEACH_WIN32_MENU, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_MENU));

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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
HMENU hMenu;//����һ���˵����
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
	//��2�ִ�����̬�˵��ķ�ʽ
   /*HMENU hMenu;
   hMenu=LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));*/
	//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); MAKEINTRESOURCE(IDI_SMALL)��LPCWSTR���͵���һ���ַ���ָ������
	   /*
	   LoadMenuW(
    _In_opt_ HINSTANCE hInstance,
    _In_ LPCWSTR lpMenuName);
	   */
   //��̬�˵��Ĵ�����ʽ
  
   hMenu = CreateMenu();//����һ���յĲ˵������ҷ�������˵��ľ�� ���Ϊһ������ָ��
   //β����Ӳ˵���
   AppendMenu(hMenu,//ָ������һ���˵���β������׷��
	   0,//���
	   5001,//�˵���ID��������Դ��������Ϣ�˵��������ܹ�ʹ��
	   _T("�����ļ�"));
	   /*
	   AppendMenuW 
    _In_ HMENU hMenu,
    _In_ UINT uFlags,
    _In_ UINT_PTR uIDNewItem,
    _In_opt_ LPCWSTR lpNewItem);
	   */ 
   AppendMenu(hMenu,0,5002,_T("�½�"));
   
   //�Ӳ˵�����ӷ���
   HMENU hMenu1= CreateMenu();
   AppendMenu(hMenu1, 0, 5003, _T("�ļ�"));
   AppendMenu(hMenu1, 0, 5004, _T("����"));
   //�ڰ��µĲ˵�׷�ӵ�����ȥ,���ΪMF_POPUP ��ʾ�ܵ����˵�
   AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu1, _T("�½�����(&F)"));

   //��ָ��λ�ò���˵��ķ���  (ǰ��)
   HMENU hMenu2 = CreateMenu();
   InsertMenu(hMenu, 1, MF_BYPOSITION, 6001, _T("�������λ��"));//����λ�õĲ���
   InsertMenu(hMenu, 5002, MF_BYCOMMAND, 6002, _T("�����������"));//�����������

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, /*nullptr*/hMenu, hInstance, nullptr);//������������������ΪhMenu
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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
//�˵�������
//��̬�˵��������ʱ��ʹ���������̬�˵�(�ں������й����и�ֵ)����ݲ˵�(Ԥ�ȱ���ã���Ӧ�Ҽ���Ϣʱ����) 
//�˵�������Ƕ�׵� 
/*
1.������̬�˵� ��ͼ-��������-��Դ��ͼ ��menu�ļ����µ��Ĭ��ע������������ �����޸�
a.���磺����(&S) �Ϳ������ÿ�ݼ�
b.- ��ʾ�ָ���
c.menu�����Ҽ� ����menu�����µ�menu
d.��ע�ᴰ�������� wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
e.��̬�˵�ֻ����һ��
f.case ID_NEWFILE://��WM_COMMAND�˵���Ϣ  ID_NEWFILE�ǿ����Լ��Բ˵�������
g.��Ҫ������ݼ���Ϣ ��Ҫ����Դ��ͼAccelerator��������
h.������enableΪfasle��Ϊ�Ǽ���(���)
*/
HMENU g_hMenu;//�Ҽ��˵���ݼ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		//�Ҽ������˵�
	case WM_CREATE:
		g_hMenu = LoadMenu(hInst, MAKEINTRESOURCEW(IDR_MENU2));
		break;
	case WM_LBUTTONDOWN:
		EnableMenuItem(hMenu, 5003, MF_GRAYED);//���������
		break;
	case WM_RBUTTONDOWN:
	{
		POINT point;
		point.x = LOWORD(lParam);//�������
		point.y = HIWORD(lParam);
		//�ͻ�������ת������Ļ���� �������ת��Ϊ��������
		ClientToScreen(hWnd, &point);
		//�õ��Ӳ˵����
		HMENU h1 = GetSubMenu(g_hMenu, 0);
			/*
			ClientToScreen(
    _In_ HWND hWnd,
    _Inout_ LPPOINT lpPoint);//LPPOINT��һ��ָ��POINT���͵�ָ��
			*/
		//EnableMenuItem(hMenu, 5003, MF_ENABLED);//����Ҽ�����
		TrackPopupMenu(h1,//��ʾ��һ���˵�
			TPM_LEFTALIGN,//�Ҷ�����ʾ �˵��Ķ��䷽ʽ
			point.x,//x��������
			point.y,//y��������
			0,//����Ϊ0
			hWnd,//��ǰ����
			nullptr//Ĭ��
		);
	}
		break;
    case WM_COMMAND://�˵���Ϣ
        {
            int wmId = LOWORD(wParam);//�ڵ�λ���ֽڱ����Ų˵����ID
            // �����˵�ѡ��:  
            switch (wmId)
            {
			case ID_NEWFILE://��Ӧ�˵���Ϣ
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
