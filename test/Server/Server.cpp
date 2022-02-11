#include "Server.h"


CServer::CServer()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}
CServer::~CServer()
{
    WSACleanup();
}
int CServer::GetFreePort()
{
	addrinfo* result = NULL;
	addrinfo	hints;


    // Resolve the server address and port
    for (int port = 7000; port < 8000; port++)
    {
        ZeroMemory(&hints, sizeof(hints));

        hints.ai_family   = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        auto iResult = getaddrinfo("127.0.0.1", std::to_string(port).c_str(), &hints, &result);


        auto ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        if (ConnectSocket == INVALID_SOCKET)
        {
            throw std::runtime_error("socket failed with error");
        }


        // Connect to server.
        iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);

        if (iResult == SOCKET_ERROR)
        {

            closesocket(ConnectSocket);
            return port;
        }
        shutdown(ConnectSocket, SD_SEND);
        closesocket(ConnectSocket);
    }
    return 0;
}
void CServer::Work()
{
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;

    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));

    int iSendResult;
    int recvbuflen = 512;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo("127.0.0.1", std::to_string(GetFreePort()).c_str(), &hints, &result);
    if (iResult != 0) 
    {
        exit(-1);
    }
    while (true)
    {

        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET)
        {
            exit(-1);
        }

        // Setup the TCP listening socket
        iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) 
        {
            exit(-1);
        }

        iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            exit(-1);
        }

        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) 
        {
            exit(-1);
        }

        // No longer need server socket
        closesocket(ListenSocket);

        ZeroMemory(m_ServerBuff, recvbuflen);

        iResult = recv(ClientSocket, m_ServerBuff, recvbuflen, 0);

        //strcpy_s(GlobalVars::buff, m_ServerBuff);

        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) 
        {
            closesocket(ClientSocket);
        }

        // cleanup
        closesocket(ClientSocket);
    }
}