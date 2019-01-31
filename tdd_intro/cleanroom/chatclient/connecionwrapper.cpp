#include "connecionwrapper.h"
#include "utils.h"

ConnecionWrapper::ConnecionWrapper(ISocketWrapperPtr socketWrapper)
    : m_socket(nullptr)
{
    std::string buffer;
    utils::Connection(*socketWrapper.get(), m_socket, buffer);
    this->name = buffer.substr(0, buffer.find(':'));
}

std::string ConnecionWrapper::getNickname()
{
    return name;
}
