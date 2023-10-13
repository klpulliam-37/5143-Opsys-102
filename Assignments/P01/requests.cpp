#pragma once
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "requests.h"
#include "jsonhandler.h"

namespace cpprequests {
    std::string url = "http://127.0.0.1:5000";
    cpr::Header header = cpr::Header{{"Content-Type", "application/json"}};
    std::string session_id = "";
    std::string username = "";

    void SetSessionID(std::string _session_id) {
        session_id = _session_id;
    }

    std::string GetSessionID() {
        return session_id;
    }

    void SetUsername(std::string _username) {
        username = _username;
    }

    std::string GetUsername() {
        return username;
    }

    bool StartSession(std::string username, std::string password) {
        cpr::Response r = cpr::Post(
                                cpr::Url{url + "/session"},
                                header,
                                cpr::Body{"{\r\n    \"username\": \"" + username + "\",\r\n    \"password\": \"" + password + "\"\r\n}"}
                            );

        // std::cout << "Status Code: " << r.status_code << '\n';
        if(r.status_code == 0)
        {
            std::cerr << r.error.message << std::endl;
            return false;
        }
        else if (r.status_code == 401) {
            std::cerr << "Error: Invalid Credentials" << std::endl;
            return false;
        }
        else if (r.status_code >= 400) {
            // std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
            return false;
        }

        // std::cout << "Text: " << r.text << '\n';
        const char* text = r.text.c_str();

        SetSessionID(jsonhandler::ExtractValue(jsonhandler::StringToJson(text), "session_id"));
        SetUsername(jsonhandler::ExtractValue(jsonhandler::StringToJson(text), "username"));

        return true;
    }

    std::string GetCWD() {
        cpr::Response r = cpr::Get(
            cpr::Url{url + "/utilities/pwd"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << "Response Text: " << text << std::endl;
        std::string cwd = jsonhandler::ExtractValue(jsonhandler::StringToJson(text), "cwd");

        return cwd;
    }

    std::string GetShellPath() {
        return GetUsername() + ":~" + GetCWD();
    }
}

