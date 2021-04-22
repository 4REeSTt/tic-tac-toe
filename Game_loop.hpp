#pragma once
#include <iostream>
#include "Game_structure.hpp"

//Current game loop
void current_game_loop(Game_structure& game_status) {
    while (true) {
        print(game_status);
        human(game_status);
        print(game_status);
        if (win_check(game_status) != Player::EMPTY) break;
        if (draw_check(game_status))break;
        ai(game_status);
        if (win_check(game_status) != Player::EMPTY) break;
        if (draw_check(game_status))break;
        //Win will be inside structure
    }
}


void Game_loop(Game_structure& game_status){
    //Start of the game, choosing size of the field
    //Human can play only X
    //int basic_field_size;
    do{
        field_size_choise(game_status); //Create field, by size of choice
        clear_field(game_status);                  //Make sure that field is EMPTY
        current_game_loop(game_status);            //Start game session
        print(game_status);

        winner_output(game_status);
    }while(want_more(game_status)); //Clears heap memory if game will be continued
}
