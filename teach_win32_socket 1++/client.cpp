// client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<WinSock2.h>//windows sockect头文件
#pragma comment(lib,"ws2_32.lib")//socket库文件
void receiveMessage();
SOCKET g_severSocket;
int main()
{
	//0.确定版本信息
	WSADATA wsaDATA;//结构体--版本信息
	WSAStartup(MAKEWORD(2, 2), &wsaDATA);//Windows 异步socket启动命令 MAKEWORD(修订版低一字节，主版本高一字节)//待解决
										 /*
										 int WSAStartup(
										 WORD      wVersionRequired,//版本号 高阶字节为修订版，低阶字节为主版本 例如2.2
										 LPWSADATA lpWSAData//字符指针，指向版本的信息
										 );成功返回0
										 DWORD(unsigned long);
										 WORD(unsigned short);
										 */
										 //printf("%d\n", LOBYTE(wsaDATA.wVersion));
										 //printf("%d\n", HIBYTE(wsaDATA.wVersion));
	if (LOBYTE(wsaDATA.wVersion) != 2 || HIBYTE(wsaDATA.wVersion) != 2)
	{
		printf("请求版本失败\n");
		return -1;
	}

	//1.创建socket
	SOCKET severSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	/*
	SOCKET WSAAPI socket(
	int af,//地址族规范,决定了socket的地址类型 AF_INET AF_INET6   ,AF_INET表示ipv4地址（32位），端口号（16位）
	int type,//socket的传输类型 SOCK_STREAM SOCK_DGRAM SOCK_RAW
	int protocol//指定协议 IPPROTO_ICMP IPPROTO_TCP IPPROTO_UDP
	);
	*/
	//SOCKET实质上是一个unsigned int 用来标记
	if (severSocket == INVALID_SOCKET)
	{
		printf("socket创建失败\n");
		WSACleanup();//关闭socket请求
		return -1;
	}

	//初始化协议
	SOCKADDR_IN clientAddr = { 0 };
	/*
	typedef struct sockaddr_in {

	#if(_WIN32_WINNT < 0x0600)
	short   sin_family;
	#else //(_WIN32_WINNT < 0x0600)
	ADDRESS_FAMILY sin_family;//地址族
	#endif //(_WIN32_WINNT < 0x0600)

	USHORT sin_port;//端口
	IN_ADDR sin_addr;//点分格式ip地址
	CHAR sin_zero[8];
	} SOCKADDR_IN, *PSOCKADDR_IN;
	*/
	clientAddr.sin_family = AF_INET;
	//存储端口号，注意：网络上的数值方式（大端：先存高位再存低位）和pc的数值方式（小端：先存低位再存高位）是有区别的,通过htons来转换
	clientAddr.sin_port = htons(8888);//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
									 //存储ip地址，利用inet_addr()转换成4字节
	clientAddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.4");//服务端的IP地址 



	//4.(客户端)连接
	int clientConnect = connect(severSocket, (sockaddr*)&clientAddr, sizeof(clientAddr));//建立于服务器的连接，severSocket连接的时候用的是服务端的ip及端口
	/*The connect function establishes a connection to a specified socket.
	int WSAAPI connect(
  SOCKET         s,
  const sockaddr *name,
  int            namelen
);
	*/
	if (clientConnect == SOCKET_ERROR)
	{
		printf("socket连接失败\n");
		closesocket(severSocket);//先关闭socket
		WSACleanup();//再关闭client socket请求
		return -1;
	}
	printf("连接成功\n");
	
	g_severSocket = severSocket;//给全局SOCKET赋值，方便线程使用
	//5.通讯，收发句柄
	//---------创建一个支线程
	//创建一个线程
	int index = 0;
	HANDLE handle1 = CreateThread(nullptr,//指向一个结构LPSECURITY_ATTRIBUTES   ，必须为空
		0,//新线程的初始化堆栈大小，默认0
		(LPTHREAD_START_ROUTINE)receiveMessage,//对应的线程函数名
		(LPVOID)index,//传给线程（回调）函数的参数
		0,//线程的参数
		nullptr//线程的ID,因为设置了句柄，所以不需要
	);
	char buff[1024] = { 0 };
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		printf("请输入:\n");
		gets_s(buff, sizeof(buff));//scanf_s/cin不能区别空格，或者使用cin.getline()
		//scanf_s("%s", buff,sizeof(buff)-1);
		//发送
		if (send(severSocket, buff, sizeof(buff), 0) > 0)
		{
			printf("发送消息成功\n");
		}

		/*The send function sends data on a connected socket.
		int WSAAPI send(
  SOCKET     s,//客户端的socket标识，表示要发送的地址端口
  const char *buf,//缓存字符指针
  int        len,//长度
  int        flags/收发方式，0表示默认收发方式，一次都收完，返回值>0表示收到数据，==0表示没有收到数据或者收到数据为空，出错返回负数
);//参数设置和recv一样
		*/
	}
	//6.关闭socket
	TerminateThread(handle1, 0);//先关线程
	closesocket(severSocket);
	WSACleanup();
	return 0;
	//如果是server项目为主启动项，那么要启动client时点击client--调试--启动新实例
}

void receiveMessage()//不写线程传入的参数也没事，带确认
{
	char buff[1024] = { 0 };
	while (true)
	{
		if (recv(g_severSocket, buff, sizeof(buff), 0) > 0)//接收服务端的信息，为什么是recv severSocket 待解决 而且只能你发一条我发一条，待解决 把所有的clientSocket换成severStocket 就明白了这只是一个变量用来和IP和端口绑定
			printf(">>:%s\n", buff);
	}
}
