#pragma once

class Manager;
class Command;

class Parser
{
public:
    Parser();
    ~Parser();

private:
    Manager* managerRef;

protected:

public:
    void SplitCommand(std::string cmds);
    Command* CreateCommand(std::string cmd);
    Command DetermineCommand(std::string cmd);

    void SetManager(Manager* manager);
};