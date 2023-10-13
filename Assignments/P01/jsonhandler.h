#pragma once
#include <iostream>
#include <string>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"

using namespace rapidjson;

namespace jsonhandler {
    const char* GetParseErrorString(ParseErrorCode code) {
        switch (code) {
            case kParseErrorNone: return "No error.";
            case kParseErrorDocumentEmpty: return "The document is empty.";
            case kParseErrorDocumentRootNotSingular: return "The document root must not be followed by other values.";
            case kParseErrorValueInvalid: return "Invalid value.";

            case kParseErrorObjectMissName: return "Missing a name for object member.";
            case kParseErrorObjectMissColon: return "Missing a colon after a name of object member.";
            case kParseErrorObjectMissCommaOrCurlyBracket: return "Missing a comma or '}' after an object member.";

            case kParseErrorArrayMissCommaOrSquareBracket: return "Missing a comma or ']' after an array element.";

            case kParseErrorStringUnicodeEscapeInvalidHex: return "Incorrect hex digit after \\u escape in string.";
            case kParseErrorStringUnicodeSurrogateInvalid: return "The surrogate pair in string is invalid.";
            case kParseErrorStringEscapeInvalid: return "Invalid escape character in string.";
            case kParseErrorStringMissQuotationMark: return "Missing a closing quotation mark in string.";
            case kParseErrorStringInvalidEncoding: return "Invalid encoding in string.";

            case kParseErrorNumberTooBig: return "Number too big to be stored in double.";
            case kParseErrorNumberMissFraction: return "Miss fraction part in number.";
            case kParseErrorNumberMissExponent: return "Miss exponent in number.";

            case kParseErrorTermination: return "Parsing was terminated.";
            case kParseErrorUnspecificSyntaxError: return "Unspecific syntax error.";
            default: return "Unknown parsing error.";
        }
    }

    Document StringToJson(const char* jsonStr) {
        // TODO: Need to use a try catch throw block to handle parsing errors.
        Document jsonObj;
        ParseResult parseResult = jsonObj.Parse(jsonStr);

        // Check if parsing succeeded
        if (jsonObj.HasParseError()) {
            std::cerr << "Parse error: " << GetParseErrorString(parseResult.Code()) << std::endl;
            // return;
        }

        return jsonObj;
    }

    std::string JsonToString() {
        std::string parsedJson = "";

        return parsedJson;
    }

    std::string ExtractValue(Document json, const char* key) {
        const Value& value = json[key];
        return value.GetString();
    }

    // std::string ExtractSessionID(Document session) {
    //     const Value& session_id = session["session_id"];
    //     // std::cout << "Session ID: " << session_id.GetString() << std::endl;

    //     return session_id.GetString();
    // }

    // std::string ExtractUsername(Document session) {
    //     const Value& username = session["username"];

    //     return username.GetString();
    // }

    // std::string ExtractCWD(Document rBody) {
    //     const Value& cwd = rBody["cwd"];
    //     return cwd.GetString();
    // }

    void ParseTest() {
        const char* jsonStr = R"(
            {"active":true,"cwd_id":0,"groups":[2],"last_active":"Fri, 13 Oct 2023 09:15:52 GMT","session_id":"R8OBQLBHGNWOY6166LWZB3XHG3T0HU0J","success":true,"user_id":4,"username":"utest1"}
        )";

        Document jsonObj;
        ParseResult parseResult = jsonObj.Parse(jsonStr);

        if (parseResult.IsError()) {
            std::cerr << "Parse error: " << GetParseErrorString(parseResult.Code()) << std::endl;
            return;
        }

        // Accessing values from the parsed JSON
        bool active = jsonObj["active"].GetBool();
        int cwd_id = jsonObj["cwd_id"].GetInt();
        const Value& groups = jsonObj["groups"];
        const char* last_active = jsonObj["last_active"].GetString();
        const char* session_id = jsonObj["session_id"].GetString();
        bool success = jsonObj["success"].GetBool();
        int user_id = jsonObj["user_id"].GetInt();
        const char* username = jsonObj["username"].GetString();

        std::cout << "Parsed JSON values:" << std::endl;
        std::cout << "Active: " << active << std::endl;
        std::cout << "cwd_id: " << cwd_id << std::endl;
        std::cout << "Groups: " << groups[0].GetInt() << std::endl;
        std::cout << "Last Active: " << last_active << std::endl;
        std::cout << "Session ID: " << session_id << std::endl;
        std::cout << "Success: " << success << std::endl;
        std::cout << "User ID: " << user_id << std::endl;
        std::cout << "Username: " << username << std::endl;
    }

    void jsonexample() {
        // Example JSON string
        const char* json = R"(
            {
                "name": "John Doe",
                "age": 30,
                "city": "New York"
            }
        )";

        // Parse the JSON string
        Document document;
        ParseResult parseResult = document.Parse(json);

        // Check if parsing succeeded
        if (document.HasParseError()) {
            std::cerr << "Parse error: " << GetParseErrorString(parseResult.Code()) << std::endl;
            return;
        }

        // Accessing values from the parsed JSON
        const Value& name = document["name"];
        const Value& age = document["age"];
        const Value& city = document["city"];

        std::cout << "Name: " << name.GetString() << std::endl;
        std::cout << "Age: " << age.GetInt() << std::endl;
        std::cout << "City: " << city.GetString() << std::endl;

        // Create a new JSON object
        Document newDocument;
        newDocument.SetObject();
        Value author("Jane Smith");
        Value year(1985);

        newDocument.AddMember("author", author, newDocument.GetAllocator());
        newDocument.AddMember("year", year, newDocument.GetAllocator());

        // Convert the new JSON object to a string
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        newDocument.Accept(writer);

        std::cout << "New JSON object:\n" << buffer.GetString() << std::endl;
    }
}

