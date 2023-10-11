#include <iostream>
#include "manager.h"
#include "parser.h"
#include "requests.h"

// #include <ncurses.h>

void ShellDriver();
void RequestsDriver();

int main() 
{
    RequestsDriver();
    // ShellDriver();
    return 0;
}

void ShellDriver() {
    bool shouldRun = true;
    Manager* manager = new Manager();
    manager->SetupManager();

    while(shouldRun)
    {
        shouldRun = manager->WaitForCommand();
    }
    manager->SaveHistory();
}

void RequestsDriver() {
    CR::TestGet();
}
