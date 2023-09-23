#pragma once
#include <vector>
#include <string>

class Helper
{
private:
    std::vector<std::string> static History;

public:
    Helper();
    std::string static GetDir();
    std::string static FormatDir(std::string path);
    void static UpdateHistory(std::string command);
    std::string static GetHistory();
};
