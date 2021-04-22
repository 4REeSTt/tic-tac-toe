#pragma once
#include <iostream>
#include <random>
#include <windows.h>
#include "Game_structure.hpp"

Player win_check(Game_structure& game_status) {
    for (int i = 0; i < game_status.get_field_size(); i++) {
        for (int j = 0; j < game_status.get_field_size(); j++) {
            if (line_check(game_status, i, j, 1, 0)) return game_status.get_player();
            if (line_check(game_status, i, j, 0, 1)) return game_status.get_player();
            if (line_check(game_status, i, j, 1, 1)) return game_status.get_player();
            if (line_check(game_status, i, j, -1, 1)) return game_status.get_player();
        }
    }
    return Player::EMPTY;
}
bool draw_check(Game_structure& game_status){
    for(int i = 0; i < game_status.get_field_size(); i++)
        for(int j = 0; j < game_status.get_field_size(); j++)
            if(game_status.get_field_value(i,j) == Player::EMPTY)
                return false;
   game_status.set_player(Player::EMPTY);
    return true;
}


void human(Game_structure& game_status){
    int x, y;
    game_status.set_player(Player::HUMAN);
    do{
        std::cout << "Make your turn (row and col)(1 - " << game_status.get_field_size() << ")\n>";
        std::cin >> x >> y;
        if(!std::cin){
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        x--;y--;
    }while(!isvalid(game_status, x, y) || !isempty_box_in_field(game_status, x, y));
    game_status.set_field_value(x, y);
}

void ai(Game_structure& game_status){
    int x, y;
    game_status.set_player(Player::AI);
    if(ai_win_check(game_status)) return;
    if(human_win_check(game_status)) return;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, game_status.get_field_size());
    do{
        x = dist(mt);
        y = dist(mt);
    } while (!isempty_box_in_field(game_status, x, y));
    game_status.set_field_value(x, y);
}
