#pragma once
#include "command.h"

class LS: public Command
{
public: 
    LS(string cmd) : Command(cmd) {};

    string Execute(string input) override;

private:

};

class PWD: public Command
{
public:
    PWD(string cmd) : Command(cmd) {};

    string Execute(string input) override;

private:

};

class History: public Command
{
public:
    History(string cmd) : Command(cmd) {};

    string Execute(string input) override;
};