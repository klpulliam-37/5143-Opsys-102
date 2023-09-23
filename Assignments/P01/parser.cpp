#pragma once
#include <iostream>
#include <sstream>
#include "parser.h"
#include "manager.h"
#include "command.h"
#include "cmdtypes.h"

using namespace std;

Parser::Parser()
{
    
}

Parser::~Parser()
{

}

void Parser::SetManager(Manager* manager)
{
    managerRef = manager;
}

void Parser::SplitCommand(string cmds)
{
    // Create stream object and have it parse line into seperate strings
    stringstream ss(cmds);
    string cmdStr;
    Command cmd;

    // Split on redirect which only appears after last command
    // - should only handle redirect after last command

    // split on pipes '|'
    while (!ss.eof())
    {
        getline(ss, cmdStr, '|');
        // Command* command = CreateCommand(cmdStr);
        managerRef->AddCommand(CreateCommand(cmdStr));
    }
}

Command* Parser::CreateCommand(string cmd)
{
    // Create stream object and have it parse line into seperate strings
    stringstream ss(cmd);
    string part;
    Command* cmdPtr;

    // Get command name
    ss >> part;
    Command command = DetermineCommand(part);
    cmdPtr = &command; // Determines command class based on command name

    // split command into command object
    // only directive to look for is 'help'
    // - what is a directive?

    // For every string, print it
    while (ss >> part)
    {        


        // If -, then add as a flag to cmd
        if (part[0] == '-') 
        {
            cmdPtr->SetFlags(part);
        }

        // If no delimiter, then add to misc
        else
        {
            cmdPtr->SetArguments(part);
        }

        // cout << "Command Index: " << CommandIndex << '\n';
    }

    // PrintCommands();

    return cmdPtr;
}

Command Parser::DetermineCommand(string cmd)
{
    if (cmd == "ls")
    {
        return LS(cmd);
    }
    // // mkdir
    // else if (cmd == "mkdir")
    // {

    // }
    // // cd
    // else if (cmd == "cd")
    // {
        
    // }
    // // pwd
    else if (cmd == "pwd")
    {
        return PWD(cmd);
    }
    // // cp
    // else if (cmd == "cp")
    // {
        
    // }
    // // mv
    // else if (cmd == "mv")
    // {
        
    // }
    // // rm
    // else if (cmd == "rm")
    // {
        
    // }
    // // rmdir
    // else if (cmd == "rmdir")
    // {
        
    // }
    // // cat
    // else if (cmd == "cat")
    // {
        
    // }
    // // less
    // else if (cmd == "less")
    // {
        
    // }
    // // tail
    // else if (cmd == "tail")
    // {
        
    // }
    // // grep
    // else if (cmd == "grep")
    // {
        
    // }
    // // wc
    // else (cmd == "wc")
    // {
        
    // }
    return Command(cmd);
}