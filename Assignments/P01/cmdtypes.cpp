#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <filesystem>
#include <sys/stat.h>
#include <algorithm>

#include "manager.h"
#include "parser.h"
#include "cmdtypes.h"
#include "requests.h"
#include "helper.h"
#include "colors.h"

using namespace std;
namespace fs = std::filesystem;

string LS::Execute(string input = "")
{
    Command::Execute(input);

    string fileNames = "";

    vector<pair<string, string>> files = cpprequests::GetLS();

    string filename = "";
    // Iterate over the vector using a range-based for loop
    for (const pair<string, string>& file : files) {
        if (file.second == "directory") {
            filename = colors::BLUE() + file.first + colors::RESET();
        }else {
            filename = file.first;
        }
        if (Helper::GetHasRedirectO() || GetPrints()) {
            cout << filename << endl;
        }
        fileNames += filename + '\n';
    }

    return fileNames;

    // if (!Helper::GetHasRedirectO())
    // {
        // // vector<string> flags = GetFlags();
        // string flags = PrintFlags();

        // // Check for show all flag
        // if (flags.find('a') != string::npos)
        // {
        //     showHidden = true;
        // }
        // else if (flags.find('l') != string::npos)
        // {
        //     longListing = true;
        // }
        // else if (flags.find('h') != string::npos)
        // {
        //     humanReadable = true;
        // }

        // // -a
        // if (showHidden && !longListing && !humanReadable)
        // {
        //     cout << filepath.back() << '\n';
        // }
        // // -l
        // else if (!showHidden && longListing && !humanReadable)
        // {
            
        // }
        // // -h
        // else if (!showHidden && !longListing && humanReadable)
        // {
            
        // }
        // // -al
        // else if (showHidden && longListing && !humanReadable)
        // {
            
        // }
        // // -ah
        // else if (showHidden && !longListing && humanReadable)
        // {
            
        // }
        // // -lh
        // else if (!showHidden && longListing && humanReadable)
        // {
            
        // }
        // // -alh
        // else if (showHidden && longListing && humanReadable)
        // {
            
        // }
        // // no flags
        // else
        // {
        //     if (filepath.back()[0] != '.')
        //     {
        //         cout << filepath.back() << '\n';
        //     }
        // }
    // }
        
}

string PWD::Execute(string input = "")
{
    Command::Execute(input);

    string pwd = cpprequests::GetCWD();
    if (Helper::GetHasRedirectO() || GetPrints())
    {
        cout << pwd << '\n';
    }
    return pwd;
}

string CD::Execute(string input = "")
{
    Command::Execute(input);
    
    string newpath = "";

    string path = "";

    stringstream ss(GetArguments());
    getline(ss, path);

    // Remove whitespace to ensure correct path
    for (size_t i = 0; i < path.length(); ++i) {
        if (isspace(path[i])) {
            path.erase(i, 1);
            --i;  // Adjust index after erasing
        }
    }

    // cout << "Path: '" << path << "'" << endl;
    newpath = cpprequests::ChangeDirectory(path);

    if (Helper::GetHasRedirectO() || GetPrints()) {
        cout << newpath << endl;
    }

    return newpath;
}

string MkDir::Execute(string input = "")
{
    Command::Execute(input);

    string dirName = "", path = "", success = "";

    stringstream ss(GetArguments());
    getline(ss, dirName);
    dirName = Helper::RemoveWhitespace(dirName);
    if (!ss.eof()) {
        getline(ss, path);
        success = cpprequests::MakeDirectory(dirName, path);
    }else{
        success = cpprequests::MakeDirectory(dirName);
    }
    
    return success;
}

string CAT::Execute(string input = "")
{
    Command::Execute(input);

    string output = "";
    vector<map<string, string>> files = cpprequests::CAT();
    stringstream ss(GetArguments());
    string fileName;

    while (getline(ss, fileName, ' ')) {
        fileName = Helper::RemoveWhitespace(fileName);
        
        // Find the files specified in the cmd arguments and ensure it is a file.
        // If the file doesn't exist, then ignore it.
        for (int i = 0; i < files.size(); i++) {
            if (files[i]["file_name"] == fileName) {
                if (files[i]["file_type"] == "directory") {
                    cout << colors::RED() << "cat: " << fileName << ": Is a directory" << colors::RESET() << endl;
                }
                else if ((Helper::GetHasRedirectO() || GetPrints())) {
                    cout << files[i]["contents"] + '\n';
                }
                output += files[i]["contents"];
            }
        }
    }

    return output;
}

string Grep::Execute(string input = "") {
    Command::Execute(input);

    // Get the keyword(first arg), and check for it in the file(second arg)
    string keyword = "", fileName = "", contents = "", lines = "", line = "";
    // cout << "Args: " << GetArguments() << endl;
    stringstream ssArgs(GetArguments());
    getline(ssArgs, keyword, ' ');
    getline(ssArgs, fileName);

    keyword = Helper::RemoveWhitespace(keyword);
    fileName = Helper::RemoveWhitespace(fileName);

    // Get a files contents, split on newlines, and check for the keyword
    // Also highlight the word in the string
    // cout << "Before Grep\n";
    if (input != "") {
        contents = input;
    } else {
        contents = cpprequests::Grep(keyword, fileName);
    }
    
    // cout << "After Grep\n";
    stringstream ss(contents);

    while(getline(ss, line)) {
        // cout << "Before find\n";
        size_t phrase = line.find(keyword);
        // cout << "After find\n";
        if (phrase != string::npos) {
            string part1 = line.substr(0,phrase);
            string part2 = line.substr(phrase, keyword.size());
            string part3 = line.substr(phrase + keyword.size(), line.size() - (phrase + keyword.size()));
            line = part1 + colors::RED() + part2 + colors::RESET() + part3;
            lines += line + '\n';
        }
    }

    if (Helper::GetHasRedirectO() || GetPrints()) {
        cout << lines;
    }

    return lines;
}

string History::Execute(string input = "")
{
    Command::Execute(input);
    // Be sure to adjust index to index - 1 when 
    // accessing history list in manager.
    int historyIndex = 1;

    string history = Helper::GetHistory();
    stringstream ss(history);
    if (!Helper::GetHasRedirectO())
    {
        string command = "";
        while(getline(ss, command))
        {
            if (Helper::GetHasRedirectO() || GetPrints()) {
                cout << historyIndex++ << " " << command << "\n";
            }
        }
    }
    return history;
}

string HistoryIndex::Execute(string input = "")
{
    Command::Execute(input);

    int commandIndex = stoi(GetCmd().erase(0,1));
    // cout << "Index: " << commandIndex << endl;
    // need to get specified index from parser, so index check logic goes here
    if (commandIndex < 1 || commandIndex > Helper::GetHistorySize())
    {
        cout << "WARNING: Invalid Index for !x command.\n";
        return "";
    }
    else
    {
        // cout << "Command At Index: " << commandIndex << " -> " << Helper::GetCommandAtHistoryIndex(commandIndex) << endl;
        managerRef->parser->SplitCommand(Helper::GetCommandAtHistoryIndex(commandIndex - 1));
    }

    // use managerRef to reparse command
}

string Error::Execute(string input = "") {
    Command::Execute(input);

    string error = colors::RED() + "Error: " + GetCmd() + " command not found." + colors::RESET();

    if (Helper::GetHasRedirectO() || GetPrints()) {
        cout << error << endl;
    }

    return error;
}