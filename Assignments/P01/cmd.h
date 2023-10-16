#pragma once
#include <vector>
#include <string>

using namespace std;

class Command
{
public:
    Command();
    Command(string cmd);
    ~Command();

private:
    string name;
    vector<string> flags;
    // Need to change this to vector<string> later for multiple redirects.
    string redirects; 
    vector<string> arguments;
    bool bPrints = false;

public:
    string GetCmd();
    vector<string> GetFlags();
    string GetRedirects();
    string GetArguments();
    bool GetPrints();

    void SetCmd(string cmd);
    void SetFlags(string flag);
    void SetRedirects(string _redirects);
    void SetArguments(string _arguments);
    void SetPrint(bool _bPrints);
    string PrintFlags();
    string PrintCommand();

    virtual string Execute(string input);

};