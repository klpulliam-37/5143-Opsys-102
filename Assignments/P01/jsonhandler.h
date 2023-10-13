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
            // Add more cases for other error codes as needed
            default: return "Unknown parsing error.";
        }
    }

    Document StringToJson(const char* jsonStr) {
        // TODO: Need to use a try catch throw block to handle parsing errors.
        // Unknown parser error is currently occuring when trying to parse json reponse.
        Document jsonObj;
        ParseResult parseResult = jsonObj.Parse(jsonStr);

        // Check if parsing succeeded
        if (jsonObj.HasParseError()) {
            std::cerr << "Parse error: " << GetParseErrorString(parseResult.Code()) << std::endl;
            // return;
        }

        std::cout << "In StringToJson\n";

        const Value& session_id = jsonObj["session_id"];
        std::cout << "Set Value\n";
        std::cout << "Session ID: " << session_id.GetString() << std::endl;
        std::cout << "Printing Session ID\n";

        std::cout << "Out StringToJson\n";

        return jsonObj;
    }

    std::string JsonToString() {
        std::string parsedJson = "";

        return parsedJson;
    }

    void PrintSession(Document session) {
        std::cout << "In PrintSession\n";
        const Value& session_id = session["session_id"];
        std::cout << "Session ID: " << session_id.GetString() << std::endl;
        std::cout << "Out PrintSession\n";
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

