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

    // Split on redirect which only appears after last command
    // - should only handle redirect after last command

    // split on pipes '|'
    while (!ss.eof())
    {
        getline(ss, cmdStr, '|');
        CreateCommand(cmdStr);
    }
}

void Parser::CreateCommand(string cmd)
{
    // Create stream object and have it parse line into seperate strings
    stringstream ss(cmd);
    string part;

    // Get command name
    ss >> part;
    
    Command* command;
    if (part == "ls")
    {
        command = new LS(cmd);
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
        command = new PWD(cmd);
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
    // else if (cmd == "wc")
    // {
        
    // }
    else
    {
        command = new Command("");
    }

    // split command into command object
    // only directive to look for is 'help'
    // - what is a directive?

    // For every string, print it
    while (ss >> cmd)
    {        
        // If -, then add as a flag to cmd
        if (cmd[0] == '-') 
        {
            command->SetFlags(cmd);
        }

        // If no delimiter, then add to misc
        else
        {
            command->SetArguments(cmd);
        }
    }

    managerRef->AddCommand(command);
}