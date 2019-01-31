// server.cpp : 定义控制台应用程序的入口点。
//
//同一解决方案下的多项目管理，先生成一个空的解决方案再添加项目，再把某一项目设置为启动项
#include "stdafx.h"
#include<WinSock2.h>//windows sockect头文件
#pragma comment(lib,"ws2_32.lib")//socket库文件

/*UDP socket创建
0.确定版本信息（IPV4?IPV6?端口几位？）
1.创建socket
2.绑定IP（服务器）
3.通讯（收发数据）
4.关闭socket
*/

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

	//1.创建socket --UDP
	SOCKET severSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//severSocket表示绑定的是服务端的IP
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
	int severBind = bind(severSocket, (sockaddr*)&severAddr, sizeof(severAddr));
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

	printf("等待客户端通讯...\n");
	//3.通讯，收发句柄 
	char buff[1024] = { 0 };
	
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		SOCKADDR_IN clientAddr = { 0 };
		int addrSize = sizeof(clientAddr);
		if (recvfrom(severSocket, buff, sizeof(buff), 0,(sockaddr*)&clientAddr,&addrSize) > 0)//最后两个参数给nullptr表示不储存客户端地址
			printf("来自ip：%s>>:%s\n",inet_ntoa(clientAddr.sin_addr), buff);
		/*The recvfrom function receives a datagram and stores the source address.
		int recvfrom(
  SOCKET   s,
  char     *buf,
  int      len,
  int      flags,
  sockaddr *from,//储存客户端的地址
  int      *fromlen
);
		*/
	}

	//6.关闭socket
	closesocket(severSocket);
	WSACleanup();//关闭seversocket请求

	return 0;
}