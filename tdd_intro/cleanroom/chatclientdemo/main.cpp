#include <iostream>
#include "connecionwrapper.h"
#include "ChatApp.h"
#include "gui.h"

int main(int argc, char *argv[])
{
    try
    {
        std::shared_ptr<Gui> gui = std::make_shared<Gui>();
        std::shared_ptr<SocketWrapper> socketMock = std::make_shared<SocketWrapper>();

        std::cout << "Waiting connection:" << std::endl;

        ConnecionWrapper wrapper(socketMock);
        ChatApp app(gui, wrapper);
        //app.PrintMe();
        app.StartChat();

        std::cout << std::endl << "end" << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << std::endl << ex.what() << std::endl;
    }
    return 0;
}
