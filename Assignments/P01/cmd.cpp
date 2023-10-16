#include "cmd.h"
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

vector<string> Command::GetFlags()
{
    return flags;
}

string Command::PrintFlags() 
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
    string argumentsStr;

    for (vector<string>::iterator m = arguments.begin(); m != arguments.end(); ++m)
    {
        argumentsStr += *m + ' ';
    }

    return argumentsStr;
}

bool Command::GetPrints() {
    return bPrints;
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
    arguments.push_back(_arguments);
}

void Command::SetPrint(bool _bPrints) {
    bPrints = _bPrints;
}

string Command::PrintCommand()
{
    string commandStr;
    commandStr = name + ' ' + PrintFlags() + GetArguments() + '\n';
    return commandStr;
}

string Command::Execute(string input)
{
    // cout << "Base Execute\n";
    // cout << "Input: " << input << '\n';
    // cout << "Flags: " << GetFlags() << '\n';
    return "";
}