// teach_win32_Process_Thread2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>//创建线程用
//线程(函数)由两个部分组成
//1.操作系统内核对象 用来存放线程统计信息和管理
//2.线程堆栈 用来维护线程在执行代码中需要的函数参数和局部变量
//进程必然带一个入口函数，即主线程
//线程的生命周期会受到进程的影响，进程一旦死亡，里面的所有线程都会死亡
//线程的开销比进程少，进程是不活跃的，如果要去异步解决问题 尽量创建线程而不是进程
//魔兽世界跑地图会加载地图，加载玩家，需要去异步解决问题就是多线程


//内核对象
//内核对象处于已通知和未通知两种状态，状态的切换由系统来决定
//在线程运行的过程中，内核对象处于未通知状态，当线程结束时，变为已通知状态
//内核对象之一事件
//事件  基于内核对象的同步机制，一道一道工序来
//事件的定义：事件句柄的定义（因为拿不到对象，所以只能去拿句柄）
HANDLE g_hEvent;

int ticket = 1000;//定义十张票，
void func(LPVOID param);

int main()
{
	//事件的初始化
	g_hEvent=CreateEvent(nullptr,//安全属性
		false,//自动重置(true)---当一个线程对资源运算结束时内核只通知一个其他线程;手动重置(false) 当一个线程对资源运算结束时内核只通知所有其他线程
		true,//事件的初始化，true为已通知
		nullptr//事件内核对象的名称
		);
	/*
	HANDLE CreateEventA(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCSTR                lpName
);
	*/

	//创建一个线程
	int index = 1;
	HANDLE handle1 = CreateThread(nullptr,//指向一个结构LPSECURITY_ATTRIBUTES   ，必须为空
		0,//新线程的初始化堆栈大小，默认0
		(LPTHREAD_START_ROUTINE)func,//对应的线程函数名
		(LPVOID)index,//传给线程（回调）函数的参数
		0,//线程的参数
		nullptr//线程的ID,因为设置了句柄，所以不需要
	);
	index++;
	HANDLE handle2 = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)func, (LPVOID)index, 0, nullptr);
	while (1)
	{
		//事件内核 ---等待通知
		//当一个线程抢到这个内存进行运算时，内核状态会自动变为未通知
		WaitForSingleObject(g_hEvent,INFINITE/*表示一直等待*/);//等待内核事件的通知，等待直到事件状态为已通知，就是看g_hEvent句柄对应的内核事件的状态
		//如果事件使未通知，则表示有线程在占用，在WaitForSingleObject()形成阻塞，阻止其它线程进行运算
		if (ticket > 0)
		{
			printf("火车站卖出%d张票\n", ticket);
			ticket--;
		}
		else
		{
			//重新来设置事件通知
			SetEvent(g_hEvent);
			break;
		}
		//重新来设置事件通知
		SetEvent(g_hEvent);
	}
	//线程的三种退出
	//1.线程函数的主动返回（推荐）
	//2.在主线程使用TerminateThread结束指定的子线程
	//TerminateThread(handle1, 0);//可能会导致资源释放不彻底
	//3.调用ExitThread结束
	//ExitThread(0);


	CloseHandle(g_hEvent);//关闭事件
	//事件的线程抢占频率比较平均[重要]
	//释放线程
	TerminateThread(handle1, 0);
	TerminateThread(handle2, 0);
	return 0;//代表进程死亡
}

void func(LPVOID param)
{
	while (1)
	{
		WaitForSingleObject(g_hEvent, INFINITE/*表示一直等待*/);//等待内核事件的通知，等待直到事件状态为已通知
		if (ticket > 0)
		{
			printf("第%d代售点,卖出%d张票\n", (int)param, ticket);
			ticket--;
		}
		else
		{
			//重新来设置事件通知
			SetEvent(g_hEvent);
			break;
		}
		//重新来设置事件通知
		SetEvent(g_hEvent);
	}
}

////把10从内存复制到cpu寄存器 2.减减变为9 3.再从cpu寄存器复制到内存 
//各个线程都可以抢占cpu，假如线程1抢占到了cpu，线程1需要打印printf() 但是这个是需要时间运算的
//然后需要--，这时候量程的时间片到了，--操作被终止
//接着比如被线程2抢到了 线程2打印 然后--的时候时间到了
//线程1抢到了 继续执行--
//所以需要线程间的通讯，线程的互斥