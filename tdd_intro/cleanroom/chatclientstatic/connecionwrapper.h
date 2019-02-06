#pragma once

#include "socketwrapper.h"

class ConnecionWrapper
{
public:
    ConnecionWrapper(ISocketWrapperPtr socketWrapper);

    std::string getNickname();
    void Send(std::string &buffer);
    std::string Receive();
    bool IsServer();

private:
    ISocketWrapperPtr m_socket;
    std::string name;
    bool m_isServer;
};
