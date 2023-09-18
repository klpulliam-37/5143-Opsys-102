#pragma once
// #include <map>
#include <vector>
#include "command.h"

// Maybe try and foward declare later?
// class std::vector;
// class std::map;

class Manager
{
private:
    // std::map<std::string, std::vector<std::string>> CmdMap;
    vector<Command> Commands;

public:
    Manager();
    ~Manager();

private:
    void ParseCommand(std::string cmd);

public:
    void WaitForCommand();
};