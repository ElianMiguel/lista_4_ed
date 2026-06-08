#include "Game.hpp"
#include "GamesDatabase.hpp"
#include "Trie.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    int k = std::stoi(argv[1]);
    std::string prefix = argv[2];

    Trie trie;

    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    std::vector<Game*> results = trie.autocomplete(prefix, k);

    for (Game* game : results) {
        std::cout << game->getTitle() << " | " << 
        "Popularity: " << game->getPopularity() << std::endl;
    }

    return 0;
}