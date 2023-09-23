#pragma once
#include <iostream>
#include <filesystem>
#include <string>

#include "cmdtypes.h"

using namespace std;

string PWD::Execute(string input = "")
{
    string path;

    if (input == "")
    {
        // something  here
    }

    path = filesystem::current_path();
    
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == '"')
        {
            path.erase(i,1);
        }
    }

    cout << path << '\n';
    return path;
}