#include "command.h"
#include <iostream>
// #include <string>

using namespace std;

Command::Command()
{
    
}

Command::Command(string cmd) 
{
    name = cmd;
}

Command::~Command()
{

}

string Command::GetCmd() 
{
    return name;
}
string Command::GetFlags() 
{
    string flagsStr;

    for (vector<string>::iterator flag = flags.begin(); flag != flags.end(); ++flag)
    {
        flagsStr += *flag + ' ';
    }

    return flagsStr;
}

string Command::GetRedirects() 
{
    return redirects;
}

string Command::GetArguments()
{
    cout << "GetArguments()\n";
    string argumentsStr;

    for (vector<string>::iterator m = arguments.begin(); m != arguments.end(); ++m)
    {
        argumentsStr += *m + ' ';
    }

    return argumentsStr;
}

void Command::SetCmd(string cmd) 
{
    name = cmd;
}

void Command::SetFlags(string flag)
{
    flags.push_back(flag);
}

void Command::SetRedirects(string _redirects) 
{
    redirects = _redirects;
}

void Command::SetArguments(string _arguments)
{
    cout << "SetArguments()\n";
    arguments.push_back(_arguments);
    cout << "end SetArguments()\n";
}

string Command::PrintCommand()
{
    string commandStr;
    commandStr = name + ' ' + GetFlags() + GetArguments() + '\n';
    return commandStr;
}