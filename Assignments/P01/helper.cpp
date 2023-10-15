#pragma once
#include <filesystem>
#include <sstream>

#include "helper.h"

using namespace std;

std::vector<std::string> Helper::History;
bool Helper::HasRedirectO = false;
string Helper::Outfile = "";

string Helper::GetDir()
{
    string path = filesystem::current_path();
    
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == '"')
        {
            path.erase(i,1);
        }
    }

    return path;
}

string Helper::FormatDir(string path)
{
    string ignore, drive, user, pwd, formatted;
    stringstream ss(path);

    getline(ss, ignore, '/');
    getline(ss, drive, '/');
    getline(ss, user, '/');
    getline(ss, pwd, '\n');

    formatted = user + '@' + drive + ":~" + pwd + "% ";

    return formatted;
}

void Helper::UpdateHistory(string command)
{
    History.push_back(command);
}

string Helper::GetHistory()
{
    string list;
    for (int i = 0; i < History.size(); i++)
    {
        list += History.at(i) + '\n';
    }

    return list;
}

string Helper::GetCommandAtHistoryIndex(int index)
{
    return History.at(index);
}

int Helper::GetHistorySize()
{
    return History.size();
}

void Helper::SetHasRedirectO(bool _hasRedirectO, string output)
{
    HasRedirectO = _hasRedirectO;
    Outfile = output;
}

bool Helper::GetHasRedirectO()
{
    return HasRedirectO;
}

string Helper::GetOutfile()
{
    return Outfile;
}

string Helper::RemoveWhitespace(string _str) {
    string str = _str;
    // Remove whitespace to ensure correct path
    for (size_t i = 0; i < str.length(); ++i) {
        if (isspace(str[i])) {
            str.erase(i, 1);
            --i;  // Adjust index after erasing
        }
    }
    return str;
}