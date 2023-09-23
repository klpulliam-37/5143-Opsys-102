#include <iostream>
#include <ncurses.h>
#include "manager.h"
#include "parser.h"

// class Base
// {
// public:
//     virtual void print()
//     {
//         std::cout << "Base\n";
//     }
// };

// class Derived : public Base
// {
// public:
//     void print() override
//     {
//         std::cout << "Derived\n";
//     }
// };

int main() 
{
    // Derived d;
    // Base* b = &d;
    // b->print();

    Manager* manager = new Manager();
    manager->SetupManager();

    // manager->TestDeriv();

    while(true)
    {
        manager->WaitForCommand();
    }
    return 0;
}
