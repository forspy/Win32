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
int ticket = 10;//����ʮ��Ʊ��
void func1(LPVOID param);
void func2(LPVOID param);
int main()
{
	//����һ���߳�
	int index = 1;
	HANDLE handle1=CreateThread(nullptr,//ָ��һ���ṹLPSECURITY_ATTRIBUTES   ������Ϊ��
		0,//���̵߳ĳ�ʼ����ջ��С��Ĭ��0
		(LPTHREAD_START_ROUTINE)func1,//��Ӧ���̺߳�����
		(LPVOID)index,//�����̣߳��ص��������Ĳ���
		0,//�̵߳Ĳ���
		nullptr//�̵߳�ID,��Ϊ�����˾�������Բ���Ҫ
	);
	index++;
	HANDLE handle2 = CreateThread(nullptr,0,(LPTHREAD_START_ROUTINE)func2,(LPVOID)index,0,nullptr);
	while (1)
	{
		if (ticket > 0)
		{
			printf("��վ����%d��Ʊ\n", ticket);
			ticket--;
		}
		else
		{
			break;
		}
	}
	//�̵߳������˳�
	//1.�̺߳������������أ��Ƽ���
	//2.�����߳�ʹ��TerminateThread����ָ�������߳�
	//TerminateThread(handle1, 0);//���ܻᵼ����Դ�ͷŲ�����
	//3.����ExitThread����
	//ExitThread(0);
    return 0;//�����������
}

void func1(LPVOID param)
{
	while (1)
	{
		if (ticket > 0)
		{
			printf("��%d���۵�,����%d��Ʊ\n", (int)param, ticket);
			ticket--;
		}
		else
		{
			break;
		}
	}
}
void func2(LPVOID param)
{
	while (1)
	{
		if (ticket > 0)
		{
			printf("��%d���۵�,����%d��Ʊ\n", (int)param, ticket);
			ticket--;
		}
		else
		{
			break;
		}
	}
}
////��10���ڴ渴�Ƶ�cpu�Ĵ��� 2.������Ϊ9 3.�ٴ�cpu�Ĵ������Ƶ��ڴ� 
//�����̶߳�������ռcpu�������߳�1��ռ����cpu���߳�1��Ҫ��ӡprintf() �����������Ҫʱ�������
//Ȼ����Ҫ--����ʱ�����̵�ʱ��Ƭ���ˣ�--��������ֹ
//���ű��类�߳�2������ �߳�2��ӡ Ȼ��--��ʱ��ʱ�䵽��
//�߳�1������ ����ִ��--
//������Ҫ�̼߳��ͨѶ���̵߳Ļ���