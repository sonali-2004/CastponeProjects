#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;

int main() {
    fs::path cwd = fs::current_path();
    string cmd, a, b;

    cout << "File Explorer (Day 3)\n";
    cout << "Commands: ls, cd <dir>, touch <file>, rm <file>, cp <src> <dst>, mv <src> <dst>, exit\n\n";

    while (true) {
        cout << cwd << " $ ";
        getline(cin, cmd);

        if (cmd == "ls") {
            for (auto &p : fs::directory_iterator(cwd))
                cout << (fs::is_directory(p) ? "[DIR]  " : "       ")
                     << p.path().filename().string() << "\n";
        }
        else if (cmd.rfind("cd",0)==0) {
            a = cmd.size()>3 ? cmd.substr(3) : "";
            fs::path newPath = (a=="..") ? cwd.parent_path() : cwd/a;
            if (fs::exists(newPath) && fs::is_directory(newPath))
                cwd = fs::canonical(newPath);
            else cout<<"cd: "<<a<<": No such directory\n";
        }
        else if (cmd.rfind("touch",0)==0) {
            a = cmd.size()>6 ? cmd.substr(6) : "";
            if (a.empty()) cout<<"touch: missing file\n";
            else ofstream(cwd/a).close();
        }
        else if (cmd.rfind("rm",0)==0) {
            a = cmd.size()>3 ? cmd.substr(3) : "";
            if (fs::exists(cwd/a)) fs::remove_all(cwd/a);
            else cout<<"rm: file not found\n";
        }
        else if (cmd.rfind("cp",0)==0) {
            istringstream iss(cmd); string s; iss>>s>>a>>b;
            if(fs::exists(cwd/a))
                fs::copy(cwd/a,cwd/b,fs::copy_options::overwrite_existing);
            else cout<<"cp: source not found\n";
        }
        else if (cmd.rfind("mv",0)==0) {
            istringstream iss(cmd); string s; iss>>s>>a>>b;
            if(fs::exists(cwd/a))
                fs::rename(cwd/a,cwd/b);
            else cout<<"mv: source not found\n";
        }
        else if (cmd=="exit") break;
        else if (!cmd.empty()) cout<<"Unknown command: "<<cmd<<"\n";
    }
}
