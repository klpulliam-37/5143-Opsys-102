// TODO: Commands being piped should also not display information to the shell
// TODO: Create the append functionality when redirecting to a file, AKA >>
// TODO: Implement the rest of the commands now that the program is connected 
//       to the Virtual-File-System
// TODO: Implement optional path parameter for ls command
// TODO: Fix !x command, causes aborted error and not sure why
// TODO: cd command still works on files, need to fix
// TODO: not passing contents when making a directory results in a failed request.
//       contents should not be required. Handled the error with path["contents"] being null,
//       need to push now.

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
