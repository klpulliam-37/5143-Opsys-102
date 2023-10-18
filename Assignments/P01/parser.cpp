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

        if (cmds.find(">>") != string::npos) {
            Helper::SetIsAppendMode(true);
        }

        output = Helper::RemoveWhitespace(output);

        Helper::SetHasRedirectO(true, output);

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
    else if (cmd == "touch") {
        command = new Touch(cmd);
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
    // cp
    else if (cmd == "cp")
    {
        command = new Copy(cmd);
    }
    // // mv
    // else if (cmd == "mv")
    // {
        
    // }
    // rm
    else if (cmd == "rm")
    {
        command = new RM(cmd);
    }
    // // rmdir
    else if (cmd == "rmdir")
    {
        command = new RmDir(cmd);
    }
    // cat
    else if (cmd == "cat")
    {
        command = new CAT(cmd);
    }
    else if (cmd == "head")
    {
        command = new Head(cmd);
    }
    // tail
    else if (cmd == "tail")
    {
        command = new Tail(cmd);
    }
    // // less
    // else if (cmd == "less")
    // {
        
    // }
    // grep
    else if (cmd == "grep")
    {
        command = new Grep(cmd);
    }
    // wc
    else if (cmd == "wc")
    {
        command = new WC(cmd);   
    }
    // chmod
    else if (cmd == "chmod") {
        command = new ChMod(cmd);
    }
    // sort
    else if (cmd == "sort") {
        command = new Sort(cmd);
    }
    //who
    else if (cmd == "who") {
        command = new Who(cmd);
    }
    // history
    else if (cmd == "history")
    {
        command = new History(cmd);
    }
    // !x
    else if (cmd[0] == '!')
    {
        command = new HistoryIndex(cmd, managerRef);
    }
    // invalid command
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