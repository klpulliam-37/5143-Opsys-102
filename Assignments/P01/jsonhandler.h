#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"

using namespace rapidjson;

namespace jsonhandler {
    const char* GetParseErrorString(ParseErrorCode code);
    Document StringToJson(const char* jsonStr);
    std::string JsonToString();
    std::string ExtractValue(Document json, const char* key);
    std::string UnpackArray(Document json);
    std::vector<std::pair<std::string, std::string>> ParseList(Document list, const char* key);
    std::vector<std::map<std::string, std::string>> ParseObjs(Document json, std::vector<const char*> keys);
    void PrintObjs(std::vector<std::map<std::string, std::string>> objs);
    void ParseTest();
    void jsonexample();
}
