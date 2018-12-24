/*
Win32�������

// ��������ļ�windows.h�����ļ�����������windowsͷ�ļ�

WINDEF.H       �������Ͷ���
WINNT.H		   ֧��Unicode���Ͷ���
WINBASE.H      �ں˺���
WINGDI.H       ͼ���豸�ӿں���
WINUSER.H      �û��ӿں���
*/
#include<Windows.h>
/*
���ڶ�����̵Ĵ�����
LRESULT      ����ΪLONG(long)
CALLBACK     __stdcall��ָ��windows������û���Ӧ�ó���֮�䷢���ĺ������õ������������
HWND         ���ھ�� 32λ���֣��ò���Ϊ������Ϣ�Ĵ��ھ����CreateWindoww��������ֵ��
UINT         unsigned int �޷�������32λ
WPARAM       UINT��32λ��Ϣ����
LPARAM       LONG��32λ��Ϣ����
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WindowsӦ�ó������ں���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance/*һ��ΪNULL*/, PSTR lpszCmdLine, int iCmdShow)
{
	/*
	���崰����
	TCHAR:char
	_T��TEXT�꣬����һ��ͨ��û�У���Unicodeϵͳ�У�
	�Զ��Ѻ�����ַ���ת��Ϊ���ַ���
	*/
	TCHAR tcClassName[] = TEXT("MySeondProgramming");   // ���������ַ�

	//����һ��������ṹ������ṹ�����ж�����ڵ����Զ���ͨ������Щ����ֵ���ı䴰�ڵ�����
	WNDCLASS wndclass;//
	//������������
	wndclass.lpszClassName = tcClassName;//��������
	wndclass.lpszMenuName = nullptr;//������˵���Դ����
	wndclass.hInstance = hInstance;//��ǰ���̶�����������WinMain����
	wndclass.lpfnWndProc = WndProc;                                 // ���ڶ���Ĺ��̴�������ָ������ָ��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���ڱ���ˢ�Ӷ���
	wndclass.hIcon=(HICON)::LoadImage(NULL, L"CaptionICO.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); 
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                 // ������
	wndclass.cbClsExtra = 0;                                        // ͬ�ര�ڶ��󹫹���������С
	wndclass.cbWndExtra = 0;                                        // ��ǰ���ڶ���˽����������С
	wndclass.style = CS_HREDRAW | CS_VREDRAW;                       // ��������ˮƽ��ֱ�ߴ�ı��ˢ��

	// ע�ᴰ����  ����Ϊָ��WNDCLASS�ṹ��ָ��
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("RegisterClass ERROR."), TEXT("ERROR"), MB_ICONERROR);

		return 0;                                                   //  ���ע��ʧ�ܣ����ز���ֹ����
	}

	// ���崰�ڶ�������  ָ���йش��ڲ�����ϸ����
	TCHAR tcWindowCaptionName[] = TEXT("Windows�������");    // ���ڶ����������
	CREATESTRUCT cs;//// ���ڶ������������ṹ
	cs.lpszClass = tcClassName;// ��������
	cs.lpszName = tcWindowCaptionName; // ���ڶ���������ƣ���ʾ�ڱ�����
	cs.style = WS_OVERLAPPEDWINDOW;// ���ڶ�����
	cs.x = 100;// ���ڶ�������Ļ�ϵ�x����
	cs.y = 200;// ���ڶ�������Ļ�ϵ�y����
	cs.cx = 500;// ���ڶ���Ŀ��
	cs.cy = 400;// ���ڶ���ĸ߶�
	cs.hwndParent = NULL; // ���ڶ���ĸ����ھ�� 
	cs.hMenu = NULL;  // ���ڶ���˵�������Ӵ��ڱ��
	cs.hInstance = hInstance; // ��ǰ���� ʵ�������WinMain����
	cs.lpCreateParams = NULL;   // ��������ָ�룬���Է����Ժ���Ҫ���õĳ����е�����

	/*
	�������ڶ���
	���崰�ھ��hWnd��ֵΪCreateWindow�����ķ���ֵ
	�����ɹ����ش��ھ�������򷵻�NULL
	*/
	HWND hWnd = CreateWindow(cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy, 
		cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
	// �жϴ��ڴ����Ƿ�ɹ�
	if (hWnd == NULL)
	{
		MessageBox(NULL, TEXT("CreateWindow ERROR."), TEXT("ERROR"), MB_ICONERROR);

		return 0;
	}
	// ��ʾ����
	ShowWindow(hWnd, iCmdShow);//iCmdShowָ�����������ʾ������SW_HIDE ���ش��ڲ��Ҽ�������һ������
	// ���´���
	UpdateWindow(hWnd);
	// ��Ϣѭ��������������ڲŲ���һ������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);  // ��msg�ṹ���ݸ�windows���������������Ϣ��ת��
		DispatchMessage(&msg);   // ������Ϣ���ɴ˲���ϵͳ���� ��Ӧ�Ĵ��ڹ��̴�����Ϣ
	}
	// �����ڷ���
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		/*
		PAINTSTRUCT  ��ͼ�ṹ��������WINUSER.H��
		HDC ���νṹ
		RECT �豸��������
		*/
		PAINTSTRUCT ps;
		HDC hDC;
		RECT rect;

		hDC = BeginPaint(hWnd, &ps);        // ��ȡ��ʾ�豸���󼰻�����������
		GetClientRect(hWnd, &rect);         //  ��ȡ��ǰ���ڶ���ͻ�������
		SetBkMode(hDC, TRANSPARENT);        // ���ñ�����ʽ 
		SetTextColor(hDC, RGB(255, 0, 0));  // �����ļ���ɫ

											// �����ļ�
		DrawText(hDC, TEXT("Windows�������"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hWnd, &ps);                // �ͻ������ƽ������黹��ʾ�豸����

		return 0;
	}
	case WM_DESTROY:
	{
		// ����WM_QUIT��Ϣ��֪ͨ�߳���Ϣ����ѭ���������������������˳�
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
