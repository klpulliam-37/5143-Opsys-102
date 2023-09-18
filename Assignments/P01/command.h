#include <vector>

using namespace std;

class Command
{
public:
    Command(string cmd) {name = cmd;}
    ~Command();

private:
    string name;
    vector<string> flags;

    // Need to change this to vector<string> later for multiple redirects.
    std::string redirects; 

public:
    string GetCmd() {return name;}
    vector<string> GetFlags() {return flags;}
    string GetRedirects() {return redirects;}

    // void SetCmd(string cmd) {name = cmd;}
    void SetFlags();
    void SetRedirects(string redir) {redirects = redir;}

};