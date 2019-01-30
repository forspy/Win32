// server.cpp : �������̨Ӧ�ó������ڵ㡣
//
//ͬһ��������µĶ���Ŀ����������һ���յĽ�������������Ŀ���ٰ�ĳһ��Ŀ����Ϊ������
#include "stdafx.h"
#include<WinSock2.h>//windows sockectͷ�ļ�
#pragma comment(lib,"ws2_32.lib")//socket���ļ�
//Windows����ͨѶ
//socket���
//����ļܹ�
//�߲�����ܹ���
/*
Ӧ�ò㣨���̣���Э�飺HTTP FTP SMTP POP3...QQ���û�����
��ʾ�㣺����ת�������ź�-�����źţ������ݼ���  ��Э��
�Ự�㣺��������  ��Э��
����㣺Э�飺TCP(��绰) UDP������Ϣ��
����㣺Э�� IPV4��32λ��ʾ��ַ ��ָ�ʽ-�ַ��� �ڲ���Ҫת��Ϊint�� IPV6��64λ��ʾ��ַ�� ICMP
������·�㣺�������ݵķ�ʽ ������(�����ַ�����) ���Ĵ��䣨���ݵ�Ԫ ֡���䣩
����㣺���ˡ����¡�����...
*/
//���ѱ�ʾ�㡢�Ự�㲢��Ӧ�ò�
//socket���׽��֣� ��Ҫserver��IP��ַ �˿� Ȼ��client ����server IP��ַ �˿�  ������������
//socket��Ϊ��ʽ�׽���(TCP) ���ݱ��׽��֣�UDP�� ԭʼ�׽��֣�����û����Э��ģ��ȴ�ȥ�Լ�������Э���socket��
//socket������̣�c�ͻ���/s����� ģ�ͣ�
/*
0.ȷ���汾��Ϣ��IPV4?IPV6?�˿ڼ�λ����
1.����socket
2.��IP����������
3.��ʼ��������������
4.����
5.ͨѶ���շ����ݣ�
6.�ر�socket
*/
void sendMessage();
SOCKET g_clientSocket;
int main()
{
	//0.ȷ���汾��Ϣ
	WSADATA wsaDATA;//�ṹ��--�汾��Ϣ
	WSAStartup(MAKEWORD(2,2),&wsaDATA);//Windows �첽socket�������� MAKEWORD(�޶����һ�ֽڣ����汾��һ�ֽ�)//�����
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

	//1.����socket
	SOCKET severSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
	int severBind=bind(severSocket,(sockaddr*)&severAddr,sizeof(severAddr));
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

	//3.��������������
	int severListen=listen(severSocket,10);
	/*
	int WSAAPI listen(
  SOCKET s,//socket��ʶ
  int    backlog//��������--�ȴ����е���󳤶ȣ���һ������ȥ����ͻ��˵�������Ϣ��
);
	*/

	if (severListen == SOCKET_ERROR)
	{
		printf("socket����ʧ��\n");
		closesocket(severSocket);//�ȹر�socket
		WSACleanup();//�ٹر�socket����
		return -1;
	}
	printf("�����ɹ�\n");
	int clientAddr_len = sizeof(severAddr);
	//4.(�ͻ���)����
	SOCKADDR_IN clientAddr = { 0 };
	printf("�ȴ�����...\n");
	SOCKET clientSocket=accept(severSocket,(sockaddr*)&clientAddr,&clientAddr_len);
	g_clientSocket = clientSocket;
	//accept��һ��������������Ӽ���������ȡ���׽������ӣ���ͬһʱ��ֻ�ܱ�֤һ���ͻ������ӣ��������֣��Ĵλ���
	/*
	SOCKET WSAAPI accept(
  SOCKET   s,//socket��ʶ
  sockaddr *addr,//sockaddr *���͵�ָ�룬�ͻ�Э��ĵ�ַ,�Ի�ȡ���Ӻ�ͻ��˵ĵ�ַ
  int      *addrlen//Э����ڴ��С  ����ڶ���������������д�����޷�����ͻ��˵�Э������Ϣ
);
	*/
	if (clientSocket == INVALID_SOCKET)
	{
		printf("socket����ʧ��\n");
		closesocket(severSocket);//�ȹر�socket
		WSACleanup();//�ٹر�socket����
		return -1;
	}
	printf("���ӳɹ�\n");
	printf("�пͻ������ӽ������ͻ��˵�ip:>>%s\n", inet_ntoa(severAddr.sin_addr));

	//5.ͨѶ���շ����
	//--------------
	//��һ���߳�������������
	//����һ���߳�
	int index = 0;
	HANDLE handle1 = CreateThread(nullptr,//ָ��һ���ṹLPSECURITY_ATTRIBUTES   ������Ϊ��
		0,//���̵߳ĳ�ʼ����ջ��С��Ĭ��0
		(LPTHREAD_START_ROUTINE)sendMessage,//��Ӧ���̺߳�����
		(LPVOID)index,//�����̣߳��ص��������Ĳ����������������ṹ
		0,//�̵߳Ĳ���
		nullptr//�̵߳�ID,��Ϊ�����˾�������Բ���Ҫ
	);
	//---------------
	char buff[1024] = { 0 };
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		if (recv(clientSocket, buff, sizeof(buff), 0) > 0)//����ͻ��˶�һ��������ֻ��Ҫ�ٽ��յ�ʱ���߳̽��վ��У���һ���ͻ��˾Ϳ�һ���߳�
			printf(">>:%s\n", buff);
		/*The recv function receives data from a connected socket or a bound connectionless socket.
		int recv(
  SOCKET s,//�ͻ��˵�socket��ʶ
  char   *buf,//�����ַ�ָ��
  int    len,//����
  int    flags//�շ���ʽ��0��ʾĬ���շ���ʽ��һ�ζ�����
);//����ֵ>0��ʾ�յ����ݣ�==0��ʾû���յ����ݻ����յ�����Ϊ�գ������ظ���
		*/
	}

	//6.�ر�socket
	TerminateThread(handle1, 0);//�ȹ��߳�
	closesocket(clientSocket);
	closesocket(severSocket);
	WSACleanup();//�ر�seversocket����

	return 0;
}


void sendMessage()//��֧�̴߳�����
{
	while (true)
	{
		char severbuff[1024] = { 0 };
		printf("������:\n");
		gets_s(severbuff, sizeof(severbuff));
		if (send(g_clientSocket, severbuff, sizeof(severbuff), 0) > 0)//����Ϊʲôsever��Ŀ����send��ʱ����send(clientSocket, severbuff, sizeof(severbuff), 0)����send--clientSocket�أ������
		{
			printf("������Ϣ�ɹ�\n");
		}
	}
}
