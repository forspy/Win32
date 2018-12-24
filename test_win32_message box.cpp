#include<Windows.h> //windows编程的头文件
#pragma comment(lib,"winmm.lib")

int WINAPI WinMain(HINSTANCE hInstance, //应用程序当前实例句柄
	HINSTANCE hPrevInstance,  //应用程序先前实例句柄
	LPSTR lpCmdLine,//指向应用程序命令行的字符串指针，不包括执行文件名
	int nCmdShow)//指明窗口如何显示，假如SW_HIDE 隐藏窗口并且激活另外一个窗口
{
	PlaySound(L"一曲红尘.wav", NULL, SND_FILENAME | SND_ASYNC);//mp3好像不能播放，待解决
	//mciSendString(L"open ./bird.mp3", 0, 0, 0);//打开音乐
	//mciSendString(L"play ./bird.mp3 repeat", 0, 0, 0); //先打开 然后播放
	MessageBox(NULL,/*没有窗口*/L"加油!", L"提示", MB_YESNO| MB_ICONINFORMATION);//MB_OK  | MB_ICONERROR MB_ICONINFORMATION 等可以自己试一下

	return 0;
}
/*
2.句柄和Windows对象 
Windows对象---- - 窗口、图标、光标、菜单及正在运 行的应用程序实例等等。
句 柄---- - 系统用来唯一标识某个Windows对象的一 个无符号整数，相当于Windows对象的名字，应用程序只有通过句柄才能使用Windows对象。
应用程序是通过恒定不变的句柄来访问程序中各个对象的。这是多任务操作系统对多个进程进行管理的基本手段。
*/