#include <iostream>
#include <string>
#include <sstream>
#include "manager.h"
#include "command.h"
#include "cmdtypes.h"

using namespace std;

Manager::Manager()
{

}

Manager::~Manager()
{

}

void Manager::SplitCommand(string cmds)
{
    // Create stream object and have it parse line into seperate strings
    stringstream ss(cmds);
    string cmd;

    // Split on redirect which only appears after last command
    // - should only handle redirect after last command

    // split on pipes '|'
    while (!ss.eof())
    {
        getline(ss, cmd, '|');
        Commands.push_back(CreateCommand(cmd));
    }

    PrintCommands();
}

Command Manager::CreateCommand(string cmd)
{
    // Create stream object and have it parse line into seperate strings
    stringstream ss(cmd);
    string part;
    Command* cmdObj;

    // Get command name
    ss >> part;
    cmdObj = DetermineCommand(part); // Determines command class based on command name

    // split command into command object
    // only directive to look for is 'help'
    // - what is a directive?

    // For every string, print it
    while (ss >> part)
    {        


        // If -, then add as a flag to cmd
        if (part[0] == '-') 
        {
            cmdObj->SetFlags(part);
        }

        // If no delimiter, then add to misc
        else
        {
            cmdObj->SetArguments(part);
        }

        // cout << "Command Index: " << CommandIndex << '\n';
    }

    // PrintCommands();

    return *cmdObj;
}

void Manager::WaitForCommand()
{
    string cmds;
    cout << "% ";
    getline(cin, cmds);
    // cout << cmd << '\n';

    ClearCommands();
    SplitCommand(cmds);
}

void Manager::PrintCommands()
{
    // CommandIndex = 0;

    for (vector<Command>::iterator command = Commands.begin(); command != Commands.end(); ++command)
    {
        // cout << "Printing Commands" << '\n';
        cout << command->PrintCommand() + '\n';
        // CommandIndex++;
    }
}

void Manager::ClearCommands()
{
    Commands.clear();
    CommandIndex = 0;
}

Command* Manager::DetermineCommand(string cmd)
{
    Command* command;
    if (cmd == "ls")
    {
        command = new LS(cmd);
        return command;
    }
    // // mkdir
    // else if (cmd == "mkdir")
    // {

    // }
    // // cd
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // pwd
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // cp
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // mv
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // rm
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // rmdir
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // cat
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // less
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // tail
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // grep
    // else if (cmd == "mkdir")
    // {
        
    // }
    // // wc
    // else (cmd == "mkdir")
    // {
        
    // }
    return new Command(cmd);
}