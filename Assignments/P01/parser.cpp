#pragma once
#include <iostream>
#include <sstream>
#include "parser.h"
#include "manager.h"
#include "cmd.h"
#include "cmdtypes.h"
#include "helper.h"

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
    string output;

    if (cmds.find('!') == string::npos)
    {
        Helper::UpdateHistory(cmds);
    }

    // Split on redirect which only appears after last command
    // - should only handle redirect after last command
    if (cmds.find('>') != string::npos)
    {
        getline(ss, cmdStr, '>');
        getline(ss, output);

        output.erase(0, 1);

        // cout << "ParseRedir: " << Helper::GetHasRedirectO() << '\n';
        Helper::SetHasRedirectO(true, output);
        // cout << "ParseRedir: " << Helper::GetHasRedirectO() << '\n';

        stringstream ssr(cmdStr);
        // split on pipes '|'
        while (!ssr.eof())
        {
            // cout << "Command String: |" << cmdStr << "|\n";
            getline(ssr, cmdStr, '|');
            CreateCommand(cmdStr);
        }
    }else{
        // split on pipes '|'
        while (!ss.eof())
        {
            // cout << "Command String: |" << cmdStr << "|\n";
            getline(ss, cmdStr, '|');
            CreateCommand(cmdStr);
        }
    }
}

void Parser::CreateCommand(string cmdStr)
{
    // Create stream object and have it parse line into seperate strings
    stringstream ss(cmdStr);
    string cmd;

    // Get command name
    ss >> cmd;
    
    Command* command;
    if (cmd == "ls")
    {
        command = new LS(cmd);
    }
    // mkdir
    else if (cmd == "mkdir")
    {
        command = new MkDir(cmd);
    }
    // cd
    else if (cmd == "cd")
    {
        command = new CD(cmd);
    }
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
    // cat
    else if (cmd == "cat")
    {
        command = new CAT(cmd);
    }
    else if (cmd == "head")
    {
        command = new Head(cmd);
    }
    // // less
    // else if (cmd == "less")
    // {
        
    // }
    // // tail
    // else if (cmd == "tail")
    // {
        
    // }
    // grep
    else if (cmd == "grep")
    {
        command = new Grep(cmd);
    }
    // // wc
    // else if (cmd == "wc")
    // {
        
    // }
    else if (cmd == "history")
    {
        command = new History(cmd);
    }
    else if (cmd[0] == '!')
    {
        command = new HistoryIndex(cmd, managerRef);
    }
    else
    {
        command = new Error(cmd);
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