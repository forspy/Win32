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

//信号量（对可用资源的计数）  类似图书馆借书系统 表示可借阅的书的本数： 
/*
1.当前资源大于0，发出信号
2.等于0 不发出信号
*/
//注意只有在针对同一资源时需要考虑线程互斥
HANDLE g_hSemaphore;

int ticket = 100;//定义十张票，
void func(LPVOID param);

int main()
{
	g_hSemaphore = CreateSemaphore(nullptr,//安全属性
		1,//当前资源数量
		1,//最大资源数量
		nullptr
	);//创建信号量
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
		WaitForSingleObject(g_hSemaphore, INFINITE);//线程等待内核信号
		if (ticket > 0)
		{
			printf("火车站卖出%d张票\n", ticket);
			ticket--;
		}
		else
		{
			ReleaseSemaphore(g_hSemaphore, 1,/*重置当前的资源数量*/nullptr);
			break;
		}
		ReleaseSemaphore(g_hSemaphore, 1,/*重置当前的资源数量*/nullptr);
	}
	//线程的三种退出
	//1.线程函数的主动返回（推荐）
	//2.在主线程使用TerminateThread结束指定的子线程
	//TerminateThread(handle1, 0);//可能会导致资源释放不彻底
	//3.调用ExitThread结束
	//ExitThread(0);
	CloseHandle(g_hSemaphore);

	//线程的通信 ---需要确保线程执行完资源的运算才结束
	DWORD threadExitCode1, threadExitCode2;//线程退出码
	while (true)
	{
		GetExitCodeThread(handle1, &threadExitCode1);//把线程退出码放在threadExitCode1中
		GetExitCodeThread(handle2, &threadExitCode2);

		if (threadExitCode1 != STILL_ACTIVE&&threadExitCode2 != STILL_ACTIVE)
			break;
	}

	TerminateThread(handle1, 0);
	TerminateThread(handle2, 0);
	//也是较为均价 综上 内核对象对于线程的分配都较为均匀
	return 0;//代表进程死亡
}

void func(LPVOID param)
{
	while (1)
	{
		WaitForSingleObject(g_hSemaphore, INFINITE);//线程等待内核信号
		if (ticket > 0)
		{
			printf("第%d代售点,卖出%d张票\n", (int)param, ticket);
			ticket--;
		}
		else
		{
			ReleaseSemaphore(g_hSemaphore, 1,/*重置当前的资源数量*/nullptr);
			break;
		}
		ReleaseSemaphore(g_hSemaphore, 1,/*重置当前的资源数量*/nullptr);
	}
}

////把10从内存复制到cpu寄存器 2.减减变为9 3.再从cpu寄存器复制到内存 
//各个线程都可以抢占cpu，假如线程1抢占到了cpu，线程1需要打印printf() 但是这个是需要时间运算的
//然后需要--，这时候量程的时间片到了，--操作被终止
//接着比如被线程2抢到了 线程2打印 然后--的时候时间到了
//线程1抢到了 继续执行--
//所以需要线程间的通讯，线程的互斥