#include "utils.h"

namespace
{
    const std::string ip = "127.0.0.1";
    const int port = 4444;
}

bool utils::TryBind(ISocketWrapper &socket)
{
    try
    {
        socket.Bind(ip, port);
    }
    catch (std::runtime_error &)
    {
        return false;
    }

    return true;
}

void utils::Handshake(ISocketWrapperPtr &sockPtr, bool isServer)
{
    std::string buffer;
    if (isServer)
    {
        sockPtr->Read(buffer);
        sockPtr->Write(utils::GetServerHello());
    }
    else
    {
        sockPtr->Write(utils::GetClientHello());
        sockPtr->Read(buffer);
    }
}

bool utils::Connection (ISocketWrapper &socket, ISocketWrapperPtr &sockPtr)
{
    bool isServer = TryBind(socket);
    if (isServer)
    {
        socket.Listen();
        sockPtr = socket.Accept();
    }
    else
    {
        sockPtr = socket.Connect(ip, port);
    }

    utils::Handshake(sockPtr, isServer);

    return isServer;
}

std::string utils::GetClientHello()
{
    return "client:!HELLO";
}

std::string utils::GetServerHello()
{
    return "server:!HELLO";
}
