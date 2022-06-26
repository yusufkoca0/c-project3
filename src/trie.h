#ifndef UNTITLED2_TRIE_H
#define UNTITLED2_TRIE_H
#include <iostream>
#include <vector>


class trie {
    bool root;
    char letter;
    bool endofWord;
    std::string englishEquivalent;
    std::vector<trie> branches;
public:
    trie();

    trie(bool root);

    trie(bool root, char letter, bool endofWord);

    trie(bool root, char letter, bool endofWord, const std::string &englishEquivalent);

    bool isRoot() const;

    void setRoot(bool root);

    char getLetter() const;

    void setLetter(char letter);

    bool isEndofWord() const;

    void setEndofWord(bool endofWord);

    const std::string &getEnglishEquivalent() const;

    void setEnglishEquivalent(const std::string &englishEquivalent);

    const std::vector<trie> &getBranches() const;

    void setBranches(const std::vector<trie> &branches);

    void insert(std::string key, std::string value, std::string fullkey, std::string output);

    void search(std::string word, std::string output);

    void deleteCheck(std::string word, std::string fullword, std::string output);

    void delete1(std::string word, std::string output);

    void list (int x, std::string s, std::string output);

    void print(std::string s, std::string output);
};


#endif //UNTITLED2_TRIE_H
