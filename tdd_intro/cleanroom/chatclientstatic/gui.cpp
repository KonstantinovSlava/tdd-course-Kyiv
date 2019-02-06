#include "gui.h"
#include <iostream>

Gui::Gui()
{

}

std::string Gui::Read()
{
    std::string buf;
    std::cin >> buf;
    return buf;
}

void Gui::Write(const std::string& text)
{
    std::cout << text;
}
