#include <iostream>
// #include <ncurses.h>
#include "manager.h"
#include "parser.h"

int main() 
{
    bool shouldRun = true;
    Manager* manager = new Manager();
    manager->SetupManager();

    while(shouldRun)
    {
        shouldRun = manager->WaitForCommand();
    }
    manager->SaveHistory();
    return 0;
}
