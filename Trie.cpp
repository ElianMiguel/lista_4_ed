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

bool Trie::insert(Game* game) {}

bool Trie::contains(std::string title) {}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {}

std::string Trie::toSearchKey(std::string text) {}

void Trie::sortResults(std::vector<Game*>& games) {}