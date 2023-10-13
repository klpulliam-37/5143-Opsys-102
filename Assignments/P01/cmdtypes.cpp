#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <sys/stat.h>
#include <algorithm>

#include "manager.h"
#include "parser.h"
#include "cmdtypes.h"
#include "helper.h"

using namespace std;
namespace fs = std::filesystem;

string LS::Execute(string input = "")
{
    Command::Execute(input);

    if (!Helper::GetHasRedirectO())
    {
        // vector<string> flags = GetFlags();
        string flags = PrintFlags();

        // Check for show all flag
        if (flags.find('a') != string::npos)
        {
            showHidden = true;
        }
        else if (flags.find('l') != string::npos)
        {
            longListing = true;
        }
        else if (flags.find('h') != string::npos)
        {
            humanReadable = true;
        }

        // Path to the directory
        std::string path = Helper::GetDir();
    
        // This structure would distinguish a file from a
        // directory
        struct stat sb;
    
        // Looping until all the items of the directory are
        // exhausted
        for (const auto& entry : fs::directory_iterator(path)) 
        {
            // Converting the path to const char * in the
            // subsequent lines
            std::filesystem::path outfilename = entry.path();
            std::string outfilename_str = outfilename.string();
            const char* path = outfilename_str.c_str();
    
            // Testing whether the path points to a
            // non-directory or not If it does, displays path
            if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
            {
                stringstream ss(path);
                vector<string> filepath;
                string word;

                while(!ss.eof())
                {
                    getline(ss, word, '/');
                    filepath.push_back(word);
                }

                // -a
                if (showHidden && !longListing && !humanReadable)
                {
                    cout << filepath.back() << '\n';
                }
                // -l
                else if (!showHidden && longListing && !humanReadable)
                {
                    
                }
                // -h
                else if (!showHidden && !longListing && humanReadable)
                {
                    
                }
                // -al
                else if (showHidden && longListing && !humanReadable)
                {
                    
                }
                // -ah
                else if (showHidden && !longListing && humanReadable)
                {
                    
                }
                // -lh
                else if (!showHidden && longListing && humanReadable)
                {
                    
                }
                // -alh
                else if (showHidden && longListing && humanReadable)
                {
                    
                }
                // no flags
                else
                {
                    if (filepath.back()[0] != '.')
                    {
                        cout << filepath.back() << '\n';
                    }
                }
            }
        }
    }
}

string PWD::Execute(string input = "")
{
    Command::Execute(input);

    string pwd = Helper::GetDir();
    if (!Helper::GetHasRedirectO())
    {
        cout << pwd << '\n';
    }
    return pwd;
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
            cout << historyIndex++ << " " << command << "\n";
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