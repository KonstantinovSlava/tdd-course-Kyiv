#include "chatapp.h"

ChatApp::ChatApp(std::shared_ptr<IGui> gui, ConnecionWrapper &connection)
    : m_gui(gui),
      m_connection(connection)
{
}

void ChatApp::PrintMe()
{
    m_gui->Write("me:");
}

void ChatApp::SendMsg()
{
    std::string buffer = m_gui->Read();
    m_connection.Send(buffer);
}

void ChatApp::DisplayMsg()
{
    std::string message = m_connection.Receive();
    m_gui->Write(message);
}

void ChatApp::StartChat()
{
    if (m_connection.IsServer())
    {
        DisplayMsg();
        SendMsg();
    }
    else
    {
        SendMsg();
        DisplayMsg();
    }
}
