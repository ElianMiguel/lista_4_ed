#ifndef TRIE_HPP
#define TRIE_HPP

const int ALPHABET_SIZE = 36;

#include <string>
#include <vector>
#include "Game.hpp"

class TrieNode {

public:

    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfTitle;
    Game* game;

    TrieNode();
    ~TrieNode();
};

class Trie {

private:

    TrieNode* root;

public:

    Trie();
    ~Trie();

    bool insert(Game* game);
    bool contains(std::string title);

    std::vector<Game*> autocomplete(std::string prefix, int k);

    std::string toSearchKey(std::string text);
    void sortResults(std::vector<Game*>& games);

    // Outros métodos auxiiares, se necessário

    int getIndex(char c);
};

#endif