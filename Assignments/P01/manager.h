#pragma once
// #include <map>
#include <vector>

class Parser;
class Command;

// Maybe try and foward declare later?
// class std::vector;

class Manager
{
private:
    std::vector<Command*> Commands;
    Parser* parser;
    // string altInput;
    bool hasRedirectO = false;
    string outfile;

public:
    Manager();
    ~Manager();

private:
    void PrintCommands();
    void ClearCommands();
    // void ParseCommands(std::string cmds);

public:
    void SetupManager();
    void WaitForCommand();
    void AddCommand(Command* command);
    void ExecuteCommands();
    // void SetInput(string _input);
    // string GetInput();
    void SetORedirect(bool _hasRedirectO, string outfile);

    // void TestDeriv();

};