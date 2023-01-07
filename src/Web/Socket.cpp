#include "Socket.h"

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#define MAX_ACCEPTABLE_PACKET_SIZE 10485760

namespace Web::Network
{

    SOCKET Socket::GetRawSocket() const
    {
        return *m_pRawSocket;
    }

    std::string Socket::RecvString() const
    {
        int iSize = 0;
        ::recv(*m_pRawSocket, (char*)&iSize, 4, NULL);

        if (iSize <= 0 || iSize > MAX_ACCEPTABLE_PACKET_SIZE)
            exit(-1);

        auto pBuff = std::unique_ptr<char>(new char[iSize+1]);


        pBuff.get()[iSize] = '\0';
        int iRecvdBytes = 0;
        while (iRecvdBytes < iSize)
        {
            const auto tmp = ::recv(*m_pRawSocket, pBuff.get()+iRecvdBytes, iSize-iRecvdBytes, NULL);

            if (!tmp) exit(-1);
            iRecvdBytes += tmp;
        }

        return pBuff.get();
    }

    nlohmann::json Socket::RecvJson() const
    {
        return nlohmann::json::parse(RecvString());
    }

    void Socket::SendString(const std::string &str) const
    {
        int iSize = str.size();

        ::send(*m_pRawSocket, (const char*)&iSize, sizeof(iSize), NULL);
        ::send(*m_pRawSocket, str.c_str(), str.size(), NULL);
    }

    void Socket::SendJson(const nlohmann::json &jsn) const
    {
        SendString(jsn.dump());
    }

    Socket::Socket(int af, int type, int protocol)
    {
        printf("Created Socket\n");
        m_pRawSocket = std::shared_ptr<SOCKET>(new SOCKET, [](SOCKET* pSocket)
        {
#ifdef _WIN32
            closesocket(*pSocket);
#else
            close(*pSocket);
#endif
        });

        *m_pRawSocket = socket(af, type, protocol);
    }

    void Socket::Bind(const std::string &ip, int iPort)
    {
#if defined(_WIN32) // Windows
        SOCKADDR_IN addr;
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.S_un.S_addr);
        addr.sin_port = htons(iPort);
        addr.sin_family = AF_INET;

        bind(*m_pRawSocket, (SOCKADDR *) &addr, sizeof(addr));
#else // Linux
        sockaddr_in addr{};

        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);
        addr.sin_port = htons(iPort);
        addr.sin_family = AF_INET;

        bind(*m_pRawSocket, (sockaddr*)&addr, sizeof(addr));
#endif
    }

    Socket Socket::Listen()
    {
        listen(*m_pRawSocket, SOMAXCONN);

        auto connectionSocket = accept(*m_pRawSocket, NULL, NULL);

        return connectionSocket;
    }

    Socket::Socket(SOCKET socket)
    {
        m_pRawSocket = std::shared_ptr<SOCKET>(new SOCKET, [](SOCKET* pSocket)
        {
#ifdef _WIN32
            closesocket(*pSocket);
#else // Linux
            close(*pSocket);
#endif
            delete pSocket;
        });
        *m_pRawSocket = socket;
    }

    Socket::Socket()
    {
        // AF_INET, SOCK_STREAM, IPPROTO_TCP
        m_pRawSocket = std::shared_ptr<SOCKET>(new SOCKET, [](const SOCKET* pSocket)
        {

#ifdef _WIN32
            closesocket(*pSocket);
#else // Linux
            close(*pSocket);
#endif
            delete pSocket;
        });

        *m_pRawSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    void Socket::Connect(const std::string &ip, int iPort)
    {
        SOCKADDR_IN addr;
        inet_pton(AF_INET,ip.c_str() , &addr.sin_addr.S_un.S_addr);
        addr.sin_port = htons(iPort);
        addr.sin_family = AF_INET;

        // connect(m_sConnection, (sockaddr*)&addr, sizeof(addr));
        connect(*m_pRawSocket, (sockaddr*)&addr, sizeof(addr));
    }

}