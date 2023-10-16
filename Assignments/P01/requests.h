#pragma once
#include <map>

// class cpr;
// class Header;

namespace cpprequests {
    void SetSessionID(std::string _session_id);
    std::string GetSessionID();
    void SetUsername(std::string _username);
    std::string GetUsername();

    std::string GetPathByID(std::string id);

    bool StartSession(std::string username, std::string password);
    std::string GetCWD();
    std::string GetShellPath();
    std::vector<std::pair<std::string, std::string>> GetLS();
    std::string ChangeDirectory(std::string path);
    std::string MakeDirectory(std::string dirName, std::string path = "");
    // std::string Touch(std::string fileName);
    std::vector<std::map<std::string, std::string>> CAT();
}

