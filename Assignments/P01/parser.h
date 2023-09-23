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
    void CreateCommand(std::string cmd);

    void SetManager(Manager* manager);
};