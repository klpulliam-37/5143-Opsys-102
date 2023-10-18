#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// #include <filesystem>
// #include <sys/stat.h>
// #include <algorithm>

#include "manager.h"
#include "parser.h"
#include "cmdtypes.h"
#include "requests.h"
#include "helper.h"
#include "colors.h"

using namespace std;
// namespace fs = std::filesystem;

string LS::Execute(string input = "")
{
    Command::Execute(input);

    string path = Helper::RemoveWhitespace(GetArguments());

    string files = "";

    vector<map<string, string>> filesList = cpprequests::GetLS(path);
   
    string flags = PrintFlags();
    // cout << "Flags: " << flags << endl;

    // Check for show all flag
    if (flags.find('a') != string::npos)
    {
        // cout << "Show Hidden active\n";
        showHidden = true;
    }
    else if (flags.find('l') != string::npos)
    {
        // cout << "Long Listing active\n";
        longListing = true;
    }
    else if (flags.find('h') != string::npos)
    {
        // cout << "Human Readable active\n";
        humanReadable = true;
    }

    // -a
    if (showHidden && !longListing && !humanReadable)
    {


    }
    // -l
    else if (!showHidden && longListing && !humanReadable)
    {
        // cout << "Before Looping\n";
        Helper::SetIsSpecialPrint(true);
        for (int i = 0; i < filesList.size(); i++) {
            // cout << "Looping\n";
            string filename = "";
            if (filesList[i]["file_type"] == "directory") {
                filename = colors::BLUE() + filesList[i]["file_name"] + colors::RESET();
            }else {
                filename = filesList[i]["file_name"];
            }
            stringstream userinfo(cpprequests::GetUser(filesList[i]["user_id"]));
            string user = "", group = "";
            getline(userinfo, user);
            // getline(userinfo, group);
            // cout << "Before cout\n";
            cout << left << setw(11) << filesList[i]["permissions"] 
                << setw(user.length() + 1) << user
                << setw(user.length() + 1) << user
                << right << setw(6) << filesList[i]["file_size"]
                << setw(13) << Helper::ConvertDateTime(filesList[i]["modification_time"])
                << ' ' << filename << endl;
            files += filename + '\n';
        }

        // "file_name": "d.txt",
        // "file_size": 33,
        // "file_type": "file",
        // "group_id": 2,
        // "id": 11,
        // "modification_time": "2023-10-18T00:20:51.150793",
        // "permissions": "-rwxr-x--x",
        // "pid": 2,
        // "user_id": 1
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
    // no flags or all flags (-lah)
    else
    {
        for (int i = 0; i < filesList.size(); i++) {
            string filename = "";
            if (filesList[i]["file_type"] == "directory") {
                filename = colors::BLUE() + filesList[i]["file_name"] + colors::RESET();
            }else {
                filename = filesList[i]["file_name"];
            }
            files += filename + '\n';
        }
    }
    
    return files;
}

string PWD::Execute(string input = "")
{
    Command::Execute(input);

    string pwd = cpprequests::GetCWD();

    return pwd;
}

string CD::Execute(string input = "")
{
    Command::Execute(input);
    
    string newpath = "";

    string path = "";

    stringstream ss(GetArguments());
    getline(ss, path);

    path = Helper::RemoveWhitespace(path);

    newpath = cpprequests::ChangeDirectory(path);

    return "";
}

string MkDir::Execute(string input = "")
{
    Command::Execute(input);

    string dirName = "", entirePath = "", path = "", success = "", temp = "";
    
    stringstream args(GetArguments());
    getline(args, entirePath);
    entirePath = Helper::RemoveWhitespace(entirePath);

    stringstream part(entirePath);
    vector<string> pathParts;


    while (getline(part, temp, '/')) {
        pathParts.push_back(temp);
    }

    for (int i = 0; i < pathParts.size() - 1; i++) {
        path += pathParts.at(i) + '/';
    }

    dirName = pathParts.back();
    // cout << "Entire Path: " << entirePath << endl;
    // cout << "Path: " << Helper::RemoveWhitespace(path) << endl;
    // cout << "Dir Name: " << Helper::RemoveWhitespace(dirName) << endl;

    success = cpprequests::MakeDirectory(dirName, path);
    
    return "";
}

string RmDir::Execute(string input = "") 
{
    Command::Execute(input);

    string output = "";

    string path = "", success = "";

    stringstream ss(GetArguments());
    getline(ss, path);
    path = Helper::RemoveWhitespace(path);

    success = cpprequests::RemoveDirectory(path);
    
    return "";
}

string RM::Execute(string input = "") {
    Command::Execute(input);

    string fileName = "", entirePath = "", path = "", success = "", temp = "";
    
    stringstream args(GetArguments());
    getline(args, entirePath);
    entirePath = Helper::RemoveWhitespace(entirePath);

    stringstream part(entirePath);
    vector<string> pathParts;


    while (getline(part, temp, '/')) {
        pathParts.push_back(temp);
    }

    for (int i = 0; i < pathParts.size() - 1; i++) {
        path += pathParts.at(i) + '/';
    }

    fileName = pathParts.back();
    path = Helper::RemoveWhitespace(path);
    fileName = Helper::RemoveWhitespace(fileName);
    cout << "Entire Path: " << entirePath << endl;
    cout << "Path: " << path << endl;
    cout << "File Name: " << fileName << endl;

    success = cpprequests::Remove(fileName, path);
    
    return "";
}

string CAT::Execute(string input = "")
{
    Command::Execute(input);

    string output = "";

    if (input != "" && GetArguments() == "") {
        // cout << "Args: '" << GetArguments() << "'\n";
        output = input;
    } else {
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
                    output += files[i]["contents"];
                }
            }
        }
        output += '\n';
    }
    

    return output;
}

string Head::Execute(string input = "") 
{
    string output = "";
    string contents = CAT::Execute(input);

    // cout << "Contents: \n" << contents << endl;

    int numLines = 10;
    string fileName = "", lines = "", line = "";
    string flags = PrintFlags();
    stringstream args(GetArguments());
    stringstream contentReader(contents);

    getline(args, fileName, ' ');

    if (flags.find('n') != string::npos) {
        getline(args, lines);
        numLines = stoi(lines);
    } // Should do additional checks to see if there are more args provided,
        // and if so, to cancel the command

    fileName = Helper::RemoveWhitespace(fileName);
    lines = Helper::RemoveWhitespace(lines);

    for (int i = 0; i < numLines; i++) {
        getline(contentReader, line);
        output += line + '\n';
    }
    
    return output;
}

string Tail::Execute(string input = "") 
{
    string output = "";
    
    string contents = CAT::Execute(input);

    // cout << "Contents: \n" << contents << endl;

    int numLines = 10;
    string fileName = "", lines = "", line = "";
    string flags = PrintFlags();
    vector<string> lineList;
    stringstream args(GetArguments());
    stringstream contentReader(contents);

    getline(args, fileName, ' ');

    if (flags.find('n') != string::npos) {
        getline(args, lines);
        numLines = stoi(lines);
    } // Should do additional checks to see if there are more args provided,
        // and if so, to cancel the command

    fileName = Helper::RemoveWhitespace(fileName);
    lines = Helper::RemoveWhitespace(lines);

    while(getline(contentReader, line)) {
        lineList.push_back(line);
    }

    for (int i = numLines; i > 0; i--) {
        int index = lineList.size() - i;
        output += lineList[index] + '\n';
    }
    
    return output;
}

// Still needs some work, not giving exact values for words and characters.
// Off by one on both. Extra character and missing words when no spaces.
string WC::Execute(string input = "") {
    string output = "";
    string contents = CAT::Execute(input);
    string flags = PrintFlags();

    // Check for show all flag
    if (flags.find('l') != string::npos)
    {
        showLines = true;
    }
    if (flags.find('w') != string::npos)
    {
        showWords = true;
    }
    if (flags.find('c') != string::npos)
    {
        showCharacters = true;
    }

    int lineCount = 0, wordCount = 0, characterCount = 0;
    string copy = contents;
    string line = "", word = "", character = "";
    stringstream stream(copy);

    bool isNull = false;

    // Count the number of lines
    for (int i = 0; i < copy.size(); i++) {
        if (copy[i] == '\n') {
            lineCount++;
        } else if (copy[i] == ' ') {
            wordCount++;
        } else if (isalnum(copy[i]) && copy[i+1] == '\0') {
            wordCount++;
            characterCount++;
        } else {
            characterCount++;
        }
    }

    // -l
    if (showLines && !showWords && !showCharacters)
    {
        
        output = to_string(lineCount) + '\n';
    }
    // -w
    else if (!showLines && showWords && !showCharacters)
    {
        output = to_string(wordCount) + '\n';
    }
    // -c
    else if (!showLines && !showWords && showCharacters)
    {
        output = to_string(characterCount) + '\n';
    }
    // -lw
    else if (showLines && showWords && !showCharacters)
    {
        output = "     " + to_string(lineCount) + "     " + to_string(wordCount) + '\n';
    }
    // -lc
    else if (showLines && !showWords && showCharacters)
    {
        output = "     " + to_string(lineCount) + "     " + to_string(characterCount) + '\n';
    }
    // -wc
    else if (!showLines && showWords && showCharacters)
    {
        output = "     " + to_string(wordCount) + "     " + to_string(characterCount) + '\n';
    }
    // no flags or all flags (-lwc)
    else
    {
        output = "     " + to_string(lineCount) + "     " + to_string(wordCount) + "     " + to_string(characterCount) + '\n';
    }

    return output;
}

string Grep::Execute(string input = "") 
{
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

    // if (Helper::GetHasRedirectO() || GetPrints()) {
    //     cout << lines;
    // }

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

string Error::Execute(string input = "") 
{
    Command::Execute(input);

    string error = colors::RED() + "Error: " + GetCmd() + " command not found." + colors::RESET();

    cout << error << endl;

    return "";
}