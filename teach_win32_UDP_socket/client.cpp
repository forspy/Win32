// client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<WinSock2.h>//windows sockectͷ�ļ�
#pragma comment(lib,"ws2_32.lib")//socket���ļ�

int main()
{
	//0.ȷ���汾��Ϣ
	WSADATA wsaDATA;//�ṹ��--�汾��Ϣ
	WSAStartup(MAKEWORD(2, 2), &wsaDATA);//Windows �첽socket�������� MAKEWORD(�޶����һ�ֽڣ����汾��һ�ֽ�)//�����
										 /*
										 int WSAStartup(
										 WORD      wVersionRequired,//�汾�� �߽��ֽ�Ϊ�޶��棬�ͽ��ֽ�Ϊ���汾 ����2.2
										 LPWSADATA lpWSAData//�ַ�ָ�룬ָ��汾����Ϣ
										 );�ɹ�����0
										 DWORD(unsigned long);
										 WORD(unsigned short);
										 */
										 //printf("%d\n", LOBYTE(wsaDATA.wVersion));
										 //printf("%d\n", HIBYTE(wsaDATA.wVersion));
	if (LOBYTE(wsaDATA.wVersion) != 2 || HIBYTE(wsaDATA.wVersion) != 2)
	{
		printf("����汾ʧ��\n");
		return -1;
	}

	//1.����socket --UDP
	SOCKET severSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//severSocket��ʾ�󶨵��Ƿ���˵�IP

	if (severSocket == INVALID_SOCKET)
	{
		printf("socket����ʧ��\n");
		WSACleanup();//�ر�socket����
		return -1;
	}

	//��ʼ��Э��
	SOCKADDR_IN severAddr = { 0 };

	severAddr.sin_family = AF_INET;
	//�洢�˿ںţ�ע�⣺�����ϵ���ֵ��ʽ����ˣ��ȴ��λ�ٴ��λ����pc����ֵ��ʽ��С�ˣ��ȴ��λ�ٴ��λ�����������,ͨ��htons��ת��
	severAddr.sin_port = htons(8888);//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
									 //�洢ip��ַ������inet_addr()ת����4�ֽ�
	severAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");//The inet_addr function converts a string containing an IPv4 dotted-decimal address into a proper address for the IN_ADDR structure.
	
	//2.ͨѶ
	char buff[1024] = { 0 };
	printf("��������Ϣ\n");
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		gets_s(buff, sizeof(buff));
		//��ΪTCP����ͻ�����connect��UDPû��connect��������sendto����������ϣ��൱�ڰ�connect��send������һ���γ�sendto
		if (sendto(severSocket, buff, sizeof(buff), 0, (sockaddr*)&severAddr, sizeof(severAddr)) > 0)
			printf("���ͳɹ�\n");
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

	//3.�ر�socket
	closesocket(severSocket);
	WSACleanup();//�ر�seversocket����
    return 0;
}

