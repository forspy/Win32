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
		//�Ի��򴴽����� �Ի�����û�ж�̬�����ķ����������
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
		//��̬�Ի��򴴽�����
		DialogBox(hInst,//Ӧ�ó���ʵ�����
			MAKEINTRESOURCE(IDD_DIALOG1),//�ؼ�����ͨ���Ի����ID����MAKEINTRESOURCE()��������һ������
			hWnd,//�����;��
			About//�Ի������Ϣ���������ص�����
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
TCHAR str[1024] = { 0 };
//�Լ��ĶԻ�������
INT_PTR CALLBACK myDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);//��ȫ�ȼ�
	switch (message)
	{
	case WM_INITDIALOG://��ʼ���Ի���ʱ(����WM_CREATE)����̬�ؼ���������
	{
		//�ؼ�Ҳ��һ������
		//��ѹʽ��ť
		CreateWindow(_T("Button"),//�ǿؼ�����,����Button��һ������
			_T("����"),//�ؼ�������
			WS_CHILD | WS_VISIBLE|BS_PUSHBUTTON,//�Ӵ���|�ɼ�|ʹ�û���button��һ�����
			10, 10,//�ؼ�λ��
			100, 30,//��x����y
			hDlg,//�ؼ��ĸ����ھ��
			(HMENU)5001,//ϵͳ���õĿؼ�ID��,�ԱȾ�̬�ؼ�����Ŀؼ�ID��
			hInst,//ʵ�����
			nullptr//������Ϣ 
		);
		//�����ʾ��Ϣ ���Ļ���Ҳ��Button������f12�鿴����������
		CreateWindow(_T("Button"),_T("�����ʾ�"),WS_CHILD | WS_VISIBLE | BS_GROUPBOX,10, 50,650, 200,hDlg,(HMENU)5002,hInst,nullptr);
		//һ������Ա
		//��̬�ı������û���ʾ��Ϣ ����Static�������������ڿؼ��������в鿴
		CreateWindow(_T("Static"), _T("��ͥ��Ա"), WS_CHILD | WS_VISIBLE , 20, 70, 60, 20, hDlg, (HMENU)5003, hInst, nullptr);
		//��ѡ�򣬻���Button������ѡBS_AUTORADIOBUTTON ����ΪWS_GROUP ֱ���¸�WS_GROUPǰ��Щ��ѡ��Ϊһ��
		CreateWindow(_T("Button"), _T("����"), WS_CHILD | WS_VISIBLE| BS_AUTORADIOBUTTON|WS_GROUP, 20, 90, 50, 30, hDlg, (HMENU)6001, hInst, nullptr);
		CreateWindow(_T("Button"), _T("�ְ�"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 120, 50, 30, hDlg, (HMENU)6002, hInst, nullptr);
		CreateWindow(_T("Button"), _T("����"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 150, 50, 30, hDlg, (HMENU)6003, hInst, nullptr);
		//������ѧ��
		//��̬�ı������û���ʾ��Ϣ ����Static�������������ڿؼ��������в鿴
		CreateWindow(_T("Static"), _T("ѧ��"), WS_CHILD | WS_VISIBLE, 300, 70, 60, 20, hDlg, (HMENU)5004, hInst, nullptr);
		//��ѡ�򣬻���Button������ѡBS_AUTORADIOBUTTON ����ΪWS_GROUP ֱ���¸�WS_GROUPǰ��Щ��ѡ��Ϊһ��
		CreateWindow(_T("Button"), _T("��ר"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 300, 90, 50, 30, hDlg, (HMENU)6004, hInst, nullptr);
		CreateWindow(_T("Button"), _T("����"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 300, 120, 50, 30, hDlg, (HMENU)6005, hInst, nullptr);
		CreateWindow(_T("Button"), _T("�о���"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 300, 150, 70, 30, hDlg, (HMENU)6006, hInst, nullptr);
		//��������Ȥ����
		//��̬�ı������û���ʾ��Ϣ ����Static�������������ڿؼ��������в鿴
		CreateWindow(_T("Static"), _T("��Ȥ����"), WS_CHILD | WS_VISIBLE, 560, 70, 60, 20, hDlg, (HMENU)5005, hInst, nullptr);
		//��ѡ�򣬻���Button������ѡBS_AUTOCHECKBOX 
		CreateWindow(_T("Button"), _T("����"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX , 560, 90, 50, 30, hDlg, (HMENU)6007, hInst, nullptr);
		CreateWindow(_T("Button"), _T("����"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 560, 120, 50, 30, hDlg, (HMENU)6008, hInst, nullptr);
		CreateWindow(_T("Button"), _T("д����"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 560, 150, 70, 30, hDlg, (HMENU)6009, hInst, nullptr);

		//�༭���������֣����ࣺedit  ���WS_BORDERΪ�߿� ������ô�ķ�� multiline���ö��� ������ѽ��ES_MULTILINE
		CreateWindow(_T("Edit"), _T("ͳ�ƽ��"), WS_CHILD | WS_VISIBLE|WS_BORDER| ES_MULTILINE, 10, 260, 200, 100, hDlg, (HMENU)6010, hInst, nullptr);
		//�����ʾ�Ľ����ô�������˵��¼�룬�����

		//����Ĭ�ϵĿؼ�
		//����ͨ����ϵͳͶ����Ϣ�����SendMessage()�ݹ�  PostMessage()ͬ��
		//���沢û�����������ñ����������ӿؼ��Ĵ��ھ������Ϊ�ӿؼ��ܶ࣬����ͨ�����ھ���ܷ�
		//ʹ��GetDlgItem����ÿؼ��ľ����Ͷ��BM_SETCHECK��Ϣ������Ĭ�ϵ�ѡ��
		SendMessage(GetDlgItem(hDlg, 6001), BM_SETCHECK, 1, 0);
			/*��ÿؼ��ľ��
			HWND GetDlgItem(
			HWND hDlg,//��һ���Ի���
			int  nIDDlgItem//�ؼ�ID
			);
			*/
		/*��ϵͳͶ����Ϣ
		LRESULT SendMessage(
		HWND   hWnd,
		UINT   Msg,
		WPARAM wParam,//һ�����Ϣ���������Ϣ����wParam���� ��1��ʾ���
		LPARAM lParam
		);
		*/
		SendMessage(GetDlgItem(hDlg, 6004), BM_SETCHECK, 1, 0);
	}
	return (INT_PTR)TRUE;

	case WM_COMMAND://�ؼ�������Ϣ
		switch (LOWORD(wParam))//��Ӧ�������Ϣ,��Ӧ�ؼ�ID��
		{
		case 5001://ѡ������ؼ�ʱִ��
			
			//---��һ��ͳ��
			_tcscpy_s(str, _T("��ͥ��Ա:"));//���ַ����п���һ������
			if (IsDlgButtonChecked(hDlg, 6001))//IsDlgButtonChecked()�ж�ĳһ����ť�Ƿ�ѡ��
				_tcscat(str, _T("����"));
			else if (IsDlgButtonChecked(hDlg, 6002))
				_tcscat(str, _T("�ְ�"));
			else if (IsDlgButtonChecked(hDlg, 6003))
				_tcscat(str, _T("����"));
			//---�ڶ���ͳ��
			_tcscat(str, _T("  ѧ����"));
			if (IsDlgButtonChecked(hDlg, 6004))
				_tcscat(str, _T("��ר"));
			else if (IsDlgButtonChecked(hDlg, 6005))
				_tcscat(str, _T("����"));
			else if (IsDlgButtonChecked(hDlg, 6006))
				_tcscat(str, _T("�о���"));
			//---������ͳ��
			_tcscat(str, _T("  ��Ȥ���ã�"));
			if (IsDlgButtonChecked(hDlg, 6007))
				_tcscat(str, _T("���� "));
			if (IsDlgButtonChecked(hDlg, 6008))
				_tcscat(str, _T("���� "));
			if (IsDlgButtonChecked(hDlg, 6009))
				_tcscat(str, _T("д���� "));

			//��ͳ�Ƴ�������Ϣ���͵��Ի�����
			SetDlgItemText(hDlg, 6010, str);
			//�ɹ�����
			MessageBox(0, _T("�ɹ�����"), 0, 0);
			SetDlgItemText(hDlg, 6005, _T("����"));//ͨ����һ�����ɺ�ĳ���ؼ������ֱ�ǩ�Ķ�
			break;
		}

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
//���ֿؼ���ť����ͼ--���������У��ж�������� ��̬��ӷ�ʽ