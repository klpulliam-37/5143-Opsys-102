#include <iostream>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"

using namespace rapidjson;

int main() {
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
    document.Parse(json);

    // // Check if parsing succeeded
    // if (document.HasParseError()) {
    //     std::cerr << "Parse error: " << GetParseError_En(document.GetParseError()) << std::endl;
    //     return 1;
    // }

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

    return 0;
}
