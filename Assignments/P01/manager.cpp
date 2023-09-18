#include <iostream>
#include <string>
#include <sstream>
#include "manager.h"
#include "command.h"
#include "ls.h"

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

    Commands.push_back(DetermineCommand(word));

    // For every string, print it
    while (ss >> word)
    {
        // Store strings based on:
        // - cmd
        // - flags going with cmd
        // cout << word << '\n';
        // cout << Commands[1].GetCmd();
        
        // If |, then create new cmd in CmdMap
        if (word == "|")
        {
            CommandIndex++;
            ss >> word;
            Commands.push_back(DetermineCommand(word));
        }

        // If -, then add as a flag to previous cmd
        else if (word[0] == '-') 
        {
            Commands[CommandIndex]->SetFlags(word);
        }

        // If no delimiter, then add to misc
        else
        {
            Commands[CommandIndex]->SetArguments(word);
        }
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

    for (vector<Command*>::iterator command = Commands.begin(); command != Commands.end(); ++command)
    {
        cout << "Command Index: " + to_string(CommandIndex) + '\n' + (*command)->PrintCommand() + '\n';
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
    // Command* command;
    if (cmd == "ls")
    {
        // command = new LS();
        return new LS();
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