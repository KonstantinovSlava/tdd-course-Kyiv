#pragma once
#include <memory>
#include "igui.h"
#include "connecionwrapper.h"

class ChatApp
{
public:
    ChatApp(std::shared_ptr<IGui> gui, ConnecionWrapper &connection);

    void PrintMe();
    void SendMsg();
    void DisplayMsg();
    void StartChat();

private:
    std::shared_ptr<IGui> m_gui;
    ConnecionWrapper &m_connection;
};

