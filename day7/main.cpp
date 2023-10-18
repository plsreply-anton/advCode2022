#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> 
using namespace std;

struct Directory {
    string name;
    Directory *parent = nullptr;
    std::unordered_map<std::string, Directory*> subdirs;
    std::unordered_map<std::string, size_t> files;
};

struct Filesystem {
    Directory root;
    std::vector<std::unique_ptr<Directory>> storage;
    Directory* cd(string command, Directory *currentDir);
};

Directory* Filesystem::cd(string command, Directory *currentDir){
    if (command.find("/") != string::npos) return &root;
    if (command.find("..") != string::npos) return currentDir->parent;

    // Directory already exists.
    if (currentDir->subdirs[command.substr(command.find("cd"))] != nullptr)
        return currentDir->subdirs[command.substr(command.find("cd"))];

    auto &sub_dir = storage.emplace_back(
        std::make_unique<Directory>());
        sub_dir->parent = currentDir;
        currentDir->subdirs[command.substr(command.find("cd"))] = sub_dir.get();
        return currentDir->subdirs[command.substr(command.find("cd"))];


}

void readAndAppend(string filename,  vector<string> &commands)
{
    ifstream file (filename);

    if ( file.is_open() ) { 
        string line;
        while (getline(file, line))
            commands.emplace_back(line);
    }
}








int main(int argc, char const *argv[])
{
    vector<string> commands;
    string filename = "test.txt";
    readAndAppend(filename, commands);

    auto filesystem = std::make_unique<Filesystem>();
    Directory *current = &filesystem->root;
    current->parent = current;

    for (int i = 1; i < commands.size(); i++)
    {
        if (commands[i].find("cd") != string::npos)
        {
            string command = commands[i].substr(commands[i].find("cd"));
            filesystem->cd(command, current);
        }
        
    }
    

    
    

    

    return 0;
}
