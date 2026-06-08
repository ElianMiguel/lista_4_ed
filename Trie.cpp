#include "Trie.hpp"
<<<<<<< HEAD
#include <string>
=======
>>>>>>> b6549ee (add ultima funcoes do tries e main)

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
<<<<<<< HEAD
=======
    if (this->root == nullptr) {
        this->root = new TrieNode();
    }

>>>>>>> b6549ee (add ultima funcoes do tries e main)
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

void Trie::search(TrieNode* node, std::vector<Game*>& results, int k) {
    if (results.size() >= k) return;
    if (node->isEndOfTitle) results.push_back(node->game);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            search(node->children[i], results, k);
        }
    }
}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {
    std::vector<Game*> results;

    if (this->root == nullptr) {
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

    search(current, results, k);
    sortResults(results);
    return results;
}

void Trie::merge(std::vector<Game*>& games, int low, int mid, int high) {
    std::vector<Game*> left(games.begin() + low, games.begin() + mid + 1);
    std::vector<Game*> right(games.begin() + mid + 1, games.begin() + high + 1);

    int i = 0;
    int j = 0;

    while(i < mid - low + 1 && j < high - mid) {
        if (left[i]->getPopularity() > right[j]->getPopularity()) {
            games[low + i + j] = left[i];
            i++;
        }
        else if (left[i]->getPopularity() == right[j]->getPopularity() && 
                 toSearchKey(left[i]->getTitle()) <= toSearchKey(right[j]->getTitle())) {
            games[low + i + j] = left[i];
            i++;
        }
        else {
            games[low + i + j] = right[j];
            j++;
        }
    }

    while (i < mid - low + 1) {
        games[low + i + j] = left[i];
        i++;
    }

    while (j < high - mid) {
        games[low + i + j] = right[j];
        j++;
    }
}

void Trie::mergeSort(std::vector<Game*>& games, int low, int high) {
    if (low >= high) return;

    int mid = low + (high - low) / 2;

    mergeSort(games, low, mid);
    mergeSort(games, mid + 1, high);

    merge(games, low, mid, high);
}

void Trie::sortResults(std::vector<Game*>& games) {
    if (games.empty()) return;

    mergeSort(games, 0, games.size() - 1);
}
