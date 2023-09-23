#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "cmdtypes.h"
#include "helper.h"

using namespace std;

string PWD::Execute(string input = "")
{
    string pwd = Helper::GetDir();
    cout << pwd << '\n';
    return pwd;
}

string History::Execute(string input = "")
{
    string history = Helper::GetHistory();
    cout << history;
    return history;
}