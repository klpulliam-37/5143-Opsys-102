#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include "manager.h"
#include "parser.h"
#include "command.h"
#include "cmdtypes.h"

using namespace std;

Manager::Manager()
{
    parser = new Parser();
}

Manager::~Manager()
{

}

void Manager::SetupManager()
{
    parser->SetManager(this);
}

void Manager::WaitForCommand()
{
    string cmds;
    cout << "% ";
    getline(cin, cmds);

    parser->SplitCommand(cmds);
    PrintCommands();
    ExecuteCommands();
    ClearCommands();
}

void Manager::AddCommand(Command& command)
{
    cout << "AddCommand: " << command.Execute("") << '\n';
    Commands.push_back(&command);
}

void Manager::ExecuteCommands()
{
    cout << "ExecuteCommand: \n";
    // Command* command;
    for (int i = 0; i < Commands.size(); i++)
    {
        // command = Commands.at(i);
        Commands.at(i)->Execute("");
    }
}

void Manager::PrintCommands()
{
    Command* command;
    for (int i = 0; i < Commands.size(); i++)
    {
        command = Commands.at(i);
        // cout << typeid(command).name() << '\n';
        cout << command->PrintCommand() + '\n';
    }
}

void Manager::ClearCommands()
{
    Commands.clear();
    // CommandIndex = 0;
}

void Manager::TestDeriv()
{
    vector<Command*> TestCmds;
    PWD pwd("pwd");
    TestCmds.push_back(&pwd);
    // Command* cmd = &pwd;
    TestCmds.at(0)->Execute("");
}