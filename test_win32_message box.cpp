#include<Windows.h> //windows��̵�ͷ�ļ�
#pragma comment(lib,"winmm.lib")

int WINAPI WinMain(HINSTANCE hInstance, //Ӧ�ó���ǰʵ�����
	HINSTANCE hPrevInstance,  //Ӧ�ó�����ǰʵ�����
	LPSTR lpCmdLine,//ָ��Ӧ�ó��������е��ַ���ָ�룬������ִ���ļ���
	int nCmdShow)//ָ�����������ʾ������SW_HIDE ���ش��ڲ��Ҽ�������һ������
{
	PlaySound(L"һ���쳾.wav", NULL, SND_FILENAME | SND_ASYNC);//mp3�����ܲ��ţ������
	//mciSendString(L"open ./bird.mp3", 0, 0, 0);//������
	//mciSendString(L"play ./bird.mp3 repeat", 0, 0, 0); //�ȴ� Ȼ�󲥷�
	MessageBox(NULL,/*û�д���*/L"����!", L"��ʾ", MB_YESNO| MB_ICONINFORMATION);//MB_OK  | MB_ICONERROR MB_ICONINFORMATION �ȿ����Լ���һ��

	return 0;
}
/*
2.�����Windows���� 
Windows����---- - ���ڡ�ͼ�ꡢ��ꡢ�˵��������� �е�Ӧ�ó���ʵ���ȵȡ�
�� ��---- - ϵͳ����Ψһ��ʶĳ��Windows�����һ ���޷����������൱��Windows��������֣�Ӧ�ó���ֻ��ͨ���������ʹ��Windows����
Ӧ�ó�����ͨ���㶨����ľ�������ʳ����и�������ġ����Ƕ��������ϵͳ�Զ�����̽��й���Ļ����ֶΡ�
*/