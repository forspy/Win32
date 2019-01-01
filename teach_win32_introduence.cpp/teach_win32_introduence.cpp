//win32表示 一次访问32位内存
//64位兼容32位 所以学习32位
//vs默认编辑器32位
//控制台与win32项目有什么区别？
/*
控制台：指令操作 看到值 c/c++ 数据结构
*/
//项目分为逻辑模块 和渲染（绘制）模块  图形界面 把想给用户看的东西表达出来
//1.window应用程序也有入口函数 WinMain
//2.windows里面也有自己的数据类型，这些数据类型都是C/C++类型的重定义
//3.windows数据类型都是大写
//4.Windows封装了C语言
#include<Windows.h>
#include<tchar.h>
#pragma comment(lib,"Winmm.lib")//播放音乐需要的库文件
int APIENTRY WinMain(_In_ HINSTANCE hInstance, //1.应用程序当前 实例句柄 //2.HINSTANCE 类似于void* 只给地址访问 不给大小 // 3. _In_修饰 表示hInstance是需要给进来的 不需要给出去 //4.句柄一般以H开头
	_In_opt_ HINSTANCE hPrevInstance,  //应用程序先前实例句柄 现在大多已经不用 设为NULL
	_In_ LPSTR lpCmdLine,//指向应用程序命令行的字符串指针，不包括执行文件名 //指针一般以P/LP开头 
	_In_ int nCmdShow)//指明窗口显示方式 ，假如SW_HIDE 隐藏窗口并且激活另外一个窗口
	//WINAPI 表示windows应用程序接口 表示修饰 
	//例如可以在cmd下运行一个实例1.txt C:\Windows>notpad.exe f:/1.txt  这时1.txt就是实例hInstance
{
	char a = '我';//从“int”到“char”截断 因为char表示一个英文字符，而'我'一个字符占两个字节,所以截断
	char a0 = 'a';
	wchar_t b = '我';//wchar_t为宽字节类型表示一个字符由两个字节组成，所以不会截断
	char *p1 = "我们";//字符指针类型
	wchar_t *p2 = L"你好";//宽字节字符指针类型,L表示宽字节
	TCHAR *p = L"爱的";//1.TCHAR为通配类型，在Unicode编码下TCHAR其实就是wchar_t,在多字节字符集中TCHAR就是char //2.L表示宽字节,在unicode的宽字节类型中要使用L
	
	TCHAR* p3 = _T("大家好");//_T()为通配带参宏，会根据Unicode还是多字节，自动选择要不要加L //2.需要头文件<tchar.h>
	//例如字符串处理函数 _tcscpy 当Unicode的时候变为wcscpy，多字节变成strcpy
	MessageBoxA(0, "hello", 0, 0);//A-多字节消息窗口
	MessageBoxW(0, 0, _T("标题"), 0);//W-unicode处理
	MessageBox(0, 0, 0, MB_OKCANCEL|MB_ICONWARNING);//通配函数
	/*
	int MessageBox(
	HWND    hWnd, //窗口句柄 一个void* 指向一个窗口
	LPCTSTR lpText, //对话框消息
	LPCTSTR lpCaption,//对话框标题
	UINT    uType//指示消息框中显示的按钮
    );
	*/
	//MessageBox其实是有返回值的
	if (MessageBox(0, 0, 0, MB_OKCANCEL)==IDOK)//1.消息盒子返回条件//2.如果不==IDOK不论怎么选都会返回"返回了确定"
		MessageBox(0, L"返回了确定", 0, MB_OKCANCEL);
	else
		MessageBox(0, L"返回了取消", 0, MB_OKCANCEL);

	/*
	MP3属于有损失的格式，牺牲音乐文件的质量以换取较小的文件体积；
WAV是无损的格式，标准格式化的WAV文件和CD格式一样，是44.1K的取样频率，16位量化数字，因此在声音文件质量和CD相当。
MP3是利用一种音频压缩技术，由于这种压缩方式的全称叫MPEG Audio Layer3，所以人们把它简称为MP3。因为人耳只能听到一定频段内的声音，而其他更高或更低频率的声音对人耳是没有用处的，所以MP3技术就把这部分声音去掉了，
从而使得文件体积大为缩小，但在人耳听起来， 却并没有什么失真。MP3可以将声音用1∶10甚至1∶12的压缩率进行压缩.
WAV格式是微软公司开发的一种声音文件格式，也叫波形声音文件，是最早的数字音频格式，被Windows平台及其应用程序广泛支持。WAV格式支持许多压缩算法，支持多种音频位数、采样频率和声道.
	*/

	//WAV格式音乐播放
	
	PlaySound(L"./倩女幽魂.wav", nullptr, SND_ASYNC|SND_LOOP| SND_FILENAME);//注意这里如果不写SND_ASYNCwindows会运行wav音乐，并且只能在进程中关掉，待解决，所以要加异步
	//SND_ASYNC表示声音以异步方式播放，PlaySound在开始播放后立即返回。 要终止异步播放的波形声音，请在pszSound设置为NULL的情况下调用PlaySound。
	//SND_LOOP表示声音重复播放，直到再次调用PlaySound并将pszSound参数设置为NULL。 如果设置了此标志，则还必须设置SND_ASYNC标志。
	//pszSound参数是文件名。 如果找不到该文件，除非设置了SND_NODEFAULT标志，否则该函数将播放默认声音。
	//Tips:无法解析的外部符号一般表示缺少头文件或者库文件
	//头文件中有函数的申明，库文件实现函数的定义。
	/*
   BOOL PlaySound(
   LPCTSTR pszSound, //文件名 LPCTSTR就是LPCWSTR 一般用相对路径
   HMODULE hmod,//应用程序实例句柄 HMODULE就是HINSTANCE  表示处理包含要加载的资源的可执行文件。 除非在fdwSound中指定了SND_RESOURCE，否则此参数必须为NULL。
   DWORD   fdwSound//DWORD就是unsigned long  用于播放声音的标志。 定义了一些值。
   );
	*/
	//MP3格式的音乐播放
	mciSendString(L"open ./路飞猛攻.mp3", nullptr, 0, nullptr);
	mciSendString(L"play ./路飞猛攻.mp3 repeat", nullptr, 0, nullptr);
	/*
   MCIERROR mciSendString(
   LPCTSTR lpszCommand,//MCI命令字符串
   LPTSTR  lpszReturnString,//指向接收返回信息的缓冲区的指针。 如果不需要返回信息，则此参数可以为NULL。
   UINT    cchReturn,//lpszReturnString参数指定的返回缓冲区的大小（以字符为单位）。
   HANDLE  hwndCallback//回调函数窗口句柄 如果在命令字符串中指定了“notify”标志，则处理回调窗口。 什么是回调函数 如果A()的函数里面使用了B()函数，那么B()称为A()的回调函数
   );
	*/
	MessageBox(0, 0, 0, 0);//因为PlaySound用了异步SND_ASYNC，防止一播放音乐就结束，相当于控制台里面的getchar()的功能,mciSendString也一样
}


//多字节字符集 1个字节表示一个英文字符  2个字节表示来表示一个中文字符 例如UTF-8 
//宽字节字符集 都用2个字节表示一个字符 wchar_t  例如：Unicode、GB2312 
/* 
多字节编码：char，string，CStringA。
Unicode编码：wchar_t，wstring，CStringW。//带W的为Unicode字符集 因为Unicode是宽字节字符集用W表示?
*/


/*
如果入口函数是wWinMain 对应LPWSTR
如果入口函数是WinMain 对应LPSTR
在Unicode字符集中 宏函数_tWinMain表示 wWinMain
*/

