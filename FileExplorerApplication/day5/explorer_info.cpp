#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;
namespace fs = std::filesystem;

void listFiles(const fs::path& p) {
    for (auto &f : fs::directory_iterator(p))
        cout << (fs::is_directory(f) ? "[DIR]  " : "       ")
             << f.path().filename().string() << "\n";
}

void showInfo(const fs::path& file) {
    if (!fs::exists(file)) {
        cout << "info: file not found\n";
        return;
    }
    auto ftime = fs::last_write_time(file);
    auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + chrono::system_clock::now());
    time_t cftime = chrono::system_clock::to_time_t(sctp);

    cout << "File: " << file.filename() << "\n";
    cout << "Path: " << fs::absolute(file) << "\n";
    cout << "Size: " << fs::file_size(file) << " bytes\n";
    cout << "Last Modified: " << put_time(localtime(&cftime), "%Y-%m-%d %H:%M:%S") << "\n";

    fs::perms p = fs::status(file).permissions();
    cout << "Permissions: "
         << ((p & fs::perms::owner_read)  != fs::perms::none ? "r" : "-")
         << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
         << ((p & fs::perms::owner_exec)  != fs::perms::none ? "x" : "-")
         << ((p & fs::perms::group_read)  != fs::perms::none ? "r" : "-")
         << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
         << ((p & fs::perms::group_exec)  != fs::perms::none ? "x" : "-")
         << ((p & fs::perms::others_read)  != fs::perms::none ? "r" : "-")
         << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
         << ((p & fs::perms::others_exec)  != fs::perms::none ? "x" : "-")
         << "\n";
}

void changePerms(const fs::path& file, const string& mode) {
    if (!fs::exists(file)) {
        cout << "chmod: file not found\n";
        return;
    }
    fs::perms p = fs::perms::none;
    for (char c : mode) {
        if (c == 'r') p |= fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read;
        if (c == 'w') p |= fs::perms::owner_write | fs::perms::group_write | fs::perms::others_write;
        if (c == 'x') p |= fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec;
    }
    fs::permissions(file, p);
    cout << "Permissions updated for " << file << "\n";
}

int main() {
    fs::path cwd = fs::current_path();
    string cmd, a, b;

    cout << "File Explorer (Day 5)\n";
    cout << "Commands: ls, cd <dir>, mkdir <dir>, touch <file>, info <file>, chmod <file> <rwx>, exit\n\n";

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
            else if (fs::exists(cwd/a)) cout << "mkdir: already exists\n";
            else fs::create_directory(cwd/a);
        }
        else if (cmd.rfind("touch",0)==0) {
            a = cmd.size()>6 ? cmd.substr(6) : "";
            if (a.empty()) cout << "touch: missing file name\n";
            else ofstream(cwd/a).close();
        }
        else if (cmd.rfind("info",0)==0) {
            a = cmd.size()>5 ? cmd.substr(5) : "";
            if (a.empty()) cout << "info: missing file name\n";
            else showInfo(cwd/a);
        }
        else if (cmd.rfind("chmod",0)==0) {
            istringstream iss(cmd);
            string s; iss >> s >> a >> b;
            if (a.empty()||b.empty()) cout << "Usage: chmod <file> <rwx>\n";
            else changePerms(cwd/a,b);
        }
        else if (cmd=="exit") break;
        else if (!cmd.empty()) cout << "Unknown command: " << cmd << "\n";
    }
}
