// client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<WinSock2.h>//windows sockectͷ�ļ�
#pragma comment(lib,"ws2_32.lib")//socket���ļ�
void receiveMessage();
SOCKET g_severSocket;
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
	SOCKADDR_IN clientAddr = { 0 };
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
	clientAddr.sin_family = AF_INET;
	//�洢�˿ںţ�ע�⣺�����ϵ���ֵ��ʽ����ˣ��ȴ��λ�ٴ��λ����pc����ֵ��ʽ��С�ˣ��ȴ��λ�ٴ��λ�����������,ͨ��htons��ת��
	clientAddr.sin_port = htons(8888);//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
									 //�洢ip��ַ������inet_addr()ת����4�ֽ�
	clientAddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.4");//����˵�IP��ַ 



	//4.(�ͻ���)����
	int clientConnect = connect(severSocket, (sockaddr*)&clientAddr, sizeof(clientAddr));//�����ڷ����������ӣ�severSocket���ӵ�ʱ���õ��Ƿ���˵�ip���˿�
	/*The connect function establishes a connection to a specified socket.
	int WSAAPI connect(
  SOCKET         s,
  const sockaddr *name,
  int            namelen
);
	*/
	if (clientConnect == SOCKET_ERROR)
	{
		printf("socket����ʧ��\n");
		closesocket(severSocket);//�ȹر�socket
		WSACleanup();//�ٹر�client socket����
		return -1;
	}
	printf("���ӳɹ�\n");
	
	g_severSocket = severSocket;//��ȫ��SOCKET��ֵ�������߳�ʹ��
	//5.ͨѶ���շ����
	//---------����һ��֧�߳�
	//����һ���߳�
	int index = 0;
	HANDLE handle1 = CreateThread(nullptr,//ָ��һ���ṹLPSECURITY_ATTRIBUTES   ������Ϊ��
		0,//���̵߳ĳ�ʼ����ջ��С��Ĭ��0
		(LPTHREAD_START_ROUTINE)receiveMessage,//��Ӧ���̺߳�����
		(LPVOID)index,//�����̣߳��ص��������Ĳ���
		0,//�̵߳Ĳ���
		nullptr//�̵߳�ID,��Ϊ�����˾�������Բ���Ҫ
	);
	char buff[1024] = { 0 };
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		printf("������:\n");
		gets_s(buff, sizeof(buff));//scanf_s/cin��������ո񣬻���ʹ��cin.getline()
		//scanf_s("%s", buff,sizeof(buff)-1);
		//����
		if (send(severSocket, buff, sizeof(buff), 0) > 0)
		{
			printf("������Ϣ�ɹ�\n");
		}

		/*The send function sends data on a connected socket.
		int WSAAPI send(
  SOCKET     s,//�ͻ��˵�socket��ʶ����ʾҪ���͵ĵ�ַ�˿�
  const char *buf,//�����ַ�ָ��
  int        len,//����
  int        flags/�շ���ʽ��0��ʾĬ���շ���ʽ��һ�ζ����꣬����ֵ>0��ʾ�յ����ݣ�==0��ʾû���յ����ݻ����յ�����Ϊ�գ������ظ���
);//�������ú�recvһ��
		*/
	}
	//6.�ر�socket
	TerminateThread(handle1, 0);//�ȹ��߳�
	closesocket(severSocket);
	WSACleanup();
	return 0;
	//�����server��ĿΪ���������ôҪ����clientʱ���client--����--������ʵ��
}

void receiveMessage()//��д�̴߳���Ĳ���Ҳû�£���ȷ��
{
	char buff[1024] = { 0 };
	while (true)
	{
		if (recv(g_severSocket, buff, sizeof(buff), 0) > 0)//���շ���˵���Ϣ��Ϊʲô��recv severSocket ����� ����ֻ���㷢һ���ҷ�һ��������� �����е�clientSocket����severStocket ����������ֻ��һ������������IP�Ͷ˿ڰ�
			printf(">>:%s\n", buff);
	}
}
