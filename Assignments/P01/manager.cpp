#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>
#include "manager.h"
#include "parser.h"
#include "cmd.h"
#include "cmdtypes.h"
#include "helper.h"
#include "requests.h"

using namespace std;

Manager::Manager()
{
    parser = new Parser();
}

Manager::~Manager()
{
    SaveHistory();
    delete parser;
}

void Manager::SetupManager()
{
    UserLogin();
    LoadHistory();

    parser->SetManager(this);
}

void Manager::UserLogin() {
    bool credentialsValid = false;
    while (!credentialsValid)
    {
        string username = "", password = "";

        cout << "Please enter your username: ";
        getline(cin, username);

        cout << "Please enter your password: ";
        getline(cin, password);

        credentialsValid = cpprequests::StartSession(username, password);
    }
}

void Manager::LoadHistory()
{
    // Load file line by line into history vector
    ifstream historyfile(".history");
    string cmd;

    if (historyfile.is_open())
    {
        while(getline(historyfile, cmd))
        {
            Helper::UpdateHistory(cmd);
        }
    }
    else
    {
        cout << "LoadHistory: .history could not be loaded" << endl;
    }
}

void Manager::SaveHistory()
{
    // To append, pass ios::app as well
    ofstream historyfile(".history");

    if (historyfile.is_open())
    {
        historyfile << Helper::GetHistory();
    }
    else
    {
        cout << "SaveHistory: .history could not be loaded" << endl;
    }
}

bool Manager::WaitForCommand()
{
    string path = Helper::GetDir();
    string shellCWD = cpprequests::GetShellPath();
    string cmds;

    cout << shellCWD;
    getline(cin, cmds);

    if (cmds == "exit")
    {
        return false;
    }

    parser->SplitCommand(cmds);
    // ParseCommands(cmds);
    // PrintCommands();
    ExecuteCommands();
    ClearCommands();
    Helper::SetHasRedirectO(false, ""); // Reset redirect
    return true;
}

void Manager::AddCommand(Command* command)
{
    Commands.push_back(command);
}

void Manager::ExecuteCommands()
{
    string input = "";
    for (int i = 0; i < Commands.size(); i++)
    {
        input = Commands.at(i)->Execute(input);
    }

    // cout << input;

    if (Helper::GetHasRedirectO())
    {
        ofstream output(Helper::GetOutfile());
        output << input;
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

// void Manager::SetORedirect(bool _hasRedirectO, string output)
// {
//     // hasRedirectO = _hasRedirectO;
//     outfile = output;
//     Helper::SetHasRedirectO(_hasRedirectO);
// }

// void Manager::SetInput(string _input)
// {
//     input = _input;
// }

// string Manager::GetInput()
// {
//     return input;
// }

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