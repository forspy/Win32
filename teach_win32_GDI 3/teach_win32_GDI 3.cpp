// teach_win32_GDI 3.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "teach_win32_GDI 3.h"
#pragma comment (lib,"Msimg32.lib")//����TransparentBlt����
#pragma comment (lib,"Winmm.lib")//����timeGetTime����
#include <TimeAPI.h>//����timeGetTime����
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

//��Ϊ��Ҫ����Ϣѭ������һ�����ھ����������Ҫһ��ȫ�ֵĴ��ھ��
HWND g_hWnd;//ȫ�ֱ��� �ڴ��ڳ�ʼ������BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)��ֵ
int heroFrame = 0;//��ʾ��ǰӢ�۶�������һ��֡
//Ӣ����ʼλ��
int heroX ;
int heroY ;
//Ӣ�۵ĳ���
int heroDir;
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
    LoadStringW(hInstance, IDC_TEACH_WIN32_GDI3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_GDI3));

    MSG msg;

    // ����Ϣѭ��: 
   /* while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
	//��Դ�ĳ�ʼ�� Ϊɶѡ�����λ�ã���Ϊ���ﴰ���Ѿ���ʼ���ˣ�����ʹ��ȫ�ֵĴ��ھ����g_hWnd
	//��Դ����-----
	//[��]����һ�����豸�������
	HDC hdc = GetDC(g_hWnd);
	//Ϊ�˽�����������⣬׼��һ������DC�γ�˫����
	HDC buffDc = CreateCompatibleDC(hdc);//����һ������DC���ݵĻ���DC
	HBITMAP buffBitmap = CreateCompatibleBitmap(hdc, 1024, 768);//����һ������λͼ������DC����
	SelectObject(buffDc, buffBitmap);//������λͼ����������DC
	
	//���ر���λͼ---------------
	//1.�ȴ���һ�������豸�����������Ǽ��ر���ͼƬ
	HDC bkDc = CreateCompatibleDC(hdc);//������Ҫ��dc�����豸���������������Ҫ����һ�����豸�������
	//2.����λͼ LoadImage ����λͼ����꣬ͼ��
	HBITMAP bkBitmap = (HBITMAP)LoadImage(hInst,_T("bk.bmp"), IMAGE_BITMAP,
		0,0,//����ͼ��Ŀ�Ⱥ͸߶ȣ����Ϊ0��Ĭ����Ϊͼ���ԭʼ���
		LR_LOADFROMFILE//��ʾ���ļ�����
	);//hinstҲ���ڴ��ڳ�ʼ���Ժ���ֵ����˺ܶ��߼�����Ⱦ�Ĳ�����Ҫ���ڳ�ʼ������֮��,��ΪLoadImage���ص���һ��HANDLE����һ��������൱��void�����Կ��Խ���ǿת
	//3����bkbitmapλͼ
	SelectObject(bkDc,bkBitmap);//��bkDc�й���bkbitmapλͼ
	//------------------
	//����Ӣ��λͼ------------
	//1.�ȴ���һ��Ӣ�۸����豸����
	HDC heroDc = CreateCompatibleDC(hdc);
	//2.����λͼ
	HBITMAP heroBitmap = (HBITMAP)LoadImage(hInst, _T("hero.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//3.����heroBitmapλͼ
	SelectObject(heroDc, heroBitmap);

	ReleaseDC(g_hWnd, hdc);//���ͷ�������豸���� 
	//Ӣ����ʼλ��
	heroX = 200;
	heroY = 400;
	//��Դ����-----------------
	memset(&msg, 0, sizeof(msg));
	//��Ϊ������������Ϣ
	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//�ǲ��ǿ����Ϣ
			{
				TranslateMessage(&msg);//������Ϣ��������̰���
				DispatchMessage(&msg);//�������ڲ�Ͷ����Ϣ
			}
		}
	//��Ϊ��������һֱ������Ϣ��������߼�����Ⱦ
		//���Ʋ���--------
		//1.���»���豸�������
		HDC hdc = GetDC(g_hWnd);
		//----------Ϊ�˽�����������е�ͼƬ�������⣬ʹ�ú�ɫ��ˢˢһ��
		RECT r = { 0,0,1024,768 };
		HBRUSH hr = CreateSolidBrush(0x00);//����һ����ˢ����
		FillRect(buffDc, &r, hr);//���r����ʾ�ľ�������
		DeleteObject(hr);//�ͷŻ�ˢ
		//----------
		//2.���Ʋ���,���Ʊ���
		//BitBlt(hdc,//Ŀ��DC
		//	0, 0,//Ŀ������Ͻ�xy���꣬�൱���Ӵ���λ��
		//	1024, 768, //Ŀ���Ӵ��Ŀ��
		//	bkDc,//��ԴDC 
		//	0, 0,//��Դ�����Ͻ�xy���꣬��ͼ��λ��
		//	SRCCOPY//����Դ����ԴDC������Ŀ��DC
		//);
		////���Ʋ��֣�����Ӣ��
		//BitBlt(hdc, 0, 0, 1024, 768, heroDc, 0, 0, SRCCOPY);
		////���⣺��������� ���ڲ���һ�𻭳�����ԭ�������Ⱥ�(ˢ���ʲ�һ��)����˻��������������һ�𻭳����ܽ�����������⣬Ҳ����˫�������
		//��ֹ��Ƶ��˫�������
		//2.���Ʋ��֣���
		BitBlt(buffDc, 0, 0, 1024, 768, bkDc, 0, 0, SRCCOPY);//��bkDc�����ݻ��뻺��buffdc����
		//BitBlt(buffDc, 0, 0, 1024, 768, heroDc, 0, 0, SRCCOPY); //��heroDc�����ݻ��뻺��buffdc����,���ǻ���ָ���
		TransparentBlt(buffDc, 
			heroX, heroY, //Ŀ������ xy����λ��
			90, 88,//Ŀ������ķ�Χ
			heroDc, 
			heroFrame*90, heroDir*88,//��ʾ��Դ��ʾ��Ŀ�������λ��
			90, 88, //��ʾѡȡ֡��������Ĵ�С�������Ŀ������Ĵ�С��һ�£��������
			RGB(255,255,255));//ע��������Ҫд֡������ʵ�ʴ�С��RGB(255,255,255)��ʾ͸���Ĳ���Ϊ��ɫ
		BitBlt(hdc, 0, 0, 1024, 768, buffDc, 0, 0, SRCCOPY);//��buffDc�����ݻ��뻺��hdc����
		
		//���м�ʱ����
		static float beginTimer = timeGetTime() / 1000.0f;//1.��̬�Ŀ�ʼʱ��,����1000��õ��� 2.��beginTimerֻ��ʼ��һ��
		float endTimer = timeGetTime() / 1000.0f;
		if (endTimer - beginTimer >= 0.5)//�������0.5�룬�൱��һ����ʱ��������ʱ���ǿ����̵߳�
		{
			//��heroFrame��0-3֮��ѭ��-----
			heroFrame++;
			if (heroFrame == 4)
				heroFrame = 0;
			//-------------
			beginTimer = endTimer;
			//ע��sleep�Ƕ��߳��õĲ������ڵ��߳�ʹ��
			
		}
		//3.�ͷ��豸����
		ReleaseDC(g_hWnd, hdc);
		//���Ʋ���------------
	}
	//�ͷ�heroλͼ��hero�����豸����
	DeleteObject(heroBitmap);
	DeleteDC(heroDc);
	//�ͷ�bkλͼ��bk�����豸����
	DeleteObject(bkBitmap);
	DeleteDC(bkDc);
	//�ͷŻ���λͼ�ͻ��渨���豸����
	DeleteObject(buffBitmap);
	DeleteDC(buffDc);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_GDI3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_GDI3);
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
      CW_USEDEFAULT, 0, 960, 640, nullptr, nullptr, hInstance, nullptr);//�������ڴ�С���óɱ���ͼ���С
   g_hWnd = hWnd;//���ڶ�ȫ�ֱ�����ֵ
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'W':
		case VK_UP:
		{
			if (heroX > 0 && heroY > 0)
			{
				heroX--;
				heroY--;
				heroDir = 3;
			}
		}
		break;
		case 'S':
		case VK_DOWN:
		{
			if (heroX < 880 && heroY < 500)
			{
				heroX++;
				heroY++;
				heroDir = 0;
			}
		}
		break;
		case 'A':
		case VK_LEFT:
		{
			if (heroX > 0 && heroY < 500)
			{
				heroX--;
				heroY++;
				heroDir = 1;
			}
		}
		break;
		case 'D':
		case VK_RIGHT:
		{
			if (heroX < 880 && heroY >0)
			{
				heroX++;
				heroY--;
				heroDir = 2;
			}
		}
		break;
		}
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
