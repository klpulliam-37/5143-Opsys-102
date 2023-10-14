#pragma once
#include <iostream>
#include <string>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"

using namespace rapidjson;

namespace jsonhandler {
    const char* GetParseErrorString(ParseErrorCode code);
    Document StringToJson(const char* jsonStr);
    std::string JsonToString();
    std::string ExtractValue(Document json, const char* key);
    std::vector<std::pair<std::string, std::string>> ParseList(Document json, const char* key);
    
    void ParseTest();
    void jsonexample();
}
