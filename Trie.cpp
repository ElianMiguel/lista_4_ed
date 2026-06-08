#include "Trie.hpp"
#include <string>

// Funções da classe TrieNode

TrieNode::TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        this->children[i] = nullptr;
    }

    this->isEndOfTitle = false;
    this->game = nullptr;
}

TrieNode::~TrieNode() {}

// Funções da classe Trie

Trie::Trie() {
    this->root = nullptr;
}

Trie::~Trie() {}

std::string Trie::toSearchKey(std::string text) {
    char* readPtr = text.data();
    char* writePtr = text.data();
    while (*readPtr != '\0') {
        if (*readPtr == 32) {
            readPtr++;
        }
        if (*readPtr >= 65 && *readPtr <= 90) {
            *writePtr = *readPtr + 32;
        } else {
            *writePtr = *readPtr;
        }

        readPtr++;
        writePtr++;
    }

    text.resize(writePtr - text.data());
    return text;
}

int Trie::getIndex(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    if (c >= '0' && c <= '9') {
        return 26 + (c - '0');
    }
    return -1;
}

bool Trie::insert(Game* game) {
    TrieNode* current = this->root;
    std::string title = toSearchKey(game->getTitle());

    for (char c : title) {
        int index = getIndex(c);

        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode(); 
        }

        current = current->children[index];
    }

    current->isEndOfTitle = true;
    current->game = game;
    return true;
}

bool Trie::contains(std::string title) {
    std::string normalized = toSearchKey(title);
    TrieNode* current = this->root;

    for (char c : title) {
        int index = getIndex(c);
        
        if (current->children[index] == nullptr) {
            return false;
        }

        current = current->children[index];
    }

    return current->isEndOfTitle;
}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {}

void Trie::sortResults(std::vector<Game*>& games) {}