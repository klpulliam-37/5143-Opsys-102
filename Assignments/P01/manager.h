#pragma once
// #include <map>
#include <vector>

class Command;

// Maybe try and foward declare later?
// class std::vector;
// class std::map;

class Manager
{
private:
    // std::map<std::string, std::vector<std::string>> CmdMap;
    std::vector<Command> Commands;
    int CommandIndex = 0;


public:
    Manager();
    ~Manager();

private:
    void ParseCommand(std::string cmd);

public:
    void WaitForCommand();
    void PrintCommands();
    void ClearCommands();
};