// teach_win32_Process_Thread2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<Windows.h>//�����߳���
//�߳�(����)�������������
//1.����ϵͳ�ں˶��� ��������߳�ͳ����Ϣ�͹���
//2.�̶߳�ջ ����ά���߳���ִ�д�������Ҫ�ĺ��������;ֲ�����
//���̱�Ȼ��һ����ں����������߳�
//�̵߳��������ڻ��ܵ����̵�Ӱ�죬����һ������������������̶߳�������
//�̵߳Ŀ����Ƚ����٣������ǲ���Ծ�ģ����Ҫȥ�첽������� ���������̶߳����ǽ���
//ħ�������ܵ�ͼ����ص�ͼ��������ң���Ҫȥ�첽���������Ƕ��߳�

//�ź������Կ�����Դ�ļ�����  ����ͼ��ݽ���ϵͳ ��ʾ�ɽ��ĵ���ı����� 
/*
1.��ǰ��Դ����0�������ź�
2.����0 �������ź�
*/
//ע��ֻ�������ͬһ��Դʱ��Ҫ�����̻߳���
HANDLE g_hSemaphore;

int ticket = 100;//����ʮ��Ʊ��
void func(LPVOID param);

int main()
{
	g_hSemaphore = CreateSemaphore(nullptr,//��ȫ����
		1,//��ǰ��Դ����
		1,//�����Դ����
		nullptr
	);//�����ź���
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
		WaitForSingleObject(g_hSemaphore, INFINITE);//�̵߳ȴ��ں��ź�
		if (ticket > 0)
		{
			printf("��վ����%d��Ʊ\n", ticket);
			ticket--;
		}
		else
		{
			ReleaseSemaphore(g_hSemaphore, 1,/*���õ�ǰ����Դ����*/nullptr);
			break;
		}
		ReleaseSemaphore(g_hSemaphore, 1,/*���õ�ǰ����Դ����*/nullptr);
	}
	//�̵߳������˳�
	//1.�̺߳������������أ��Ƽ���
	//2.�����߳�ʹ��TerminateThread����ָ�������߳�
	//TerminateThread(handle1, 0);//���ܻᵼ����Դ�ͷŲ�����
	//3.����ExitThread����
	//ExitThread(0);
	CloseHandle(g_hSemaphore);

	//�̵߳�ͨ�� ---��Ҫȷ���߳�ִ������Դ������Ž���
	DWORD threadExitCode1, threadExitCode2;//�߳��˳���
	while (true)
	{
		GetExitCodeThread(handle1, &threadExitCode1);//���߳��˳������threadExitCode1��
		GetExitCodeThread(handle2, &threadExitCode2);

		if (threadExitCode1 != STILL_ACTIVE&&threadExitCode2 != STILL_ACTIVE)
			break;
	}

	TerminateThread(handle1, 0);
	TerminateThread(handle2, 0);
	//Ҳ�ǽ�Ϊ���� ���� �ں˶�������̵߳ķ��䶼��Ϊ����
	return 0;//�����������
}

void func(LPVOID param)
{
	while (1)
	{
		WaitForSingleObject(g_hSemaphore, INFINITE);//�̵߳ȴ��ں��ź�
		if (ticket > 0)
		{
			printf("��%d���۵�,����%d��Ʊ\n", (int)param, ticket);
			ticket--;
		}
		else
		{
			ReleaseSemaphore(g_hSemaphore, 1,/*���õ�ǰ����Դ����*/nullptr);
			break;
		}
		ReleaseSemaphore(g_hSemaphore, 1,/*���õ�ǰ����Դ����*/nullptr);
	}
}

////��10���ڴ渴�Ƶ�cpu�Ĵ��� 2.������Ϊ9 3.�ٴ�cpu�Ĵ������Ƶ��ڴ� 
//�����̶߳�������ռcpu�������߳�1��ռ����cpu���߳�1��Ҫ��ӡprintf() �����������Ҫʱ�������
//Ȼ����Ҫ--����ʱ�����̵�ʱ��Ƭ���ˣ�--��������ֹ
//���ű��类�߳�2������ �߳�2��ӡ Ȼ��--��ʱ��ʱ�䵽��
//�߳�1������ ����ִ��--
//������Ҫ�̼߳��ͨѶ���̵߳Ļ���