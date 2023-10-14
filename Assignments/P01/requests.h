#pragma once
// class cpr;
// class Header;

namespace cpprequests {
    void SetSessionID(std::string _session_id);
    std::string GetSessionID();
    void SetUsername(std::string _username);
    std::string GetUsername();

    bool StartSession(std::string username, std::string password);
    std::string GetCWD();
    std::string GetShellPath();
    std::vector<std::pair<std::string, std::string>> GetLS();
}

