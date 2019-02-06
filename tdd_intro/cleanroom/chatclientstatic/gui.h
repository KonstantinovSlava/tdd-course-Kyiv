#pragma once
#include "igui.h"

class Gui : public IGui
{
public:
    Gui();

    virtual std::string Read();
    // Displays given text in GUI
    virtual void Write(const std::string& text);
};
