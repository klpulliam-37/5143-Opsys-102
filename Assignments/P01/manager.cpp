#include <iostream>
#include <string>
#include <sstream>
#include "manager.h"
#include "command.h"

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

    Commands.push_back(Command(word));

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
        cout << "Command Index: " + to_string(CommandIndex) + '\n' + command->PrintCommand() + '\n';
        CommandIndex++;
    }
}

void Manager::ClearCommands()
{
    Commands.clear();
    CommandIndex = 0;
}