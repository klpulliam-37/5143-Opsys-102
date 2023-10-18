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

class MkDir: public Command
{
public:
    MkDir(string cmd) : Command(cmd) {};

    string Execute(string input) override;
};

class RmDir: public Command
{
public:
    RmDir(string cmd) : Command(cmd) {};

    string Execute(string input) override;
};

class CAT: public Command
{
public:
    CAT(string cmd) : Command(cmd) {};

    string Execute(string input) override;
};

class Head: public CAT
{
public:
    Head(string cmd) : CAT(cmd) {};

    string Execute(string input) override;
};

class Tail: public CAT
{
public:
    Tail(string cmd) : CAT(cmd) {};

    string Execute(string input) override;
};

class WC: public CAT
{
public:
    WC(string cmd) : CAT(cmd) {};

    string Execute(string input) override;

private:
    bool showLines = false;
    bool showWords = false;
    bool showCharacters = false;
};

class Grep: public Command
{
public:
    Grep(string cmd) : Command(cmd) {};

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

class Error: public Command
{
public: 
    Error(string cmd) : Command(cmd) {};

    string Execute(string input) override;
};