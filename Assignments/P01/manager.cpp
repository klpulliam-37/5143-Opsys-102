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
    // PrintCommands();
    ExecuteCommands();
    ClearCommands();
}

void Manager::AddCommand(Command* command)
{
    Commands.push_back(*command);
}

void Manager::ExecuteCommands()
{
    Command* command;
    for (int i = 0; i < Commands.size(); i++)
    {
        command = &Commands[i];
        command->Execute("");
    }
}

void Manager::PrintCommands()
{
    for (vector<Command>::iterator command = Commands.begin(); command != Commands.end(); ++command)
    {
        cout << typeid(command).name() << '\n';
        // cout << command->PrintCommand() + '\n';
    }
}

void Manager::ClearCommands()
{
    Commands.clear();
    // CommandIndex = 0;
}

void Manager::TestDeriv()
{
    PWD pwd("pwd");
    Command* cmd = &pwd;
    cmd->Execute("");
}