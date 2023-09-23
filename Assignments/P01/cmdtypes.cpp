#include <iostream>
#include <filesystem>

#include "cmdtypes.h"

using namespace std;

string PWD::Execute(string input = "")
{
    if (input == "")
    {
        // something  here
    }
    cout << "starpath " << filesystem::current_path() << " endpath\n";
    return filesystem::current_path();
}