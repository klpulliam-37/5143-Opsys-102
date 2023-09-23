#pragma once
// #include <map>
#include <vector>

class Parser;
class Command;

// Maybe try and foward declare later?
// class std::vector;
// class std::map;

class Manager
{
private:
    std::vector<Command*> Commands;
    int CommandIndex = 0;
    Parser* parser;

public:
    Manager();
    ~Manager();

private:
    void PrintCommands();
    void ClearCommands();

public:
    void SetupManager();
    void WaitForCommand();
    void AddCommand(Command& command);
    void ExecuteCommands();

    void TestDeriv();

};