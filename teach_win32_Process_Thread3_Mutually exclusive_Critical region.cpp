#include<stdio.h>
#include<Windows.h>//创建线程用
//线程(函数)由两个部分组成
//1.操作系统内核对象 用来存放线程统计信息和管理
//2.线程堆栈 用来维护线程在执行代码中需要的函数参数和局部变量
//进程必然带一个入口函数，即主线程
//线程的生命周期会受到进程的影响，进程一旦死亡，里面的所有线程都会死亡
//线程的开销比进程少，进程是不活跃的，如果要去异步解决问题 尽量创建线程而不是进程
//魔兽世界跑地图会加载地图，加载玩家，需要去异步解决问题就是多线程

//多线程：线程通讯
/*
1.多个线程访问共享资源而不能让这个共享资源被破环
2.当一个线程将某个任务完成之后，才通知另一个线程去继续完成这个任务
*/

//线程互斥
//一、用户区间 二、内核对象（并不意味着只能用来做线程互斥）--属于内核
//一、户用区间

//高铁洗手间占用情况
//临界区 --变量 --用来标记资源变量是否被使用  --属于用户
CRITICAL_SECTION g_cs;

/*
临界区变量对象结构
typedef struct _RTL_CRITICAL_SECTION {
PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
LONG LockCount;
LONG RecursionCount;
HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
HANDLE LockSemaphore;
ULONG_PTR SpinCount;        // force size on 64-bit systems when packed
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;
*/
int ticket = 1000;//定义十张票，
void func(LPVOID param);

int main()
{
	//临界区变量的初始化
	InitializeCriticalSection(&g_cs);
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
		EnterCriticalSection(&g_cs);//哪个线程进入了，谁占领这个资源，注意临界区范围
		if (ticket > 0)
		{
			printf("火车站卖出%d张票\n", ticket);
			ticket--;
		}
		else
		{
			LeaveCriticalSection(&g_cs);
			break;
		}
		LeaveCriticalSection(&g_cs);//离开临界区，解除该线程堆这个资源的占用
	}
	//线程的三种退出
	//1.线程函数的主动返回（推荐）
	//2.在主线程使用TerminateThread结束指定的子线程
	//TerminateThread(handle1, 0);//可能会导致资源释放不彻底
	//3.调用ExitThread结束
	//ExitThread(0);

	//释放临界区变量
	DeleteCriticalSection(&g_cs);
	TerminateThread(handle1,0);
	TerminateThread(handle2, 0);
	//为什么不同线程一段一段的出现?因为线程有优先级所以会某一线程连续一段时间内抢占资源
	//因为有线程优先级的关系可能会出现线程死锁，但是可能有某一优先级低的线程抢到了资源
	//但是在量程时间内没有完成，放开了资源，但放开的时候锁住了资源，所以不太容易再次抢到资源，这样会形成线程锁死
	return 0;//主线程结束，代表进程死亡，资源释放，子线程被迫结束
}

void func(LPVOID param)
{
	while (1)
	{
		EnterCriticalSection(&g_cs);
		if (ticket > 0)
		{
			printf("第%d代售点,卖出%d张票\n", (int)param, ticket);
			ticket--;
		}
		else
		{
			LeaveCriticalSection(&g_cs);
			break;
		}
		LeaveCriticalSection(&g_cs);//解除该线程堆这个资源的占用
	}
}
////把10从内存复制到cpu寄存器 2.减减变为9 3.再从cpu寄存器复制到内存 
//各个线程都可以抢占cpu，假如线程1抢占到了cpu，线程1需要打印printf() 但是这个是需要时间运算的
//然后需要--，这时候量程的时间片到了，--操作被终止
//接着比如被线程2抢到了 线程2打印 然后--的时候时间到了
//线程1抢到了 继续执行--
//所以需要线程间的通讯，线程的互斥