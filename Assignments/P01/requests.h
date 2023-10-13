#pragma once
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "jsonhandler.h"

namespace cpprequests {
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

    // cpr::Response CreateSession(std::string username, std::string password) {
    //     cpr::Response r = cpr::Post(
    //                             cpr::Url{"http://127.0.0.1:5000/session"},
    //                             cpr::Header{{"Content-Type", "application/json"}},
    //                             cpr::Body{"{\r\n    \"username\": \"" + username + "\",\r\n    \"password\": \"" + password + "\"\r\n}"}
    //                         );
        
    //     return r;
    // }

    // void ValidateCredentials(std::string username, std::string password, cpr::Response r) {
    //     while (r.status_code == 401) {
    //         std::cerr << "Error: Invalid Credentials" << std::endl;

    //         std::string username = "", password = "";

    //         std::cout << "Please enter your username: ";
    //         std::cin >> username;

    //         std::cout << "Please enter your password: ";
    //         std::cin >> password;

    //         CreateSession(username, password);
    //     }
    // }

    bool StartSession(std::string username, std::string password) {
        cpr::Response r = cpr::Post(
                                cpr::Url{"http://127.0.0.1:5000/session"},
                                cpr::Header{{"Content-Type", "application/json"}},
                                cpr::Body{"{\r\n    \"username\": \"" + username + "\",\r\n    \"password\": \"" + password + "\"\r\n}"}
                            );

        std::cout << "Status Code: " << r.status_code << '\n';
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
            std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
            return false;
        }

        std::cout << "Text: " << r.text << '\n';
        const char* text = r.text.c_str();

        SetSessionID(jsonhandler::ExtractSessionID(jsonhandler::StringToJson(text)));
        SetUsername(jsonhandler::ExtractUsername(jsonhandler::StringToJson(text)));

        return true;
    }
}

