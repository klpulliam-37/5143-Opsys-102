#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>

#include "cmdtypes.h"
#include "helper.h"

using namespace std;
namespace fs = std::filesystem;

string LS::Execute(string input = "")
{
    Command::Execute(input);

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
            cout << filepath.back() << endl;
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

    string history = Helper::GetHistory();
    if (!Helper::GetHasRedirectO())
    {
        cout << history;
    }
    return history;
}