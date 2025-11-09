#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;

void listFiles(const fs::path& p) {
    for (auto &f : fs::directory_iterator(p))
        cout << (fs::is_directory(f) ? "[DIR]  " : "       ")
             << f.path().filename().string() << "\n";
}

void searchFile(const fs::path& root, const string& name) {
    bool found = false;
    for (auto &p : fs::recursive_directory_iterator(root)) {
        if (p.path().filename() == name) {
            cout << "Found: " << p.path() << "\n";
            found = true;
        }
    }
    if (!found) cout << "No file named '" << name << "' found.\n";
}

int main() {
    fs::path cwd = fs::current_path();
    string cmd, a;

    cout << "File Explorer (Day 4)\n";
    cout << "Commands: ls, cd <dir>, mkdir <dir>, search <name>, exit\n\n";

    while (true) {
        cout << cwd << " $ ";
        getline(cin, cmd);

        if (cmd == "ls") listFiles(cwd);
        else if (cmd.rfind("cd",0)==0) {
            a = cmd.size()>3 ? cmd.substr(3) : "";
            fs::path newPath = (a=="..") ? cwd.parent_path() : cwd/a;
            if (fs::exists(newPath)&&fs::is_directory(newPath))
                cwd = fs::canonical(newPath);
            else cout << "cd: " << a << ": No such directory\n";
        }
        else if (cmd.rfind("mkdir",0)==0) {
            a = cmd.size()>6 ? cmd.substr(6) : "";
            if (a.empty()) cout << "mkdir: missing directory name\n";
            else if (fs::exists(cwd/a)) cout << "mkdir: directory already exists\n";
            else fs::create_directory(cwd/a);
        }
        else if (cmd.rfind("search",0)==0) {
            a = cmd.size()>7 ? cmd.substr(7) : "";
            if (a.empty()) cout << "search: missing file name\n";
            else searchFile(cwd,a);
        }
        else if (cmd=="exit") break;
        else if (!cmd.empty()) cout << "Unknown command: " << cmd << "\n";
    }
}
