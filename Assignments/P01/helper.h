#pragma once
#include <vector>
#include <string>

class Helper
{
private:
    std::vector<std::string> static History;
    static bool HasRedirectO;
    static std::string Outfile;

public:
    Helper();
    std::string static GetDir();
    std::string static FormatDir(std::string path);
    void static UpdateHistory(std::string command);
    std::string static GetHistory();
    std::string static GetCommandAtHistoryIndex(int index);
    int static GetHistorySize();
    void static SetHasRedirectO(bool _hasRedirectO, std::string output);
    bool static GetHasRedirectO();
    std::string static GetOutfile();
    std::string static RemoveWhitespace(std::string _str);
};
