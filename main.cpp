#include "Game.hpp"
#include "GamesDatabase.hpp"
#include "Trie.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./app k prefix" << std::endl;
        return -1;
    }

    int k = std::stoi(argv[1]);
    std::string prefix = argv[2];
    Trie trie;

    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    std::vector<Game*> results = trie.autocomplete(prefix, k);

    if (results.size() == 0) {
        std::cout << "No results found" << std::endl;
        return -1;
    }

    for (Game* game : results) {
        std::cout << "[ " << game->getTitle() << " | " << game->getShortDescription() << " | "
        << game->getPopularity() << " ]" << std::endl;
        std::cout << std::endl;
    }

    return 0;
}