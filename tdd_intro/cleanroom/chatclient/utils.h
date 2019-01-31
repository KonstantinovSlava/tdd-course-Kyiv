#pragma once
#include "isocketwrapper.h"

namespace utils
{
    bool TryBind(ISocketWrapper &socket);
    void Handshake(ISocketWrapperPtr &sockPtr, bool isServer);
    bool Connection (ISocketWrapper &socket, ISocketWrapperPtr &sockPtr);
    std::string GetClientHello();
    std::string GetServerHello();
}
