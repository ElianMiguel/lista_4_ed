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
    if (this->root == nullptr) {
        this->root = new TrieNode();
    }

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
    if (this->root == nullptr) return false;

    std::string normalized = toSearchKey(title);
    TrieNode* current = this->root;

    for (char c : normalized) {
        int index = getIndex(c);
        
        if (current->children[index] == nullptr) {
            return false;
        }

        current = current->children[index];
    }

    return current->isEndOfTitle;
}

void Trie::search(TrieNode* node, std::vector<Game*>& results) {
    if (node->isEndOfTitle) results.push_back(node->game);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            search(node->children[i], results);
        }
    }
}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {
    std::vector<Game*> results;

    if (this->root == nullptr || k <= 0) {
        return results; 
    }

    std::string normalized = toSearchKey(prefix);
    TrieNode* current = this->root;

    for (char c : normalized) {
        int index = getIndex(c);

        if (current->children[index] == nullptr) {
            return results;
        }

        current = current->children[index];
    }

    search(current, results);
    sortResults(results);

    if (results.size() > k) {
        results.resize(k);
    }

    return results;
}

void Trie::sortResults(std::vector<Game*>& games) {
    // Usando insertion sort
    for (int i = 1; i < games.size(); i++) {
        Game* key = games[i];
        int j = i - 1;
        std::string keyTitle = toSearchKey(key->getTitle());

        while (j >= 0 && (key->getPopularity() > games[j]->getPopularity() ||
                            (key->getPopularity() == games[j]->getPopularity() &&
                             keyTitle < toSearchKey(games[j]->getTitle())))) {
            games[j + 1] = games[j];
            j--;
        }

        games[j + 1] = key;
    }
}
