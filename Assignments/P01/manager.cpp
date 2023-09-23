#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include "manager.h"
#include "parser.h"
#include "command.h"
#include "cmdtypes.h"
#include "helper.h"

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
    string path = Helper::GetDir();
    string termPath = Helper::FormatDir(path);
    string cmds;

    cout << termPath;
    getline(cin, cmds);

    parser->SplitCommand(cmds);
    // ParseCommands(cmds);
    // PrintCommands();
    ExecuteCommands();
    ClearCommands();
}

void Manager::AddCommand(Command* command)
{
    Commands.push_back(command);
}

void Manager::ExecuteCommands()
{
    for (int i = 0; i < Commands.size(); i++)
    {
        Commands.at(i)->Execute("");
    }
}

void Manager::PrintCommands()
{
    Command* command;
    for (int i = 0; i < Commands.size(); i++)
    {
        command = Commands.at(i);
        cout << command->PrintCommand() + '\n';
    }
}

void Manager::ClearCommands()
{
    Commands.clear();
}

// void Manager::ParseCommands(string cmds)
// {
//     // Create stream object and have it parse line into seperate strings
//     stringstream ss(cmds);
//     string cmdStr;
//     Command* command;    

//     // Split on redirect which only appears after last command
//     // - should only handle redirect after last command

//     // split on pipes '|'
//     while (!ss.eof())
//     {
//         getline(ss, cmdStr, '|');
        
//     }

//     // Create stream object and have it parse line into seperate strings
//     stringstream ss2(cmdStr);
//     string cmd;

//     // Get command name
//     ss2 >> cmd;
    
//     if (cmd == "ls")
//     {
//         command = new LS(cmd);
//     }
//     // // mkdir
//     // else if (cmd == "mkdir")
//     // {

//     // }
//     // // cd
//     // else if (cmd == "cd")
//     // {
        
//     // }
//     // // pwd
//     else if (cmd == "pwd")
//     {
//         cout << "CommandType: PWD\n";
//         command = new PWD(cmd);
//     }
//     // // cp
//     // else if (cmd == "cp")
//     // {
        
//     // }
//     // // mv
//     // else if (cmd == "mv")
//     // {
        
//     // }
//     // // rm
//     // else if (cmd == "rm")
//     // {
        
//     // }
//     // // rmdir
//     // else if (cmd == "rmdir")
//     // {
        
//     // }
//     // // cat
//     // else if (cmd == "cat")
//     // {
        
//     // }
//     // // less
//     // else if (cmd == "less")
//     // {
        
//     // }
//     // // tail
//     // else if (cmd == "tail")
//     // {
        
//     // }
//     // // grep
//     // else if (cmd == "grep")
//     // {
        
//     // }
//     // // wc
//     // else if (cmd == "wc")
//     // {
        
//     // }
//     else
//     {
//         command = new Command("");
//     }

//     // split command into command object
//     // only directive to look for is 'help'
//     // - what is a directive?

//     // For every string, print it
//     while (ss2 >> cmd)
//     {        


//         // If -, then add as a flag to cmd
//         if (cmd[0] == '-') 
//         {
//             command->SetFlags(cmd);
//         }

//         // If no delimiter, then add to misc
//         else
//         {
//             command->SetArguments(cmd);
//         }

//         // cout << "Command Index: " << CommandIndex << '\n';
//     }

//     // cout << "AddCommand: " << command.Execute("") << '\n';
//     Commands.push_back(command);
// }

// void Manager::TestDeriv()
// {
//     vector<Command*> TestCmds;
//     PWD pwd("pwd");
//     TestCmds.push_back(&pwd);
//     // Command* cmd = &pwd;
//     TestCmds.at(0)->Execute("");
// }