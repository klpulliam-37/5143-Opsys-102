#include <iostream>
#include <ncurses.h>
#include "manager.h"
#include "parser.h"

int main() 
{
    // Parser* obj = new Parser();
    // obj->Print();
    // std::cout << "Test Output!\n";
    Manager* manager = new Manager();

    while(true)
    {
        manager->WaitForCommand();
    }
    return 0;
}
