//win32��ʾ һ�η���32λ�ڴ�
//64λ����32λ ����ѧϰ32λ
//vsĬ�ϱ༭��32λ
//����̨��win32��Ŀ��ʲô����
/*
����̨��ָ����� ����ֵ c/c++ ���ݽṹ
*/
//��Ŀ��Ϊ�߼�ģ�� ����Ⱦ�����ƣ�ģ��  ͼ�ν��� ������û����Ķ���������
//1.windowӦ�ó���Ҳ����ں��� WinMain
//2.windows����Ҳ���Լ����������ͣ���Щ�������Ͷ���C/C++���͵��ض���
//3.windows�������Ͷ��Ǵ�д
//4.Windows��װ��C����
#include<Windows.h>
#include<tchar.h>
#pragma comment(lib,"Winmm.lib")//����������Ҫ�Ŀ��ļ�
int APIENTRY WinMain(_In_ HINSTANCE hInstance, //1.Ӧ�ó���ǰ ʵ����� //2.HINSTANCE ������void* ֻ����ַ���� ������С // 3. _In_���� ��ʾhInstance����Ҫ�������� ����Ҫ����ȥ //4.���һ����H��ͷ
	_In_opt_ HINSTANCE hPrevInstance,  //Ӧ�ó�����ǰʵ����� ���ڴ���Ѿ����� ��ΪNULL
	_In_ LPSTR lpCmdLine,//ָ��Ӧ�ó��������е��ַ���ָ�룬������ִ���ļ��� //ָ��һ����P/LP��ͷ 
	_In_ int nCmdShow)//ָ��������ʾ��ʽ ������SW_HIDE ���ش��ڲ��Ҽ�������һ������
	//WINAPI ��ʾwindowsӦ�ó���ӿ� ��ʾ���� 
	//���������cmd������һ��ʵ��1.txt C:\Windows>notpad.exe f:/1.txt  ��ʱ1.txt����ʵ��hInstance
{
	char a = '��';//�ӡ�int������char���ض� ��Ϊchar��ʾһ��Ӣ���ַ�����'��'һ���ַ�ռ�����ֽ�,���Խض�
	char a0 = 'a';
	wchar_t b = '��';//wchar_tΪ���ֽ����ͱ�ʾһ���ַ��������ֽ���ɣ����Բ���ض�
	char *p1 = "����";//�ַ�ָ������
	wchar_t *p2 = L"���";//���ֽ��ַ�ָ������,L��ʾ���ֽ�
	TCHAR *p = L"����";//1.TCHARΪͨ�����ͣ���Unicode������TCHAR��ʵ����wchar_t,�ڶ��ֽ��ַ�����TCHAR����char //2.L��ʾ���ֽ�,��unicode�Ŀ��ֽ�������Ҫʹ��L
	
	TCHAR* p3 = _T("��Һ�");//_T()Ϊͨ����κ꣬�����Unicode���Ƕ��ֽڣ��Զ�ѡ��Ҫ��Ҫ��L //2.��Ҫͷ�ļ�<tchar.h>
	//�����ַ��������� _tcscpy ��Unicode��ʱ���Ϊwcscpy�����ֽڱ��strcpy
	MessageBoxA(0, "hello", 0, 0);//A-���ֽ���Ϣ����
	MessageBoxW(0, 0, _T("����"), 0);//W-unicode����
	MessageBox(0, 0, 0, MB_OKCANCEL|MB_ICONWARNING);//ͨ�亯��
	/*
	int MessageBox(
	HWND    hWnd, //���ھ�� һ��void* ָ��һ������
	LPCTSTR lpText, //�Ի�����Ϣ
	LPCTSTR lpCaption,//�Ի������
	UINT    uType//ָʾ��Ϣ������ʾ�İ�ť
    );
	*/
	//MessageBox��ʵ���з���ֵ��
	if (MessageBox(0, 0, 0, MB_OKCANCEL)==IDOK)//1.��Ϣ���ӷ�������//2.�����==IDOK������ôѡ���᷵��"������ȷ��"
		MessageBox(0, L"������ȷ��", 0, MB_OKCANCEL);
	else
		MessageBox(0, L"������ȡ��", 0, MB_OKCANCEL);

	/*
	MP3��������ʧ�ĸ�ʽ�����������ļ��������Ի�ȡ��С���ļ������
WAV������ĸ�ʽ����׼��ʽ����WAV�ļ���CD��ʽһ������44.1K��ȡ��Ƶ�ʣ�16λ�������֣�����������ļ�������CD�൱��
MP3������һ����Ƶѹ����������������ѹ����ʽ��ȫ�ƽ�MPEG Audio Layer3���������ǰ������ΪMP3����Ϊ�˶�ֻ������һ��Ƶ���ڵ����������������߻����Ƶ�ʵ��������˶���û���ô��ģ�����MP3�����Ͱ��ⲿ������ȥ���ˣ�
�Ӷ�ʹ���ļ������Ϊ��С�������˶��������� ȴ��û��ʲôʧ�档MP3���Խ�������1��10����1��12��ѹ���ʽ���ѹ��.
WAV��ʽ��΢��˾������һ�������ļ���ʽ��Ҳ�в��������ļ����������������Ƶ��ʽ����Windowsƽ̨����Ӧ�ó���㷺֧�֡�WAV��ʽ֧�����ѹ���㷨��֧�ֶ�����Ƶλ��������Ƶ�ʺ�����.
	*/

	//WAV��ʽ���ֲ���
	
	PlaySound(L"./ٻŮ�Ļ�.wav", nullptr, SND_ASYNC|SND_LOOP| SND_FILENAME);//ע�����������дSND_ASYNCwindows������wav���֣�����ֻ���ڽ����йص��������������Ҫ���첽
	//SND_ASYNC��ʾ�������첽��ʽ���ţ�PlaySound�ڿ�ʼ���ź��������ء� Ҫ��ֹ�첽���ŵĲ�������������pszSound����ΪNULL������µ���PlaySound��
	//SND_LOOP��ʾ�����ظ����ţ�ֱ���ٴε���PlaySound����pszSound��������ΪNULL�� ��������˴˱�־���򻹱�������SND_ASYNC��־��
	//pszSound�������ļ����� ����Ҳ������ļ�������������SND_NODEFAULT��־������ú���������Ĭ��������
	//Tips:�޷��������ⲿ����һ���ʾȱ��ͷ�ļ����߿��ļ�
	//ͷ�ļ����к��������������ļ�ʵ�ֺ����Ķ��塣
	/*
   BOOL PlaySound(
   LPCTSTR pszSound, //�ļ��� LPCTSTR����LPCWSTR һ�������·��
   HMODULE hmod,//Ӧ�ó���ʵ����� HMODULE����HINSTANCE  ��ʾ�������Ҫ���ص���Դ�Ŀ�ִ���ļ��� ������fdwSound��ָ����SND_RESOURCE������˲�������ΪNULL��
   DWORD   fdwSound//DWORD����unsigned long  ���ڲ��������ı�־�� ������һЩֵ��
   );
	*/
	//MP3��ʽ�����ֲ���
	mciSendString(L"open ./·���͹�.mp3", nullptr, 0, nullptr);
	mciSendString(L"play ./·���͹�.mp3 repeat", nullptr, 0, nullptr);
	/*
   MCIERROR mciSendString(
   LPCTSTR lpszCommand,//MCI�����ַ���
   LPTSTR  lpszReturnString,//ָ����շ�����Ϣ�Ļ�������ָ�롣 �������Ҫ������Ϣ����˲�������ΪNULL��
   UINT    cchReturn,//lpszReturnString����ָ���ķ��ػ������Ĵ�С�����ַ�Ϊ��λ����
   HANDLE  hwndCallback//�ص��������ھ�� ����������ַ�����ָ���ˡ�notify����־������ص����ڡ� ʲô�ǻص����� ���A()�ĺ�������ʹ����B()��������ôB()��ΪA()�Ļص�����
   );
	*/
	MessageBox(0, 0, 0, 0);//��ΪPlaySound�����첽SND_ASYNC����ֹһ�������־ͽ������൱�ڿ���̨�����getchar()�Ĺ���,mciSendStringҲһ��
}


//���ֽ��ַ��� 1���ֽڱ�ʾһ��Ӣ���ַ�  2���ֽڱ�ʾ����ʾһ�������ַ� ����UTF-8 
//���ֽ��ַ��� ����2���ֽڱ�ʾһ���ַ� wchar_t  ���磺Unicode��GB2312 
/* 
���ֽڱ��룺char��string��CStringA��
Unicode���룺wchar_t��wstring��CStringW��//��W��ΪUnicode�ַ��� ��ΪUnicode�ǿ��ֽ��ַ�����W��ʾ?
*/


/*
�����ں�����wWinMain ��ӦLPWSTR
�����ں�����WinMain ��ӦLPSTR
��Unicode�ַ����� �꺯��_tWinMain��ʾ wWinMain
*/

