#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> 

using namespace std;

struct Directory {
    Directory *parent = nullptr;
    std::unordered_map<std::string, Directory*> subdirs;
    std::unordered_map<std::string, size_t> files;
    size_t calcSize();
    void listDirectoriesAndSizes(std::unordered_map<std::string, size_t>& directorySizes);

};

struct Filesystem {
    Directory root;
    std::vector<std::unique_ptr<Directory>> storage;
    Directory* cd(string command, Directory *currentDir);
    int ls(vector<string> commands, int i, Directory &currentDir);
};

vector<string> splitSizeAndName(string s) {
    vector<string> v;
    int start, end;
    start = end = 0;
 
    // defining the delimitation character
    char dl = ' ';
 
    while ((start = s.find_first_not_of(dl, end))
           != string::npos) {
        end = s.find(dl, start);
        v.push_back(s.substr(start, end - start));
    }

    return v;
}

Directory* Filesystem::cd(string command, Directory *currentDir){
    if (command.find("/") != string::npos) return &root;
    if (command.find("..") != string::npos) return currentDir->parent;
    

    // Directory already exists.
    if (currentDir->subdirs[command] != nullptr)
        return currentDir->subdirs[command];

    auto &sub_dir = storage.emplace_back(
        std::make_unique<Directory>());
        sub_dir->parent = currentDir;
        currentDir->subdirs[command] = sub_dir.get();
        return currentDir->subdirs[command];

}

int Filesystem::ls(vector<string> commands, int i, Directory &currentDir){
    bool newCommand = false;
    i += 1;
    while (i < commands.size()){

        //Check if we reach a new command
        if (commands[i].find("$") != string::npos)
        {
            //cout << "Nytt kommando" << endl;
            return i;
        }
        //If line implies a file
        if (any_of(commands[i].begin(), commands[i].end(), ::isdigit)) {
            
            size_t file_size = stoi(splitSizeAndName(commands[i])[0]);
            string filename = splitSizeAndName(commands[i])[1];
            //cout << filename << " " << file_size << endl;
            currentDir.files[filename] = file_size;
        }
        i += 1;
    }
    return i;
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

size_t Directory::calcSize()
{
    size_t totalSize = 0;

    // Add the size of files in this directory
    for (const auto& file : files) {
        totalSize += file.second;
    }

    // Recursively calculate the size of subdirectories
    for (const auto& subdir : subdirs) {
        totalSize += subdir.second->calcSize();
    }

    return totalSize;
}

void Directory::listDirectoriesAndSizes(std::unordered_map<std::string, size_t>& directorySizes) {

        for (const auto& subdir : subdirs) {
            size_t subdirSize = subdir.second->calcSize();
            directorySizes[subdir.first] = subdirSize;
            subdir.second->listDirectoriesAndSizes(directorySizes);
        }
}

int sort(std::unordered_map<std::string, size_t>& directorySizes) {

    int total = 0;
        for (const auto& dir : directorySizes) {
            if (dir.second < 100000)
            {
                total += dir.second;
            }
        }
    return total;
}

int main(int argc, char const *argv[])
{
    vector<string> commands;
    string filename = "day7Input.txt";
    readAndAppend(filename, commands);
    
    auto filesystem = std::make_unique<Filesystem>();
    Directory *current = &filesystem->root;
    current->parent = current;

    int i = 0;
    while (i < commands.size())
    {
        if (commands[i].find("$") != string::npos)
        {
            if (commands[i].find("cd") != string::npos)
            {
                string command = commands[i].substr(commands[i].find("cd")+3);
                current = filesystem->cd(command, current);
            }

            if (commands[i].find("ls") != string::npos){
                i = filesystem->ls(commands, i, *current);
                continue;
            }

        }
        i += 1;
    }
    current = &filesystem->root;

    std::unordered_map<std::string, size_t> directorySizes;
    std::unordered_map<std::string, size_t> sortedDirs;
    current->listDirectoriesAndSizes(directorySizes);
    size_t currentSize = current->calcSize();
    directorySizes["root"] = currentSize;

    // Display the list of directories and their sizes
    cout << "Directory Sizes:" << endl;
    for (const auto& pair : directorySizes) {
        cout << pair.first << ": " << pair.second << " bytes" << endl;
    }

    int total = sort(directorySizes);
    cout << endl;
    cout << "Total size for smaller directories: "  << total << " bytes" << endl;

    return 0;
}
