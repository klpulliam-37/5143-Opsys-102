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

    std::vector<std::map<std::string, std::string>> GetLS(std::string path) {
        std::string body = "";
        if (path == "") {
            body = "{\r\n    \"session_id\": \"" + GetSessionID() + "\"\r\n}";
        } else {
            body = "{\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"path\": \"" + path + "\"\r\n}";
        }

        cpr::Response r = cpr::Get(
            cpr::Url{url + "/utilities/ls"},
            header,
            cpr::Body{body}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        std::vector<const char*> keys;
        keys.push_back("file_name");
        keys.push_back("file_type");
        keys.push_back("file_size");
        keys.push_back("group_id");
        keys.push_back("id");
        keys.push_back("modification_time");
        keys.push_back("permissions");
        keys.push_back("pid");
        keys.push_back("user_id");

        std::vector<std::map<std::string, std::string>> files = jsonhandler::ParseObjs(jsonhandler::StringToJson(text), keys);
        return files;
    }

    std::string GetUser(std::string user_id) {
        cpr::Response r = cpr::Get(
            cpr::Url{url + "/users"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        std::vector<const char*> keys;
        keys.push_back("id");
        keys.push_back("username");
        keys.push_back("groups");

        std::vector<std::map<std::string, std::string>> filesObj = jsonhandler::ParseObjs(jsonhandler::StringToJson(text), keys);
        // std::cout << "File Name: " << fileName << std::endl;
        // jsonhandler::PrintObjs(filesObj);

        std::string userinfo = "";
        for (int m = 0; m < filesObj.size(); m++) {
            // std::cout << "Looping: " << m << std::endl;
            // std::cout << "Object File Name: " << filesObj[m]["file_name"] << std::endl;
            
            if (filesObj[m]["id"] == user_id) {
                std::vector<const char*> nameKey;
                // const char* groupObj = filesObj[m]["group"].c_str();
                // std::cout << "Groups: " << groupObj << std::endl;
                // std::vector<std::map<std::string, std::string>> group = jsonhandler::ParseObjs(jsonhandler::StringToJson(groupObj), nameKey);
                userinfo = filesObj[m]["username"] /*+ ' ' + group[0]["name"]*/;
            }
        }

        return userinfo;
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

    std::string RemoveDirectory(std::string path) {
        cpr::Response r = cpr::Delete(
            cpr::Url{url + "/path"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"path\": \"" + path + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        if (r.status_code >= 404) {
            std::cout << colors::RED() << "Error: Doesn't exist" << colors::RESET() << std::endl;
            return "false";
        }

        // std::cout << text << std::endl;

        std::string success = jsonhandler::ExtractValue(jsonhandler::StringToJson(text), "Success");
        // std::string message = jsonhandler::ExtractValue(jsonhandler::StringToJson(text), "message");

        return success;
    }

    std::string Remove(std::string fileName, std::string path) {
        cpr::Response r = cpr::Get(
            cpr::Url{url + "/utilities/ls"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"path\": \"" + path + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        std::vector<const char*> keys;
        keys.push_back("file_name");
        keys.push_back("file_type");

        std::vector<std::map<std::string, std::string>> filesObj = jsonhandler::ParseObjs(jsonhandler::StringToJson(text), keys);
        // std::cout << "File Name: " << fileName << std::endl;

        std::string success = "false";
        for (int m = 0; m < filesObj.size(); m++) {
            // std::cout << "Looping: " << m << std::endl;
            // std::cout << "Object File Name: " << filesObj[m]["file_name"] << std::endl;
            if (filesObj[m]["file_name"] == fileName) {
                if (filesObj[m]["file_type"] == "file") {
                    return RemoveDirectory(path + fileName);
                } else {
                    std::cout << colors::RED() << "rm: cannot remove '" << path << "': Is a directory" << colors::RESET() << std::endl;
                    return "";
                }
                // std::cout << "Filename: " << fileName << " is a match.\n";
                // std::string str_text = GetPathByID(filesObj[m]["id"]);
                // const char* cstr_text = str_text.c_str();
                // filesObj[m].insert(std::pair<std::string, std::string>("contents", contents));
            }
        }

        std::cout << colors::RED() << "rm: cannot remove '" << path + fileName << "': No such file or directory" << colors::RESET() << std::endl;
        return success;
    }

    std::string Copy(std::string path1, std::string path2) {
        cpr::Response r = cpr::Post(
            cpr::Url{url + "/utilities/copy"},
            header,
            cpr::Body{"{\r\n    \"copy_path\": \"" + path1 + "\",\r\n    \"destination_directory\": \"" + path2 + "\",\r\n    \"session_id\": \"" + GetSessionID() + "\"\r\n}"}
        );
        
        const char* text = r.text.c_str();

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

    std::string Grep(std::string keyword, std::string fileName) {
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
        // std::cout << "File Name: " << fileName << std::endl;

        for (int m = 0; m < filesObj.size(); m++) {
            // std::cout << "Looping: " << m << std::endl;
            // std::cout << "Object File Name: " << filesObj[m]["file_name"] << std::endl;
            if (filesObj[m]["file_name"] == fileName) {
                // std::cout << "Filename: " << fileName << " is a match.\n";
                std::string str_text = GetPathByID(filesObj[m]["id"]);
                const char* cstr_text = str_text.c_str();
                std::string contents = jsonhandler::ExtractValue(jsonhandler::StringToJson(cstr_text), "contents");
                // filesObj[m].insert(std::pair<std::string, std::string>("contents", contents));
                return contents;
            }            
        }
    }

    std::string ChangeMode(std::string path, int permissions)
    {
        std::string perm_str = std::to_string(permissions);
        cpr::Response r = cpr::Patch(
            cpr::Url{url + "/path"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"permissions\": \"" + perm_str + "\",\r\n   \"path\": \"" + path + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl; 

        std::string success = text;

        return success;


    }

    std::string Sort(std::string file) {
        cpr::Response r = cpr::Get(
            cpr::Url{url + "/utilities/sort"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\",\r\n    \"path\": \"" + file + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        std::string contents = jsonhandler::UnpackArray(jsonhandler::StringToJson(text));
        // std::cout << "In Sort\n" << contents << std::endl;

        return "";
    }

    std::string Who() {
        cpr::Response r = cpr::Get(
            cpr::Url{url + "/utilities/whoami"},
            header,
            cpr::Body{"{\r\n    \"session_id\": \"" + GetSessionID() + "\"\r\n}"}
        );

        const char* text = r.text.c_str();

        // std::cout << text << std::endl;

        // std::vector<const char*> keys;
        // keys.push_back("username");

        std::string user = jsonhandler::ExtractValue(jsonhandler::StringToJson(text), "username");
        
        return user;
    }
}

