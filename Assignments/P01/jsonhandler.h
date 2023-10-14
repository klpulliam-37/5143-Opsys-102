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
    // std::string ExtractSessionID(Document session);
    // std::string ExtractUsername(Document session);
    // std::string ExtractCWD(Document rBody);
    void ParseTest();
    void jsonexample();
}
