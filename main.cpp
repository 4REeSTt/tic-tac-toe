#include <iostream>
#include <windows.h>

#include "Game_structure.hpp"
#include "Game_loop.hpp"

int main(){
//Declare main game structure
    Game_structure Game_status;
//Start of the app
    Game_loop(Game_status);

    return 0;
}
