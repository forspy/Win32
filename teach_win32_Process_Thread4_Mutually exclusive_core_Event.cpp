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


//�ں˶���
//�ں˶�������֪ͨ��δ֪ͨ����״̬��״̬���л���ϵͳ������
//���߳����еĹ����У��ں˶�����δ֪ͨ״̬�����߳̽���ʱ����Ϊ��֪ͨ״̬
//�ں˶���֮һ�¼�
//�¼�  �����ں˶����ͬ�����ƣ�һ��һ��������
//�¼��Ķ��壺�¼�����Ķ��壨��Ϊ�ò�����������ֻ��ȥ�þ����
HANDLE g_hEvent;

int ticket = 1000;//����ʮ��Ʊ��
void func(LPVOID param);

int main()
{
	//�¼��ĳ�ʼ��
	g_hEvent=CreateEvent(nullptr,//��ȫ����
		false,//�Զ�����(true)---��һ���̶߳���Դ�������ʱ�ں�ֻ֪ͨһ�������߳�;�ֶ�����(false) ��һ���̶߳���Դ�������ʱ�ں�ֻ֪ͨ���������߳�
		true,//�¼��ĳ�ʼ����trueΪ��֪ͨ
		nullptr//�¼��ں˶��������
		);
	/*
	HANDLE CreateEventA(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCSTR                lpName
);
	*/

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
		//�¼��ں� ---�ȴ�֪ͨ
		//��һ���߳���������ڴ��������ʱ���ں�״̬���Զ���Ϊδ֪ͨ
		WaitForSingleObject(g_hEvent,INFINITE/*��ʾһֱ�ȴ�*/);//�ȴ��ں��¼���֪ͨ���ȴ�ֱ���¼�״̬Ϊ��֪ͨ�����ǿ�g_hEvent�����Ӧ���ں��¼���״̬
		//����¼�ʹδ֪ͨ�����ʾ���߳���ռ�ã���WaitForSingleObject()�γ���������ֹ�����߳̽�������
		if (ticket > 0)
		{
			printf("��վ����%d��Ʊ\n", ticket);
			ticket--;
		}
		else
		{
			//�����������¼�֪ͨ
			SetEvent(g_hEvent);
			break;
		}
		//�����������¼�֪ͨ
		SetEvent(g_hEvent);
	}
	//�̵߳������˳�
	//1.�̺߳������������أ��Ƽ���
	//2.�����߳�ʹ��TerminateThread����ָ�������߳�
	//TerminateThread(handle1, 0);//���ܻᵼ����Դ�ͷŲ�����
	//3.����ExitThread����
	//ExitThread(0);


	CloseHandle(g_hEvent);//�ر��¼�
	//�¼����߳���ռƵ�ʱȽ�ƽ��[��Ҫ]
	//�ͷ��߳�
	TerminateThread(handle1, 0);
	TerminateThread(handle2, 0);
	return 0;//�����������
}

void func(LPVOID param)
{
	while (1)
	{
		WaitForSingleObject(g_hEvent, INFINITE/*��ʾһֱ�ȴ�*/);//�ȴ��ں��¼���֪ͨ���ȴ�ֱ���¼�״̬Ϊ��֪ͨ
		if (ticket > 0)
		{
			printf("��%d���۵�,����%d��Ʊ\n", (int)param, ticket);
			ticket--;
		}
		else
		{
			//�����������¼�֪ͨ
			SetEvent(g_hEvent);
			break;
		}
		//�����������¼�֪ͨ
		SetEvent(g_hEvent);
	}
}

////��10���ڴ渴�Ƶ�cpu�Ĵ��� 2.������Ϊ9 3.�ٴ�cpu�Ĵ������Ƶ��ڴ� 
//�����̶߳�������ռcpu�������߳�1��ռ����cpu���߳�1��Ҫ��ӡprintf() �����������Ҫʱ�������
//Ȼ����Ҫ--����ʱ�����̵�ʱ��Ƭ���ˣ�--��������ֹ
//���ű��类�߳�2������ �߳�2��ӡ Ȼ��--��ʱ��ʱ�䵽��
//�߳�1������ ����ִ��--
//������Ҫ�̼߳��ͨѶ���̵߳Ļ���