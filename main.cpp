#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{

	//Windows Only
	//Winsock 라이브러리 초기화

	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup Failed." << endl;
		exit(-1);
	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Create socket failed." << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerSockADDR;   // 미리 배정

	memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN));
	ServerSockADDR.sin_addr.s_addr = htonl(INADDR_ANY); // long형, 랜카드 아무거나 다
	ServerSockADDR.sin_port = htons(20000);
	ServerSockADDR.sin_family = PF_INET;

	if (bind(ServerSocket, (SOCKADDR*)&ServerSockADDR, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) // os에 뚫은 가상의 소켓과 랜카드 연결
	{
		cout << "bind failed." << endl;
		exit(-1);
	}

	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "listen failed." << endl;
		exit(-1);
	}

	while (true)// 계속 열려있게 하는 법
	{
		SOCKADDR_IN ClientADDR;
		int ClientAddrlen = sizeof(ClientADDR);
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientADDR, &ClientAddrlen); // ip와 port 확인
		if (ClientSocket == SOCKET_ERROR)
		{
			cout << "accept failed." << endl;
			exit(-1);
		}

		char Message[] = "가즈아";
		int SendLength = send(ClientSocket, Message, strlen(Message), 0);

		closesocket(ClientSocket);
	}
	closesocket(ServerSocket);

	//Windows Only
	WSACleanup();
}