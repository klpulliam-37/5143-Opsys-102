#pragma once
#include <filesystem>
#include <sstream>

#include "helper.h"

using namespace std;

std::vector<std::string> Helper::History;
bool Helper::HasRedirectO;

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

void Helper::SetHasRedirectO(bool _hasRedirectO)
{
    HasRedirectO = _hasRedirectO;
}

bool Helper::GetHasRedirectO()
{
    return HasRedirectO;
}