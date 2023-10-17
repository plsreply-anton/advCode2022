#include <iostream>
#include <fstream>
#include <vector>
#include <cstring> 

bool findDuplicate(std::vector<char> &vector)
{   
    for (int i = 0; i < vector.size(); ++i) {
        for (int j = i + 1; j < vector.size(); ++j) {
            if (vector[i] == vector[j]) {
                //std::cout << vector[i] << std::endl;
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    //Change Part here
    int part = 2;
    std::ifstream file ("test.txt");
    std::string string;

    if ( file.is_open() ) { 
        file >> string; 
    }

    std::vector<char> lastFour;
    lastFour.push_back(string[3]);
    lastFour.push_back(string[2]);
    lastFour.push_back(string[1]);
    lastFour.push_back(string[0]);

    for (int i = 4; i < string.size(); i++)
    {
        char c = string[i];
        if (findDuplicate(lastFour))
        {
            lastFour.insert(lastFour.begin(), c);
            if (part == 1)
            {
                lastFour.pop_back();
            } else if (part == 2) {
                if (lastFour.size() > 14)
                {
                    lastFour.pop_back();
                }  
            }
        } else
        {
            std::cout << i << std::endl;
            break;
        }
    }
    return 0;
}
