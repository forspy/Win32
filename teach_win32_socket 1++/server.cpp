// server.cpp : 定义控制台应用程序的入口点。
//
//同一解决方案下的多项目管理，先生成一个空的解决方案再添加项目，再把某一项目设置为启动项
#include "stdafx.h"
#include<WinSock2.h>//windows sockect头文件
#pragma comment(lib,"ws2_32.lib")//socket库文件
//Windows网络通讯
//socket编程
//网络的架构
//七层网络架构：
/*
应用层（进程）：协议：HTTP FTP SMTP POP3...QQ等用户进程
表示层：数据转换（音信号-数字信号）、数据加密  无协议
会话层：建立链接  无协议
传输层：协议：TCP(打电话) UDP（发信息）
网络层：协议 IPV4（32位表示地址 点分格式-字符串 内部需要转换为int） IPV6（64位表示地址） ICMP
数据链路层：传输数据的方式 流传输(单个字符传输) 报文传输（数据单元 帧传输）
物理层：光纤、电缆、网卡...
*/
//五层把表示层、会话层并入应用层
//socket（套接字） 需要server的IP地址 端口 然后client 访问server IP地址 端口  这样建立链接
//socket分为流式套接字(TCP) 数据报套接字（UDP） 原始套接字（就是没有设协议的，等待去自己设置新协议的socket）
//socket编程流程（c客户端/s服务端 模型）
/*
0.确定版本信息（IPV4?IPV6?端口几位？）
1.创建socket
2.绑定IP（服务器）
3.开始监听（服务器）
4.连接
5.通讯（收发数据）
6.关闭socket
*/
void sendMessage();
SOCKET g_clientSocket;
int main()
{
	//0.确定版本信息
	WSADATA wsaDATA;//结构体--版本信息
	WSAStartup(MAKEWORD(2,2),&wsaDATA);//Windows 异步socket启动命令 MAKEWORD(修订版低一字节，主版本高一字节)//待解决
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
	SOCKADDR_IN severAddr = { 0 };
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
	severAddr.sin_family = AF_INET;
	//存储端口号，注意：网络上的数值方式（大端：先存高位再存低位）和pc的数值方式（小端：先存低位再存高位）是有区别的,通过htons来转换
	severAddr.sin_port = htons(8888);//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
	//存储ip地址，利用inet_addr()转换成4字节
	severAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");//The inet_addr function converts a string containing an IPv4 dotted-decimal address into a proper address for the IN_ADDR structure.
    
	//2.（服务器）绑定地址
	int severBind=bind(severSocket,(sockaddr*)&severAddr,sizeof(severAddr));
	/*
	int bind(
  SOCKET         s,//socket标识
  const sockaddr *addr,//sockaddr *类型的指针，服务器协议的地址
  int            namelen//协议的内存大小
);
	*/
	if (severBind == SOCKET_ERROR)
	{
		printf("socket绑定失败\n");
		closesocket(severSocket);//先关闭socket
		WSACleanup();//再关闭socket请求
		return -1;
	}
	printf("绑定成功\n");

	//3.（服务器）监听
	int severListen=listen(severSocket,10);
	/*
	int WSAAPI listen(
  SOCKET s,//socket标识
  int    backlog//监听个数--等待队列的最大长度（用一个队列去保存客户端的连接信息）
);
	*/

	if (severListen == SOCKET_ERROR)
	{
		printf("socket监听失败\n");
		closesocket(severSocket);//先关闭socket
		WSACleanup();//再关闭socket请求
		return -1;
	}
	printf("监听成功\n");
	int clientAddr_len = sizeof(severAddr);
	//4.(客户端)连接
	SOCKADDR_IN clientAddr = { 0 };
	printf("等待连接...\n");
	SOCKET clientSocket=accept(severSocket,(sockaddr*)&clientAddr,&clientAddr_len);
	g_clientSocket = clientSocket;
	//accept是一个阻塞函数，会从监听队列中取队首进行连接，再同一时刻只能保证一个客户端连接，三次握手，四次挥手
	/*
	SOCKET WSAAPI accept(
  SOCKET   s,//socket标识
  sockaddr *addr,//sockaddr *类型的指针，客户协议的地址,以获取连接后客户端的地址
  int      *addrlen//协议的内存大小  如果第二个第三个参数不写，旧无法保存客户端的协议族信息
);
	*/
	if (clientSocket == INVALID_SOCKET)
	{
		printf("socket连接失败\n");
		closesocket(severSocket);//先关闭socket
		WSACleanup();//再关闭socket请求
		return -1;
	}
	printf("连接成功\n");
	printf("有客户端连接进来，客户端的ip:>>%s\n", inet_ntoa(severAddr.sin_addr));

	//5.通讯，收发句柄
	//--------------
	//做一个线程用来发送数据
	//创建一个线程
	int index = 0;
	HANDLE handle1 = CreateThread(nullptr,//指向一个结构LPSECURITY_ATTRIBUTES   ，必须为空
		0,//新线程的初始化堆栈大小，默认0
		(LPTHREAD_START_ROUTINE)sendMessage,//对应的线程函数名
		(LPVOID)index,//传给线程（回调）函数的参数，多个参数传入结构
		0,//线程的参数
		nullptr//线程的ID,因为设置了句柄，所以不需要
	);
	//---------------
	char buff[1024] = { 0 };
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		if (recv(clientSocket, buff, sizeof(buff), 0) > 0)//多个客户端对一个服务器只需要再接收的时候开线程接收就行，来一个客户端就开一个线程
			printf(">>:%s\n", buff);
		/*The recv function receives data from a connected socket or a bound connectionless socket.
		int recv(
  SOCKET s,//客户端的socket标识
  char   *buf,//缓存字符指针
  int    len,//长度
  int    flags//收发方式，0表示默认收发方式，一次都收完
);//返回值>0表示收到数据，==0表示没有收到数据或者收到数据为空，出错返回负数
		*/
	}

	//6.关闭socket
	TerminateThread(handle1, 0);//先关线程
	closesocket(clientSocket);
	closesocket(severSocket);
	WSACleanup();//关闭seversocket请求

	return 0;
}


void sendMessage()//分支线程处理函数
{
	while (true)
	{
		char severbuff[1024] = { 0 };
		printf("请输入:\n");
		gets_s(severbuff, sizeof(severbuff));
		if (send(g_clientSocket, severbuff, sizeof(severbuff), 0) > 0)//而且为什么sever项目里面send的时候是send(clientSocket, severbuff, sizeof(severbuff), 0)，是send--clientSocket呢？待解决
		{
			printf("发送消息成功\n");
		}
	}
}
