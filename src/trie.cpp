#include <algorithm>
#include <fstream>
#include "trie.h"

class sort;

trie::trie() {}

trie::trie(bool root) : root(root) {}

trie::trie(bool root, char letter, bool endofWord) : root(root), letter(letter), endofWord(endofWord) {}

trie::trie(bool root, char letter, bool endofWord, const std::string &englishEquivalent) : root(root),
                                                                                           letter(letter),
                                                                                           endofWord(
                                                                                                                 endofWord),
                                                                                           englishEquivalent(
                                                                                                                 englishEquivalent) {}

bool trie::isRoot() const {
    return root;
}

void trie::setRoot(bool root) {
    trie::root = root;
}

char trie::getLetter() const {
    return letter;
}

void trie::setLetter(char letter) {
    trie::letter = letter;
}

bool trie::isEndofWord() const {
    return endofWord;
}

void trie::setEndofWord(bool endofWord) {
    trie::endofWord = endofWord;
}

const std::string &trie::getEnglishEquivalent() const {
    return englishEquivalent;
}

void trie::setEnglishEquivalent(const std::string &englishEquivalent) {
    trie::englishEquivalent = englishEquivalent;
}

const std::vector<trie> &trie::getBranches() const {
    return branches;
}

void trie::setBranches(const std::vector<trie> &branches) {
    trie::branches = branches;
}

void trie::insert(std::string key, std::string value, std::string fullkey, std::string output) {
    bool x = 0;
    for (int i = 0; i < branches.size(); ++i) {
        if (branches.at(i).letter == key[0]){
            if (key.size() > 1){
                branches.at(i).insert(key.erase(0,1), value, fullkey, output);
            } else{
                branches.at(i).endofWord = 1;
                if (branches.at(i).englishEquivalent == "") {
                    std::string o = '"' + fullkey + '"' + " was added\n";
                    print(o,output);
                    branches.at(i).englishEquivalent = value;
                    return;
                } else {
                    if (branches.at(i).englishEquivalent == value) {
                        std::string o = '"' + fullkey + '"';
                        print(o + " already exist\n", output);
                        return;
                    } else{
                        std::string o = '"' + fullkey + '"';
                        print(o + " was updated\n", output);
                        branches.at(i).englishEquivalent = value;
                        return;
                    }
                }
            }
            x = 1;
            return;
        }
    }
    if (!x){
        if (key.size() > 1){
            branches.push_back(trie(0, key[0], 0));
            branches.at(branches.size()-1).insert(key.erase(0,1), value,fullkey, output);
        }else{
            std::string o = '"' + fullkey + '"' + " was added\n";
            print(o,output);
            branches.push_back(trie(0, key[0], 1, value));
            return;
        }
    }

}

void trie::search(std::string word, std::string output) {
    for (int i = 0; i < branches.size(); ++i) {
        if (branches.at(i).letter == word[0]){
            if (word.size() > 1){
                branches.at(i).search(word.erase(0,1), output);
                return;
            } else {
                if (branches.at(i).endofWord){
                    if (branches.at(i).englishEquivalent != "") {
                        std::string o = "The English equivalent is " + branches.at(i).englishEquivalent + '"' + "\n";
                        print('"' + o,output);
                        return;
                    } else{
                        std::string o = "not enough Dothraki word";
                        print('"' + o + '"' +'\n', output);
                        return;
                    }
                } else{
                    std::string o = "not enough Dothraki word";
                    print('"' + o + '"' +'\n', output);
                    return;
                }
            }
        }
    }
    if (root){
        std::string o = "no record";
        print('"' + o + '"' +'\n', output);
        return;
    } else{
        std::string  o = "incorrect Dothraki word";
        print('"' + o + '"' +'\n', output);
        return;
    }
}

void trie::deleteCheck(std::string word, std::string fullword, std::string output) {
    bool x = 0;
    for (int i = 0; i < branches.size(); ++i) {
        if (branches.at(i).letter == word[0]){
            x = 1;
            if (word.size() > 1){
                branches.at(i).deleteCheck(word.erase(0,1), fullword, output);
                return;
            } else {
                if (branches.at(i).endofWord){
                    if (branches.at(i).englishEquivalent != "") {
                        if (branches.at(i).branches.size() == 0) {
                            std::vector<trie>::iterator it;
                            it = branches.begin() + i;
                            branches.erase(it);
                        } else{
                            branches.at(i).englishEquivalent = "";
                            branches.at(i).endofWord = 0;
                        }
                        std::string o = '"' + fullword + '"' + " deletion is successful\n";
                        print(o,output);
                        return;
                    } else{
                        std::string o = "not enough Dothraki word";
                        print('"' + o + '"' +'\n',output);
                        return;
                    }
                } else{
                    std::string o = "not enough Dothraki word";
                    print('"' + o + '"' +'\n',output);
                    return;
                }
            }
        }
    }
    if(!x) {
        if (root) {
            std::string o = "no record";
            print('"' + o + '"' +'\n',output);
            return;
        } else {
            std::string o = "incorrect Dothraki word";
            print('"' + o + '"' +'\n',output);
            return;
        }
    }
}

void trie::delete1(std::string word, std::string output){
    for (int i = 0; i < branches.size(); ++i) {
        if (branches.at(i).letter == word[0]){
            if (word.size() > 1){
                branches.at(i).delete1(word.erase(0,1), output);
                return;
            } else {
                if (branches.at(i).endofWord == 1){
                    return;
                } else{
                    if (branches.at(i).branches.size() == 0) {
                        std::vector<trie>::iterator it;
                        it = branches.begin() + i;
                        branches.erase(it);
                        return;
                    } else{
                        return;
                    }
                }
            }
        }
    }
}

void trie::list(int x, std::string s, std::string output) {
    if (branches.size() > 1){

        std::sort(branches.begin(), branches.end(), [ ](const  trie& lhs, const trie& rhs){
            return lhs.letter < rhs.letter;
        });


        if(!root) {
            if (!endofWord) {
                for (int i = 0; i < x; ++i) {
                    std::string o = "\t";
                    print(o, output);
                }
                std::string o = "-" + s + "\n";
                print(o, output);
            }
            for (int i = 0; i < branches.size(); ++i) {
                if (branches.at(i).endofWord) {
                    for (int j = 0; j < x + 1; ++j) {
                        std::string o = "\t";
                        print(o,output);
                    }
                    std::string o = "-" + s + branches.at(i).letter + "(" + branches.at(i).englishEquivalent + ")\n";
                    print(o,output);
                    if (branches.at(i).branches.size() != 0) {
                        branches.at(i).list(x + 2, s + branches.at(i).letter, output);
                    }
                } else {
                    branches.at(i).list(x + 1, s + branches.at(i).letter, output);
                }
            }
        }else{
            for (int i = 0; i < branches.size(); ++i) {
                if (branches.at(i).endofWord) {
                    if (!endofWord) {
                        for (int j = 0; j < x + 1; ++j) {
                            std::string o = "\t";
                            print(o, output);
                        }
                        std::string o = s + branches.at(i).letter + "(" + branches.at(i).englishEquivalent + ")\n";
                        print(o, output);
                    }
                    if (branches.at(i).branches.size() != 0) {
                        branches.at(i).list(x + 1, s + branches.at(i).letter, output);
                    }
                } else {
                    branches.at(i).list(x, s + branches.at(i).letter, output);
                }
            }
        }

    }
    else if (branches.size() == 1){
        if (branches.at(0).endofWord){
            for (int j = 0; j < x; ++j) {
                std::string o = "\t";
                print(o,output);
            }
            std::string o = "-" + s+branches.at(0).letter + "(" + branches.at(0).englishEquivalent + ")\n";
            print(o,output);
            if (branches.at(0).branches.size() != 0){
                branches.at(0).list(x, s + branches.at(0).letter, output);
            }
        } else {
            branches.at(0).list(x, s + branches.at(0).letter, output);
        }
    }
}

void trie::print(std::string s, std::string output) {
    std::ofstream ofs;
    ofs.open(output, std::fstream::app);
    ofs << s;
    ofs.close();
}
