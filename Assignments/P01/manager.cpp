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

void Manager::ParseCommand(string cmdLine)
{
    // Create stream object and have it parse line into seperate strings
    stringstream ss(cmdLine);
    string word;

    // Store first string as a cmd
    ss >> word;
    // Command->SetCmd(word);

    // DetermineCommand(word);

    Commands.push_back(Command(word));

    // Split on redirect which only appears after last command
    // - should only handle redirect after last command
    

    // split on pipes '|'
    // split command into command object
    // only directive to look for is 'help'
    // - what is a directive?

    // For every string, print it
    while (ss >> word)
    {        
        // If |, then create new cmd in CmdMap
        if (word == "|")
        {
            CommandIndex++;
            ss >> word;
            Commands.push_back(Command(word));
        }

        // If -, then add as a flag to previous cmd
        else if (word[0] == '-') 
        {
            Commands[CommandIndex].SetFlags(word);
        }

        // If no delimiter, then add to misc
        else
        {
            Commands[CommandIndex].SetArguments(word);
        }

        cout << "Command Index: " << CommandIndex << '\n';
    }

    PrintCommands();
}

void Manager::WaitForCommand()
{
    string cmd;
    cout << "% ";
    getline(cin, cmd);
    // cout << cmd << '\n';

    ClearCommands();
    ParseCommand(cmd);
}

void Manager::PrintCommands()
{
    CommandIndex = 0;

    for (vector<Command>::iterator command = Commands.begin(); command != Commands.end(); ++command)
    {
        // cout << "Printing Commands" << '\n';
        cout << "Command Index: " + to_string(CommandIndex) + '\n' + command->PrintCommand() + '\n';
        CommandIndex++;
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
    return nullptr;
}