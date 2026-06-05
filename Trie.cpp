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
    char* ptr = text.data();
    while (*ptr != '\0') {
        if (int(*ptr) == 32) {
            ptr++;
        }
        if (int(*ptr) >= 65 && int(*ptr) <= 90) {
            *ptr += 32;
        }
    }

    std::string new_text = ptr;
    return new_text;
}

bool Trie::insert(Game* game) {
    TrieNode* current = this->root;
    std::string title = toSearchKey(game->getTitle());
    for (char c : title) {
        if (current->children == nullptr) {
            TrieNode* node = new TrieNode();
            if (int(c) >= 48 && int(c) <= 57) {
                current->children[25 + c - '0'];
            }
            current->children[c - 'a'] = node;
        }

        if (int(c) >= 48 && int(c) <= 57) {
            current = current->children[25 + c - '0'];
        }
        current = current->children[c - 'a'];
    }

    current->isEndOfTitle = true;
    current->game = game;
    return true;
}

bool Trie::contains(std::string title) {

}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {}

void Trie::sortResults(std::vector<Game*>& games) {}