#include<stdio.h>
#include<Windows.h>//�����߳���
//�߳�(����)�������������
//1.����ϵͳ�ں˶��� ��������߳�ͳ����Ϣ�͹���
//2.�̶߳�ջ ����ά���߳���ִ�д�������Ҫ�ĺ��������;ֲ�����
//���̱�Ȼ��һ����ں����������߳�
//�̵߳��������ڻ��ܵ����̵�Ӱ�죬����һ������������������̶߳�������
//�̵߳Ŀ����Ƚ����٣������ǲ���Ծ�ģ����Ҫȥ�첽������� ���������̶߳����ǽ���
//ħ�������ܵ�ͼ����ص�ͼ��������ң���Ҫȥ�첽���������Ƕ��߳�

//���̣߳��߳�ͨѶ
/*
1.����̷߳��ʹ�����Դ�����������������Դ���ƻ�
2.��һ���߳̽�ĳ���������֮�󣬲�֪ͨ��һ���߳�ȥ��������������
*/

//�̻߳���
//һ���û����� �����ں˶��󣨲�����ζ��ֻ���������̻߳��⣩--�����ں�
//һ����������

//����ϴ�ּ�ռ�����
//�ٽ��� --���� --���������Դ�����Ƿ�ʹ��  --�����û�
CRITICAL_SECTION g_cs;

/*
�ٽ�����������ṹ
typedef struct _RTL_CRITICAL_SECTION {
PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
LONG LockCount;
LONG RecursionCount;
HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
HANDLE LockSemaphore;
ULONG_PTR SpinCount;        // force size on 64-bit systems when packed
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;
*/
int ticket = 1000;//����ʮ��Ʊ��
void func(LPVOID param);

int main()
{
	//�ٽ��������ĳ�ʼ��
	InitializeCriticalSection(&g_cs);
	//����һ���߳�
	int index = 1;
	HANDLE handle1 = CreateThread(nullptr,//ָ��һ���ṹLPSECURITY_ATTRIBUTES   ������Ϊ��
		0,//���̵߳ĳ�ʼ����ջ��С��Ĭ��0
		(LPTHREAD_START_ROUTINE)func,//��Ӧ���̺߳�����
		(LPVOID)index,//�����̣߳��ص��������Ĳ���
		0,//�̵߳Ĳ���
		nullptr//�̵߳�ID,��Ϊ�����˾�������Բ���Ҫ
	);
	index++;
	HANDLE handle2 = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)func, (LPVOID)index, 0, nullptr);
	while (1)
	{
		EnterCriticalSection(&g_cs);//�ĸ��߳̽����ˣ�˭ռ�������Դ��ע���ٽ�����Χ
		if (ticket > 0)
		{
			printf("��վ����%d��Ʊ\n", ticket);
			ticket--;
		}
		else
		{
			LeaveCriticalSection(&g_cs);
			break;
		}
		LeaveCriticalSection(&g_cs);//�뿪�ٽ�����������̶߳������Դ��ռ��
	}
	//�̵߳������˳�
	//1.�̺߳������������أ��Ƽ���
	//2.�����߳�ʹ��TerminateThread����ָ�������߳�
	//TerminateThread(handle1, 0);//���ܻᵼ����Դ�ͷŲ�����
	//3.����ExitThread����
	//ExitThread(0);

	//�ͷ��ٽ�������
	DeleteCriticalSection(&g_cs);
	TerminateThread(handle1,0);
	TerminateThread(handle2, 0);
	//Ϊʲô��ͬ�߳�һ��һ�εĳ���?��Ϊ�߳������ȼ����Ի�ĳһ�߳�����һ��ʱ������ռ��Դ
	//��Ϊ���߳����ȼ��Ĺ�ϵ���ܻ�����߳����������ǿ�����ĳһ���ȼ��͵��߳���������Դ
	//����������ʱ����û����ɣ��ſ�����Դ�����ſ���ʱ����ס����Դ�����Բ�̫�����ٴ�������Դ���������γ��߳�����
	return 0;//���߳̽��������������������Դ�ͷţ����̱߳��Ƚ���
}

void func(LPVOID param)
{
	while (1)
	{
		EnterCriticalSection(&g_cs);
		if (ticket > 0)
		{
			printf("��%d���۵�,����%d��Ʊ\n", (int)param, ticket);
			ticket--;
		}
		else
		{
			LeaveCriticalSection(&g_cs);
			break;
		}
		LeaveCriticalSection(&g_cs);//������̶߳������Դ��ռ��
	}
}
////��10���ڴ渴�Ƶ�cpu�Ĵ��� 2.������Ϊ9 3.�ٴ�cpu�Ĵ������Ƶ��ڴ� 
//�����̶߳�������ռcpu�������߳�1��ռ����cpu���߳�1��Ҫ��ӡprintf() �����������Ҫʱ�������
//Ȼ����Ҫ--����ʱ�����̵�ʱ��Ƭ���ˣ�--��������ֹ
//���ű��类�߳�2������ �߳�2��ӡ Ȼ��--��ʱ��ʱ�䵽��
//�߳�1������ ����ִ��--
//������Ҫ�̼߳��ͨѶ���̵߳Ļ���