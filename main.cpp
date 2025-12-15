#include <iostream>
#include "GameInfo.h"

void main()
{
    std::srand(std::time(nullptr)); 

    GameInfo game(4, 6); 


    std::cout << "Secret (debug):";
    game.printSecret();
    std::cout << "\n";

    int turn = 0;


    while (!game.getWinCon())
    {
        std::vector<int> guess = game.generateNewGuess();
        game.validateGuess(guess);
        ++turn;
    }

    std::cout << "\nSecret guessed in " << turn << " turns!\n";
    std::cout << "Secret was: ";
    game.printSecret();
}
