#pragma once
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "jsonhandler.h"

namespace cpprequests {
    std::string session_id = "";

    void ExampleGet() {
        cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                                cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                                cpr::Parameters{{"anon", "true"}, {"key", "value"}});
        std::cout << "Status code: " << r.status_code << '\n';
        std::cout << "Header:\n";
        for (const std::pair<const std::basic_string<char>, std::basic_string<char>>& kv : r.header) {
            std::cout << '\t' << kv.first << ':' << kv.second << '\n';
        }
        std::cout << "Text: " << r.text << '\n';
    }

    // It works!!!
    void StartSession() {
        cpr::Response r = cpr::Post(
                                cpr::Url{"http://127.0.0.1:5000/session"},
                                cpr::Header{{"Content-Type", "application/json"}},
                                cpr::Body{"{\r\n    \"username\": \"utest1\",\r\n    \"password\": \"password\"\r\n}"}
                                // cpr::Payload{{"username", "utest1"}, {"password", "password"}}
                            );

        std::cout << "Status Code: " << r.status_code << '\n';
        if(r.status_code == 0)
            std::cerr << r.error.message << std::endl;
        else if (r.status_code >= 400) {
            std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
        } else {
            std::cout << "Request took " << r.elapsed << std::endl;
            std::cout << "Body:" << std::endl << r.text;
        }
        std::cout << "Text: " << r.text << '\n';
        const char* text = new char[r.text.length()];
        jsonhandler::PrintSession(jsonhandler::StringToJson(text));
    }
}

