// server.cpp : �������̨Ӧ�ó������ڵ㡣
//
//ͬһ��������µĶ���Ŀ����������һ���յĽ�������������Ŀ���ٰ�ĳһ��Ŀ����Ϊ������
#include "stdafx.h"
#include<WinSock2.h>//windows sockectͷ�ļ�
#pragma comment(lib,"ws2_32.lib")//socket���ļ�

/*UDP socket����
0.ȷ���汾��Ϣ��IPV4?IPV6?�˿ڼ�λ����
1.����socket
2.��IP����������
3.ͨѶ���շ����ݣ�
4.�ر�socket
*/

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
	/*
	SOCKET WSAAPI socket(
	int af,//��ַ��淶,������socket�ĵ�ַ���� AF_INET AF_INET6   ,AF_INET��ʾipv4��ַ��32λ�����˿ںţ�16λ��
	int type,//socket�Ĵ������� SOCK_STREAM SOCK_DGRAM SOCK_RAW
	int protocol//ָ��Э�� IPPROTO_ICMP IPPROTO_TCP IPPROTO_UDP
	);
	*/
	//SOCKETʵ������һ��unsigned int �������
	if (severSocket == INVALID_SOCKET)
	{
		printf("socket����ʧ��\n");
		WSACleanup();//�ر�socket����
		return -1;
	}

	//��ʼ��Э��
	SOCKADDR_IN severAddr = { 0 };
	/*
	typedef struct sockaddr_in {
	#if(_WIN32_WINNT < 0x0600)
	short   sin_family;
	#else //(_WIN32_WINNT < 0x0600)
	ADDRESS_FAMILY sin_family;//��ַ��
	#endif //(_WIN32_WINNT < 0x0600)
	USHORT sin_port;//�˿�
	IN_ADDR sin_addr;//��ָ�ʽip��ַ
	CHAR sin_zero[8];
	} SOCKADDR_IN, *PSOCKADDR_IN;
	*/
	severAddr.sin_family = AF_INET;
	//�洢�˿ںţ�ע�⣺�����ϵ���ֵ��ʽ����ˣ��ȴ��λ�ٴ��λ����pc����ֵ��ʽ��С�ˣ��ȴ��λ�ٴ��λ�����������,ͨ��htons��ת��
	severAddr.sin_port = htons(8888);//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
									 //�洢ip��ַ������inet_addr()ת����4�ֽ�
	severAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");//The inet_addr function converts a string containing an IPv4 dotted-decimal address into a proper address for the IN_ADDR structure.

	//2.�����������󶨵�ַ
	int severBind = bind(severSocket, (sockaddr*)&severAddr, sizeof(severAddr));
	/*
	int bind(
	SOCKET         s,//socket��ʶ
	const sockaddr *addr,//sockaddr *���͵�ָ�룬������Э��ĵ�ַ
	int            namelen//Э����ڴ��С
	);
	*/
	if (severBind == SOCKET_ERROR)
	{
		printf("socket��ʧ��\n");
		closesocket(severSocket);//�ȹر�socket
		WSACleanup();//�ٹر�socket����
		return -1;
	}
	printf("�󶨳ɹ�\n");

	printf("�ȴ��ͻ���ͨѶ...\n");
	//3.ͨѶ���շ���� 
	char buff[1024] = { 0 };
	
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		SOCKADDR_IN clientAddr = { 0 };
		int addrSize = sizeof(clientAddr);
		if (recvfrom(severSocket, buff, sizeof(buff), 0,(sockaddr*)&clientAddr,&addrSize) > 0)//�������������nullptr��ʾ������ͻ��˵�ַ
			printf("����ip��%s>>:%s\n",inet_ntoa(clientAddr.sin_addr), buff);
		/*The recvfrom function receives a datagram and stores the source address.
		int recvfrom(
  SOCKET   s,
  char     *buf,
  int      len,
  int      flags,
  sockaddr *from,//����ͻ��˵ĵ�ַ
  int      *fromlen
);
		*/
	}

	//6.�ر�socket
	closesocket(severSocket);
	WSACleanup();//�ر�seversocket����

	return 0;
}