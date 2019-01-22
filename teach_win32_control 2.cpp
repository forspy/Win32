// teach_win32_control 2.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "teach_win32_control 2.h"

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
//---�Ի���ģ��
INT_PTR CALLBACK    dlgProc(HWND, UINT, WPARAM, LPARAM);//ǰ���������ص�����
void createContorl(HWND hParentWnd);//����һ���ؼ�
//----
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
    LoadStringW(hInstance, IDC_TEACH_WIN32_CONTROL2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_CONTROL2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_CONTROL2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_CONTROL2);
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
//�ؼ�����Ͽ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_RBUTTONDOWN:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, dlgProc);//����ʽ�Ի���
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
TCHAR strArr[1024] = { 0 };
TCHAR Arr[1024] = { 0 };
INT_PTR CALLBACK dlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		createContorl(hDlg);//�Ի����ʼ���ؼ�
		return (INT_PTR)TRUE;

	case WM_COMMAND://�����ؼ�ʱ����
		switch (LOWORD(wParam))
		{
		case 7001://������������ݡ���ťʱ
			//��ȡ�ı�������
			GetDlgItemText(hDlg, 6001, strArr, 1023);
			SetDlgItemText(hDlg, 8001, strArr);//����Ͽ���ʾ���������ı�
			//����Ͽ������б���Ͷ���ı�����β����ӵķ�ʽCB_ADDSTRING���ı���LPARAM�ķ�ʽ����
			//SendMessage(GetDlgItem(hDlg, 8001), CB_ADDSTRING, 0, (LPARAM)strArr);
			SendMessage(GetDlgItem(hDlg, 8001), CB_INSERTSTRING, 0, (LPARAM)strArr);//ͷ�������б�
			break;
		case 7002://������ɾ�����ݡ���ťʱ
			//GetDlgItemText(hDlg, 8001, strArr, 1023);//�����Ͽ���ı�
			//MessageBox(0, strArr, 0, 0);
			SendMessage(GetDlgItem(hDlg, 8001), CB_DELETESTRING, 0, (LPARAM)strArr);//ɾ����Ͽ��б��ֵĵ�һ������ CB_RESETCONTENT��ɾ���б��е�����Ԫ��
			break;
		case 7003://�������õ�����·������ťʱ
			GetCurrentDirectory(1023,Arr);//�õ�����·��,�ں��������������γ�·��Ҳ��
			SetDlgItemText(hDlg, 6002, Arr);//���ı��������ı�
			//MessageBox(0, Arr, L"����·��", 0);
			break;
		case 7004:
			GetTempPath(1023, Arr);//�õ���ʱ·��
			SetDlgItemText(hDlg, 6002, Arr);//���ı��������ı�
			break;
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			//win32��ʵ���ļ�����
			//1.���������ļ������ľ��
			HANDLE hFile = nullptr;
			//2.�����ļ�
			hFile = CreateFile(_T("file.txt"), GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,nullptr, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);//������fopen��.open()ΪʲôOPEN_ALWAYS�����ԭ�е��ַ� ����� �ѽ��
			//GENERIC_READ | GENERIC_WRITE��ʾ�ɶ���д
			/*
HANDLE CreateFileA(
  LPCSTR                lpFileName,//·���ļ���������ʹ�����·������
  DWORD                 dwDesiredAccess,//�ļ��ķ�������
  DWORD                 dwShareMode,//�����ģʽ
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,//��ȫ����
  DWORD                 dwCreationDisposition,//�ļ�������ʽ
  DWORD                 dwFlagsAndAttributes,//�ļ����ԣ�������ʾ��������
  HANDLE                hTemplateFile
);
			*/
			//3.��д
			char s[1024] = "hello world!!���ss";
			DWORD len = 0;
			//WriteFile(hFile,s,strlen(s),&len,nullptr);//д���ļ���ʱ�����Զ��ֽ�д��ģ���TCHAR��unicode���ֽڣ���һ���ַ�ռ�����ֽ�����ֻ��д��һ�룬
			//�����Ƽ�ʹ�ö��ֽ�д���ļ�����s������Ϊchar
			char s1[1024] = { 0 };
			ReadFile(hFile, s1, 1023, &len, nullptr);//�����ļ�
			strcat_s(s, "����");
			MessageBoxA(0, s1, 0, 0);//ʹ�ö��ֽ���ʾ
			WriteFile(hFile, s, strlen(s), &len, nullptr);
			/*
	BOOL WriteFile(
  HANDLE       hFile,//�������ļ����
  LPCVOID      lpBuffer,//д�������,�ַ���buff
  DWORD        nNumberOfBytesToWrite,//д����ٸ��ֽ�
  LPDWORD      lpNumberOfBytesWritten,//д��ľ������(׼�����)
  LPOVERLAPPED lpOverlapped
);
			*/
			//4.�ر��ļ����
			CloseHandle(hFile);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//����һ���ؼ�
void createContorl(HWND hParentWnd)
{
	//���������ؼ�
	CreateWindow(_T("static"), _T("���������ݣ�"), WS_CHILD | WS_VISIBLE, 10, 20, 100, 30, hParentWnd, (HMENU)5001, hInst, nullptr);//����һ����̬�ı�
	CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE|WS_BORDER | ES_MULTILINE, 120, 15, 300, 30, hParentWnd, (HMENU)6001, hInst, nullptr);//����һ���ı���
	CreateWindow(_T("button"), _T("�������"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 50, 100, 30, hParentWnd, (HMENU)7001, hInst, nullptr);//����һ����ť
	CreateWindow(_T("button"), _T("ɾ������"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 50, 100, 30, hParentWnd, (HMENU)7002, hInst, nullptr);//����һ����ť
	//������Ͽ�����combobox  ��Ϊ����Ͽ�CBS_SIMPLE ����ʽ��Ͽ�CBS_DROPDOWN ����ʽ�б���Ͽ�CBS_DROPDOWNLIST
	CreateWindow(_T("combobox"), _T("����ʽ��Ͽ�"), WS_CHILD | WS_VISIBLE | WS_BORDER|CBS_DROPDOWN, 120, 100, 300, 200, hParentWnd, (HMENU)8001, hInst, nullptr);//ע�������б�ĸ߶�Ҫ�㹻

	CreateWindow(_T("button"), _T("�õ�����·��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 150, 100, 30, hParentWnd, (HMENU)7003, hInst, nullptr);//����һ����ť
	CreateWindow(_T("button"), _T("�õ���ʱ·��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 200, 100, 30, hParentWnd, (HMENU)7004, hInst, nullptr);//����һ����ť
	CreateWindow(_T("edit"), _T("·����ʾ"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 120, 150, 300, 80, hParentWnd, (HMENU)6002, hInst, nullptr);//����һ���ı���

}
