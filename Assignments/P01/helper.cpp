#pragma once
// #include <filesystem>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
// #include <chrono>

#include "helper.h"
#include "colors.h"

using namespace std;

std::vector<std::string> Helper::History;
bool Helper::HasRedirectO = false;
bool Helper::IsAppendMode = false;
bool Helper::IsSpecialPrint = false;
string Helper::Outfile = "";

// string Helper::GetDir()
// {
//     string path = filesystem::current_path();
    
//     for (int i = 0; i < path.size(); i++)
//     {
//         if (path[i] == '"')
//         {
//             path.erase(i,1);
//         }
//     }

//     return path;
// }

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

void Helper::SetIsAppendMode(bool _IsAppendMode) {
    IsAppendMode = _IsAppendMode;
}

bool Helper::GetIsAppendMode() {
    return IsAppendMode;
}

void Helper::SetIsSpecialPrint(bool _IsSpecialPrint) {
    IsSpecialPrint = _IsSpecialPrint;
}

bool Helper::GetIsSpecialPrint() {
    return IsSpecialPrint;
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

std::string Helper::ConvertDateTime(std::string _datetime) {
    std::tm datetime = {};

    // Parse the input datetime string
    std::istringstream ss(_datetime);
    ss >> std::get_time(&datetime, "%Y-%m-%dT%H:%M:%S");

    if (ss.fail()) {
        std::cout << colors::RED() << "Failed to parse datetime string." << colors::RESET() << std::endl;
        return "";
    }

    // Format the datetime into the desired output format
    std::ostringstream formattedDatetime;
    formattedDatetime << std::put_time(&datetime, "%b %d %H:%M");

    return formattedDatetime.str();
}
