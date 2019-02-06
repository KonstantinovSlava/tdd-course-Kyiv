#include "connecionwrapper.h"
#include "utils.h"

ConnecionWrapper::ConnecionWrapper(ISocketWrapperPtr socketWrapper)
    : m_socket(nullptr)
{
    std::string buffer;
    m_isServer = utils::Connection(*socketWrapper.get(), m_socket, buffer);
    this->name = buffer.substr(0, buffer.find(':'));
}

std::string ConnecionWrapper::getNickname()
{
    return name;
}

void ConnecionWrapper::Send(std::string &buffer)
{
    m_socket->Write(buffer);
}

std::string ConnecionWrapper::Receive()
{
    std::string buffer;
    m_socket->Read(buffer);

    return buffer;
}

bool ConnecionWrapper::IsServer()
{
    return  m_isServer;
}
