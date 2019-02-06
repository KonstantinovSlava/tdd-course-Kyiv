#pragma once
#include "isocketwrapper.h"

namespace utils
{
    bool TryBind(ISocketWrapper &socket);
    void Handshake(ISocketWrapperPtr &sockPtr, bool isServer, std::string &buffer);
    bool Connection (ISocketWrapper &socket, ISocketWrapperPtr &sockPtr, std::string &buffer);
    std::string GetClientHello();
    std::string GetServerHello();
}
