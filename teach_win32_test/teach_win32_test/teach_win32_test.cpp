// teach_win32_test.cpp : ����Ӧ�ó������ڵ㡣
//win32���
//1.��ں���
//2.ע�ᴰ��(���ٿռ�)
//3.��ʼ����������(��ʼ��)
//4.��ʾ����
//5.���´��ڣ��߼����ֺͻ�ͼ���֣�
//6.��Ϣѭ��(����)
//7.������ں���(ʤ������)
#include "stdafx.h"//
#include "teach_win32_test.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��  ����Ϊȫ�ַ�������ĺ�������
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);//[��Ҫ]�ҵ�ע����
BOOL                InitInstance(HINSTANCE, int);// ִ��Ӧ�ó����ʼ��: 
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);//CALLBACK����_stdcall��ʾ�������������Ϊ�ص����� ֻ��Ҫmsg�ṹ����Ĳ��ֳ�Ա
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//��ȫ�ȼ�������scanf() ����ֹԽ�� scanf_s() ��ֹԽ�� ȥ���������䲻Ӱ��
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ��� �����ַ��� �����ǣ�����Ŀ��������Ϊ���������ͱ�����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEACH_WIN32_TEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);//[��Ҫ]����ע���࣬��ע�ᣬ���ʼ������ �൱����Ϊ�������ٿռ� ������������ʼ��
	//������������ݵļ���0
    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	//������������ݵļ���2
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEACH_WIN32_TEST));//��ݼ����
	//Windows��Ϣ����
	//Windows�����е��¼���������Ϣ
	//������Ϣ��Windows��װ�ˣ����þ���
	//������Ϣ��windowsΪÿһ���������е�Ӧ�ó���ά����һ����Ϣ���У�Windows��Ӧ�ó��򴫵���Ϣ�ѷ�װ��Ӧ�ó������ڲ�������Ϣ�ǿɲ�����
	//������Ϣ
    MSG msg;//��Ϣ �ṹ���� �ýṹ���̵߳���Ϣ���н�����Ϣ��Ϣ
	/*
	typedef struct tagMSG {
    HWND        hwnd; ����Ϣ�����ĸ����ھ��
    UINT        message; windows����Ϣ���Ϊ��ţ���ϢID����Ϣ���WM_��ͷ���޷������ͣ�
    WPARAM      wParam;��Ϣ�ĸ�����Ϣ ����Ϣ����Ϊĳһ�࣬��һ��ľ�����Ϣ �������������Ϣ�����x����y���꣬�����������ڵ�����
    LPARAM      lParam;��Ϣ�ĸ�����Ϣ
    DWORD       time;ʱ���¼
    POINT       pt;������꣬�������꣬������
} MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;
	*/
    // ����Ϣѭ��: �൱�ڶ����ĵ��ң�ȥȡ��Ӧ�ó������Ϣ����ȡ��Ϣ
	//1.GetMessage�������������������Ϣ������õ�����Ϣ��������Ϣ����ǲ���WM_QUIT���رգ�������Ƿ���FALSE
	//2.while��GetMessage���ǵȴ��û�������ģ��
	//3..while��GetMessage������������ģ�ͣ���ʡ��Դ
	/*
    while (GetMessage(&msg, nullptr, 0, 0))//ʹ��GetMessage����Ϣ������������Ϣ
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//�ǲ��ǿ�ݼ���Ϣ
        {
            TranslateMessage(&msg);//������Ϣ��������̰���
            DispatchMessage(&msg);//Ͷ����Ϣ��Ӧ�ó������ڲ�������Ϣʹ�ã�Ͷ�ݸ�������Ϣ������WndProc���д�����Ҫ��
			//����رմ������������������Ϣ���в���(windows��װ)������GetMessage()ȡ����Ȼ��DispatchMessage()����Ͷ�ݴ�����Ϣ
        }
    }
	*/
	/*
	BOOL GetMessage(
  LPMSG lpMsg, ָ��MSG�ṹ��ָ�룬�ýṹ����̵߳���Ϣ���н�����Ϣ��Ϣ��
  HWND  hWnd,//�ĸ����ڵ���Ϣ����Ϊ���Լ����ڣ�����Ϊnull
  UINT  wMsgFilterMin,���˺��� ��Ϣ����ֵ��WM_��ͷ���磺0x0200��   ��ֵ�ĸ�0 �����κ���Ϣ
  UINT  wMsgFilterMax ���˺���
);
	*/
	//���ԣ�--------------------------
	//3.������Ϸ���Բ���Ҫ����
	//peekMessage��ͣ�ķ��أ���������Ϣ��� �õ���Ϣ����true,û�еõ���Ϣ����FALSE ������
	//ʵ����
	memset(&msg, 0, sizeof(msg));
	while (msg.message!=WM_QUIT)//��ΪpeekMessage�Ƿ���������û�еõ���Ϣ����FALSE�����Բ���������ģ��
	{
		if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))//PeekMessageʵ�����ǴӶ������濽����������Ҫ����PM_REMOVE����Ϣ�Ӷ��������Ƴ�
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//�ǲ��ǿ�ݼ���Ϣ
			{
				TranslateMessage(&msg);//������Ϣ��������̰���
				DispatchMessage(&msg);//Ͷ����Ϣ��Ӧ�ó������ڲ�������Ϣʹ�ã�Ͷ�ݸ�������Ϣ������WndProc���д�����Ҫ��
									  //����رմ������������������Ϣ���в���(windows��װ)������GetMessage()ȡ����Ȼ��DispatchMessage()����Ͷ�ݴ�����Ϣ
			}
		}
	}
	//-------------------���������Ϸ�����Ļ�������Ҫ��ݼ����˵��Ի��򣬿���ȡ��Դ��ͼ��Ӧ���ļ�����ɾ����ͼ���������Դ��ͼ����ע�ᴰ��ʱ�� wcex.hIconSm�����޸�
    return (int) msg.wParam;//����Ϊʲôֻ��Ҫreturn msg.wParam
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ ��ע��QQ����ʹ��QQ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;//WNDCLASS EXWΪunicode��չ����  wcex���������

    wcex.cbSize = sizeof(WNDCLASSEX);//��ǰ����

    wcex.style          = CS_HREDRAW | CS_VREDRAW;//���� screen��ֱˢ�£�ˮƽˢ��   �������˫����ҪCS_DBLCLKS���֧�� 
    wcex.lpfnWndProc    = WndProc;//1.WndProc��һ������ָ�� ������ֵ��wcex.lpfnWndProc  ��ʹ��wcex.lpfnWndProc�൱��ʹ��WndProc 2.WndProc�ǻص����� 
	//3.��ע������Ϣ��ʱ����߲���ϵͳ��������ڷ����¼�������WndProc����
    wcex.cbClsExtra     = 0;//������Ķ�����Ϣ
    wcex.cbWndExtra     = 0;//���ڵĶ�����Ϣ
    wcex.hInstance      = hInstance;//��ǰʵ��д��ע��
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEACH_WIN32_TEST));//1.ͼ���޸�  2.MAKEINTRESOURCE��IDI_TEACH_WIN32_TEST=107ת�����ַ���
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);//��ǰ�����״
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);//Ĭ�ϱ���������ɫ
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEACH_WIN32_TEST);
    wcex.lpszClassName  = szWindowClass;//1.�������� 2.����ָ�� 3.�൱��ʹ��szWindowClass�������
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));//1.ͼ���޸� ������

    return RegisterClassExW(&wcex);//������ϵͳ������ע�ᴰ����  �൱����������ڲ�private���� �Ѵ����������API����ע�� ��ע��ɹ�����ATOM���͵�ֵ(unsigned short)
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
   HWND hWnd;
	//���ԣ����ô���˫��-----------
   hWnd = FindWindow(szWindowClass, szTitle);//����Ѿ��ҵ��˴��ھ�return FALSE����˲�����Ƶڶ�������
   if (hWnd)
   {
	   return FALSE;
   }
   //-----------------------
   
   //���ھ��
   hWnd = CreateWindowW(szWindowClass,//��ע�ᴰ������ �൱������һ������
	   szTitle,//���ڱ�����
	   WS_OVERLAPPEDWINDOW,//���ڵķ��
       CW_USEDEFAULT, //��ʼ����Xλ�ã����ڵ����Ͻ����꣩(x,y)1920*1080��ʾ����ΪCW_USEDEFAULT�������y�����ź��ݱ��Զ�ƥ��
	   0, //Y��λ��
	   CW_USEDEFAULT,//���ڵĿ��x����
	   0,//���ڵĸ߶ȣ�y����
	   nullptr,//�����ھ����A���ڴ���B����
	   nullptr,//���ڵĲ˵���������NULL����ע��Ĳ˵�����������Ϊnull�������������ʾ�Ĳ˵����HMENU hmenu=CreateMenu();���CreateMenu()����û�д����������ô����û�в˵�
	   hInstance,//ʵ�����
	   nullptr//���ڸ�����Ϣ��һ��null
   );
   //���ԣ����ع��---
  // ShowCursor(false);
   //----------------
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);//API���� ��ʾ����
   UpdateWindow(hWnd);//���´���

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
//WndProcess ���ڹ���/�ӹ�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//������Ϣ����Ϊ�ǽ����У�Ȼ��Ӷ�������ȡ������msg�������Ϣ������ʱ��Ͳ����ľ���λ�ò���Ҫ
{
    switch (message)//��ϢIDƥ��
    {
	//���ԣ�----------------
	case WM_ACTIVATE://�������Ϣ��1.��꼤��2.����꼤�� 3.ȡ�����ڼ���
	{
		switch (wParam)//������wParam�õĶ࣬��ʾ����λ��
		{

		case WA_CLICKACTIVE://WAΪȡ���ڼ����ǰ������ĸ
		{
			HDC hdc = GetDC(hWnd);
			static int j1 = 20;//����һ�������ڲ��ľ�̬��������������Ϊ�������ڣ�������Ϊ������j��������´��õ���ʱ�����ϴ��Ǹ�j
							  //MessageBox(0, _T("��갴��"), _T("����"), 0);
			TextOut(hdc, 300, j1, _T("��꼤��"), 4);//��ʾ�ڴ��ڵ�(0,j)λ����ʾ����,4��ʾ�ַ��ĸ�����1.������ʾ��ȫ 2.����β������ 3.��Ӧ�ַ�����
			ReleaseDC(hWnd, hdc);
			j1 += 20;
		}
		break;
		case WA_ACTIVE://����꼤��
		{
			HDC hdc = GetDC(hWnd);
			static int j2 = 20;//����һ�������ڲ��ľ�̬��������������Ϊ�������ڣ�������Ϊ������j��������´��õ���ʱ�����ϴ��Ǹ�j
							  //MessageBox(0, _T("��갴��"), _T("����"), 0);
			TextOut(hdc, 450, j2, _T("����꼤��"), 5);//��ʾ�ڴ��ڵ�(0,j)λ����ʾ����,4��ʾ�ַ��ĸ�����1.������ʾ��ȫ 2.����β������ 3.��Ӧ�ַ�����
			ReleaseDC(hWnd, hdc);
			j2 += 20;
		}
		break;
		case WA_INACTIVE://ȡ�����ڼ���
		{
			HDC hdc = GetDC(hWnd);
			static int j3 = 20;//����һ�������ڲ��ľ�̬��������������Ϊ�������ڣ�������Ϊ������j��������´��õ���ʱ�����ϴ��Ǹ�j
							  //MessageBox(0, _T("��갴��"), _T("����"), 0);
			TextOut(hdc, 550, j3, _T("ȡ�����ڼ���"), 6);//��ʾ�ڴ��ڵ�(0,j)λ����ʾ����,4��ʾ�ַ��ĸ�����1.������ʾ��ȫ 2.����β������ 3.��Ӧ�ַ�����
			ReleaseDC(hWnd, hdc);
			j3 += 20;
		}
		break;

		}
	}
	break;
	//���ԣ�--------------
	//WM��ͷ����windows��Ϣ������Ϊ��������ϢҲ��ϵͳ��������Ϣ ����WM_CREATE����ϵͳ��������Ϣ
	case WM_CREATE: //�൱����Ĺ��캯����������ʱ��ϵͳ�����Ĭ�ϵĺ��� ���ڳ�ʼ��ģ���hWnd = CreateWindowW()ִ�к���ת��������д��ڵĴ�����ֻ�����һ��
	{
		//��ʾ���ڴ����ɹ�������ʾ֮ǰ
		//����������������ݵļ���1
	}
	break;
	//���ԣ�����ƶ���ʾ����λ��---
	case WM_MOUSEMOVE:
	{
		HDC hdc = GetDC(hWnd);
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		TCHAR arr[128] = { 0 };
		_stprintf_s(arr, L"x=%d,y=%d", x, y);
		
		TextOut(hdc, 0, 0,arr,_tcslen(arr));//ͨ��_tcslen����TCHAR�ַ��ĳ���,��Ҫ 
		ReleaseDC(hWnd, hdc); 
		//����Ϊ_tcslen�Լ�wchar_t�Ĳ���
		const wchar_t* a=L"sss";
		_tcslen(a);
		//�������Ϊʲôy��ֵ���෴��
	}
		break;
		//------------
		//���ԣ������͵���������Ϣ-----
	case WM_LBUTTONDOWN:
	{
		//���ԣ�ͬ������
		//SendMessage(hWnd, WM_KEYDOWN, 0, 0);//������Ϣ����,���ܣ�1.�Եݹ�ķ�ʽ���и���Ϣ�Ĵ���2.���͸�hWnd��ǰ����һ��WM_KEYDOWN����Ϣ3.û�и�����Ϣ4.Ч�����൱�ڼ��̰���
		//���ԣ��첽������
		PostMessage(hWnd, WM_KEYDOWN, 0, 0);//������Ϣ����,���ܣ�1.����з���һ��WM_KEYDOWN��Ϣ2.�ɵ�ǰ���ڴӶ����а�˳����WM_KEYDOWN����Ϣ3.û�и�����Ϣ4.Ч�����Ŷӽ�����еȴ�����ȡ
		Sleep(2000);
		HDC hdc = GetDC(hWnd);
		static int j = 20;//����һ�������ڲ��ľ�̬��������������Ϊ�������ڣ�������Ϊ������j��������´��õ���ʱ�����ϴ��Ǹ�j
		//MessageBox(0, _T("��갴��"), _T("����"), 0);
		TextOut(hdc, 0, j, _T("��갴��"), 4);//��ʾ�ڴ��ڵ�(0,j)λ����ʾ����,4��ʾ�ַ��ĸ�����1.������ʾ��ȫ 2.����β������ 3.��Ӧ�ַ�����
		ReleaseDC(hWnd, hdc);
		j += 20;
	}
	break;
	case WM_KEYDOWN:
	{
		HDC hdc = GetDC(hWnd);
		static int k = 20;//����һ�������ڲ��ľ�̬��������������Ϊ�������ڣ�������Ϊ������j��������´��õ���ʱ�����ϴ��Ǹ�j
						  //MessageBox(0, _T("��갴��"), _T("����"), 0);
		TextOut(hdc, 200, k, _T("���̰���"), 4);//��ʾ�ڴ��ڵ�(0,j)λ����ʾ����,4��ʾ�ַ��ĸ�����1.������ʾ��ȫ 2.����β������ 3.��Ӧ�ַ�����
		ReleaseDC(hWnd, hdc);
		k += 20;
		//MessageBox(0, _T("���̰���"), _T("����"), 0);
	}
	break;
	//------------------
	//��ҵ������һ���Ի�����Ҫ���10�Σ�������ܽ���---------
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		static int i = 1;//����һ�������ڲ��ľ�̬��������������Ϊ�������ڣ�������Ϊ������j��������´��õ���ʱ�����ϴ��Ǹ�j
						  //MessageBox(0, _T("��갴��"), _T("����"), 0);
		TCHAR str[100] = { 0 };//��ʱ�ַ�������  charΪ���ֽ�  TCHARΪ���ֽ�����
								  //��ʽ���ַ���
		_stprintf_s(str, _T("��갴��%d��"), i);//1.swprintf_s�����ڿ��ֽ�buff���� 2.һ����spirntf���� 3._stprintf_sΪͨ��
		TextOut(hdc, 0, 20, str, _tcslen(str));//��ʾ�ڴ��ڵ�(0,j)λ����ʾ����,4��ʾ�ַ��ĸ�����1.������ʾ��ȫ 2.����β������ 3.��Ӧ�ַ����� ͨ��_tcslen����TCHAR�ַ��ĳ���4.ͬһλ�ûḲ��ԭ������
		ReleaseDC(hWnd, hdc);
		if (i == 10)
		{
			MessageBox(hWnd, TEXT("����Ѿ������10��"), L"����", 0);
		}
		i++;
	}
	break;
	//-----------------
    case WM_COMMAND://������Ϣ���������˵�����������Ϣ
        {
            int wmId = LOWORD(wParam);//�õ����ĸ��˵�/�ĸ�����
            // �����˵�ѡ��: 
            switch (wmId)
            {
				/*
				��¼����Դ��ͼ�Ĳ鿴(��Ҫ��Resource.h�رյ������)����ͼ--��������--��Դ��ͼ
				����Menu�ļ��� ˫��������ļ� �򿪲˵�����ͼ
				��׼�˵������Ҽ��Ϳ��Կ����ò˵�����������
				*/
            case IDM_ABOUT: //����
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT: //�˳�
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);//ϵͳ������windows������Ϣ�����������細�ڵ���󻯡���С��
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
    case WM_DESTROY: //IDM_EXIT��Ϣƥ�������PostQuitMessage����������Ϣ
        PostQuitMessage(0);//����������postһ��WM_QUIT��Ϣʹ��GetMessage/PeekMessage�õ�����Ϣ���˳�
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
