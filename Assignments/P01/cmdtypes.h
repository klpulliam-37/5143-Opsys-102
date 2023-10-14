#pragma once
#include "cmd.h"

class Manager;

class LS: public Command
{
public: 
    LS(string cmd) : Command(cmd) {};

    string Execute(string input) override;

private:
    bool showHidden = false;
    bool longListing = false;
    bool humanReadable = false;
};

class PWD: public Command
{
public:
    PWD(string cmd) : Command(cmd) {};

    string Execute(string input) override;

private:

};

class CD: public Command
{
public:
    CD(string cmd) : Command(cmd) {};

    string Execute(string input) override;
};

class History: public Command
{
public:
    History(string cmd) : Command(cmd) {};

    string Execute(string input) override;
};

class HistoryIndex: public Command
{
private:
    Manager* managerRef;

public:
    HistoryIndex(string cmd, Manager* _managerRef) : Command(cmd) {managerRef = _managerRef;};

    string Execute(string input) override;
};