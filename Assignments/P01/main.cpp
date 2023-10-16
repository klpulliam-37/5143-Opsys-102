// TODO: Create the append functionality when redirecting to a file, AKA '>>' token
// TODO: Implement the rest of the commands now that the program is connected 
//       to the Virtual-File-System
//       - head, less, tail, rmdir, rm, mv, cp, grep, wc, chmod, sort, who, append, input redirect, paging
// TODO: Implement optional path parameter for ls command
// TODO: Fix !x command, causes aborted error and not sure why
// TODO: Handle bad flags
// TODO: Implement --help flag for each command and a general help command
// TODO: Handle user login timeout by checking if r.status_code is == 409

#include <iostream>
#include "manager.h"
#include "parser.h"
#include "requests.h"
#include "jsonhandler.h"

void ShellDriver();
void RequestsDriver();
void RapidJsonDriver();

int main() 
{
    // RapidJsonDriver();
    // RequestsDriver();
    ShellDriver();
    return 0;
}

void ShellDriver() {
    bool shouldRun = true;
    Manager* manager = new Manager();
    manager->SetupManager();

    while(shouldRun)
    {
        shouldRun = manager->WaitForCommand();
    }
    manager->SaveHistory();
}

void RequestsDriver() {
    // cpprequests::StartSession();
    // cpprequests::GetLS();
}

void RapidJsonDriver() {
    // jsonhandler::jsonexample();
    // jsonhandler::ParseTest();
}
