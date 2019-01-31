#pragma once

#include "socketwrapper.h"

class ConnecionWrapper
{
public:
    ConnecionWrapper(ISocketWrapperPtr socketWrapper);

    std::string getNickname();

private:
    ISocketWrapperPtr m_socket;
    std::string name;
};
