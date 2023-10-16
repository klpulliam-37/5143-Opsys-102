#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include "requests.h"
#include "jsonhandler.h"
#include "colors.h"

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

    std::string GetPathByID(std::string id) {
        cpr::Response r = cpr::Get(
            cpr::Url{url + "/path"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"id\": \"" + id + "\"\r\n}"}
        );
        std::string text = r.text;
        // std::cout << "Path by ID: " << text << std::endl;

        return text;
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
            std::cerr << colors::RED() << "Error: Invalid Credentials" << colors::RESET() << std::endl;
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
        return colors::GREEN() + GetUsername() + 
        colors::RESET() + ":" + 
        colors::LIGHT_BLUE() + "~" + GetCWD() + 
        colors::RESET() + "% ";
    }

    std::vector<std::pair<std::string, std::string>> GetLS() {
        cpr::Response r = cpr::Get(
            cpr::Url{url + "/utilities/ls"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        std::vector<std::pair<std::string, std::string>> files = jsonhandler::ParseList(jsonhandler::StringToJson(text), "file_name");
        return files;
    }

    std::string ChangeDirectory(std::string path) {
        cpr::Response r = cpr::Post(
            cpr::Url{url + "/utilities/cd"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"path\": \"" + path + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        std::string newpath = jsonhandler::ExtractValue(jsonhandler::StringToJson(text), "new_path");

        return newpath;
    }

    std::string MakeDirectory(std::string dirName, std::string path) {
        std::string body = "";

        if (path == "") {
            // body = "{\r\n    \"file_name\": \"" + dirName + "\",\r\n    \"file_type\": \"directory\",\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"contents\": \"\"\r\n}";
            body = "{\r\n    \"file_name\": \"" + dirName + "\",\r\n    \"file_type\": \"directory\",\r\n    \"session_id\": \"" + GetSessionID() + "\"\r\n}";
        }else{
            // body = "{\r\n    \"file_name\": \"" + dirName + "\",\r\n    \"file_type\": \"directory\",\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"contents\": \"\",\r\n    \"path\": \"" + path + "\"\r\n}";
            body = "{\r\n    \"file_name\": \"" + dirName + "\",\r\n    \"file_type\": \"directory\",\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"path\": \"" + path + "\"\r\n}";
        }

        cpr::Response r = cpr::Post(
            cpr::Url{url + "/path"},
            header,
            cpr::Body{body}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        std::string success = jsonhandler::ExtractValue(jsonhandler::StringToJson(text), "Success");

        return success;
    }

    std::vector<std::map<std::string, std::string>> CAT() {
        cpr::Response r = cpr::Get(
            cpr::Url{url + "/utilities/ls"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        std::vector<const char*> keys;
        keys.push_back("file_name");
        keys.push_back("file_type");
        keys.push_back("id");
        // keys.push_back("contents");

        std::vector<std::map<std::string, std::string>> filesObj = jsonhandler::ParseObjs(jsonhandler::StringToJson(text), keys);
        // jsonhandler::PrintObjs(filesObj);

        for (int m = 0; m < filesObj.size(); m++) {
            // std::cout << "ID: " << filesObj[m]["id"] << std::endl;
            std::string str_text = GetPathByID(filesObj[m]["id"]);
            const char* cstr_text = str_text.c_str();
            // std::cout << "str_text: " << str_text << std::endl;
            // std::cout << "cstr_text: " << cstr_text << std::endl;
            std::string contents = jsonhandler::ExtractValue(jsonhandler::StringToJson(cstr_text), "contents");
            // std::cout << "Contents: \n" << contents << std::endl;
            filesObj[m].insert(std::pair<std::string, std::string>("contents", contents));
        }
        // jsonhandler::PrintObjs(filesObj);

        return filesObj;
    }
}

