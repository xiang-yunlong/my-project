#include "retro_dungeon/game.hpp"
#include <iostream>
#include <string>
#include <conio.h>

int main(int argc, char* argv[]) {
    
    retro_dungeon::Game game;
    game.showTitleScreen();
    std::cin.get();
    if (!game.initialize()) {
        std::cerr << "Failed to initialize game" << std::endl;
        return 1;
    }
    
    std::cout << "Retro Dungeon v1.0.0" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter your name: ";
    
    std::string name;
    std::getline(std::cin, name);
    
    if (name.empty()) {
        name = "Adventurer";
    }
    
    game.newGame(name);
    while (game.getState() == retro_dungeon::GameState::Playing) {
        game.render();
        int c = _getch();
        
        if (c == 0xE0 || c == 0) {
            c = _getch();
        }
        
        switch(c) {
            case 'w': case 72: game.handleMovement(retro_dungeon::Direction::North); break;
            case 's': case 80: game.handleMovement(retro_dungeon::Direction::South); break;
            case 'a': case 75: game.handleMovement(retro_dungeon::Direction::West);  break;
            case 'd': case 77: game.handleMovement(retro_dungeon::Direction::East);  break;
            case 'q': game.shutdown(); return 0;
        }
        game.update();
    }
    
    game.render();
    std::cout << "\nGame Over\n";
    game.shutdown();
    return 0;
}