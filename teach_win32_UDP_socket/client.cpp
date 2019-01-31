// client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<WinSock2.h>//windows sockect头文件
#pragma comment(lib,"ws2_32.lib")//socket库文件

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

	if (severSocket == INVALID_SOCKET)
	{
		printf("socket创建失败\n");
		WSACleanup();//关闭socket请求
		return -1;
	}

	//初始化协议
	SOCKADDR_IN severAddr = { 0 };

	severAddr.sin_family = AF_INET;
	//存储端口号，注意：网络上的数值方式（大端：先存高位再存低位）和pc的数值方式（小端：先存低位再存高位）是有区别的,通过htons来转换
	severAddr.sin_port = htons(8888);//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
									 //存储ip地址，利用inet_addr()转换成4字节
	severAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");//The inet_addr function converts a string containing an IPv4 dotted-decimal address into a proper address for the IN_ADDR structure.
	
	//2.通讯
	char buff[1024] = { 0 };
	printf("请输入信息\n");
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		gets_s(buff, sizeof(buff));
		//因为TCP里面客户端有connect而UDP没有connect，所以在sendto里面进行整合，相当于把connect和send整合在一起形成sendto
		if (sendto(severSocket, buff, sizeof(buff), 0, (sockaddr*)&severAddr, sizeof(severAddr)) > 0)
			printf("发送成功\n");
		/*
		int sendto(
  SOCKET         s,
  const char     *buf,
  int            len,
  int            flags,
  const sockaddr *to,
  int            tolen
);
		*/
	}

	//3.关闭socket
	closesocket(severSocket);
	WSACleanup();//关闭seversocket请求
    return 0;
}

