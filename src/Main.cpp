#include <iostream>
#include <fstream>
#include <sstream>
#include "trie.h"

void insertfunction(std::string s, std::string output);
void searchfunction(std::string s, std::string output);
void deletefunction(std::string s, std::string output);

trie root = new trie(true);

int main(int argc, const char * argv[]) {
    std::string output = argv[2];
    std::string str;
    std::vector<std::string> inputInfo;

    //reading input
    std::ifstream in1(argv[1]);
    while (std::getline(in1, str))
    {
        if(!str.empty()) {
            inputInfo.push_back(str);
        }
    }
    in1.close();

    //clearing output file
    std::ofstream ofs;
    ofs.open(argv[2], std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    for (int i = 0; i < inputInfo.size(); ++i) {
        if (inputInfo.at(i).rfind("i", 0) == 0){
            insertfunction(inputInfo.at(i), output);
        }else if (inputInfo.at(i).rfind("s", 0) == 0){
            searchfunction(inputInfo.at(i), output);
        }else if (inputInfo.at(i).rfind("d", 0) == 0){
            deletefunction(inputInfo.at(i), output);
        }else if (inputInfo.at(i).rfind("l", 0) == 0){
            root.list(0,"", output);
        }
    }

}

void insertfunction(std::string s, std::string output){
    s = s.erase(0, 7);
    s = s.erase(s.size()-1);

    std::vector<std::string> tokens;
    std::string intermediate;

    std::stringstream check1(s);

    while(getline(check1, intermediate, ','))
    {
        tokens.push_back(intermediate);
    }

    root.insert(tokens.at(0), tokens.at(1),tokens.at(0), output);
}

void searchfunction(std::string s, std::string output){
    s = s.erase(0, 7);
    s = s.erase(s.size()-1);
    root.search(s,output);
}

void deletefunction(std::string s, std::string output){
    s = s.erase(0, 7);
    s = s.erase(s.size()-1);
    root.deleteCheck(s, s, output);
    for (int i = 0; i < s.size(); ++i) {
        s = s.erase(s.size()-1);
        root.delete1(s, output);
    }

}