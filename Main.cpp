#include<iostream>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

//서버 살아있는 지 확인용
int main()
{
	WSAData WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);
	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY;
	ServerSockAddr.sin_port = htons(11111);

	bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	while (1) //클라이언트에서 계속 받아야 하므로 while문 작성
	{
		char Buffer[1024] = { 0, };
		SOCKADDR_IN ClientSockAddr;
		memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
		int ClientSockAddrLength = sizeof(SOCKADDR_IN);
		int RecvSize = recvfrom(ServerSocket, Buffer, 1024, 0, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
		cout<< Buffer <<endl;
		int SentSize = sendto(ServerSocket, Buffer, RecvSize, 0, (SOCKADDR*)&ClientSockAddr, sizeof(SOCKADDR_IN));
	}

	return 0;
}