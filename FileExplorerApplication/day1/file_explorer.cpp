#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void listFiles(const fs::path& path) {
    std::cout << "\nContents of: " << path << "\n";
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_directory(entry))
                std::cout << "[DIR]  ";
            else
                std::cout << "       ";
            std::cout << entry.path().filename().string() << "\n";
        }
    } catch (fs::filesystem_error &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    fs::path currentPath = fs::current_path();
    std::cout << "Simple File Explorer (Day 1)\n";
    std::cout << "Current Directory: " << currentPath << "\n";

    listFiles(currentPath);
    return 0;
}
