#define NOMINMAX
#include <iostream>
#include <windows.h>
#include "Screens/clsLoginScreen.h"
#include "Global.h"

int main()
{
    SetConsoleOutputCP(65001); // Set console code page to UTF-8 to display Unicode checkmarks
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
    return 0;
}
