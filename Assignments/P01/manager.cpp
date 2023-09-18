#include <iostream>
#include <string>
#include <sstream>
#include "manager.h"

using namespace std;

Manager::Manager()
{

}

Manager::~Manager()
{

}

void Manager::ParseCommand(string cmd)
{
    // Create stream object and have it parse line into seperate strings
    stringstream ss(cmd);
    string word;

    // Store first string as a cmd
    ss >> word;
    // CmdMap[word] = vector<string>;
    Commands.push_back(new Command(word));

    // For every string, print it
    while (ss >> word)
    {
        // Store strings based on:
        // - cmd
        // - flags going with cmd
        // cout << word << '\n';
        // cout << CmdMap["cmd"];
        
        // If |, then create new cmd in CmdMap
        // If -, then add as a flag to previous cmd
    }
}

void Manager::WaitForCommand()
{
    string cmd;
    cout << "% ";
    getline(cin, cmd);
    // cout << cmd << '\n';

    ParseCommand(cmd);
}