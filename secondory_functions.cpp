#pragma once
#include <iostream>
#include <random>
#include <windows.h>
#include "Game_structure.hpp"

//Setters and Getters(Game_structure class) definition
Player Game_structure::get_player(){
    return Game_structure::current_player;
 }
void Game_structure::set_player(Player player){
    current_player = player;
}


Player Game_structure::get_field_value(int x, int y) {
    return Map[x*basic_field_size + y];
}
void Game_structure::set_field_value(int x,int y){
    Map[x*basic_field_size + y] = current_player;
}


void Game_structure::create_field(int size){
    Map = new Player [basic_field_size * basic_field_size];
}
void Game_structure::delete_field(){
    delete[] Map;
}


int Game_structure::get_field_size(){
    return basic_field_size;
}
void Game_structure::set_field_size(int size){
    basic_field_size = size;
}

//Small check smth functions
bool isvalid(Game_structure& game_status, int x, int y){
    if(x < 0 || x > (game_status.get_field_size() - 1))
        return false;
    if(y < 0 || y > (game_status.get_field_size() - 1))
        return false;
    return true;
}
bool isempty_box_in_field(Game_structure& game_status, int x,int y){
    if(game_status.get_field_value(x, y) == Player::EMPTY)
        return true;
    return false;
}
//Check line on winning combinagion depends on field size and vectors(x,y);
bool line_check(Game_structure game_status, int x, int y, int vx, int vy) {
    int out_of_x = x + ((game_status.get_field_size() - 1) * vx);
    int out_of_y = y + ((game_status.get_field_size() - 1) * vy);
    if (!isvalid(game_status, out_of_x, out_of_y))
        return false;
    for (int step = 0; step < game_status.get_field_size(); step++)
        if (game_status.get_field_value((x + vx * step), (y + vy * step)) != game_status.get_player())
            return false;
    return true;
}

//Prints new field and clears terminal output
void print(Game_structure& game_status){
    std::system("cls");
    for(int i = 0; i < game_status.get_field_size(); i++){
        std::cout << "|";
        for (int j = 0; j < game_status.get_field_size(); j++){
            std::cout << (char)game_status.get_field_value(i, j) << "|";
        }
        std::cout << "\n";
    }
}
//Set game field EMPTY
void clear_field(Game_structure& game_status){
    game_status.set_player(Player::EMPTY);
    for(int i = 0; i < game_status.get_field_size(); i++)
        for(int j = 0; j < game_status.get_field_size(); j++)
            game_status.set_field_value(i, j);   
}

//Lets AI make HUMAN turn and make EMPTY turn
void set_not_players_field(Game_structure& game_status, int x, int y, Player owner,Player other){
    game_status.set_player(other);
    game_status.set_field_value(x, y);
    game_status.set_player(owner);
}
//"Advanced AI algorithms" puts AI on EMPTY field piece and check if he(AI) wins
bool ai_win_check(Game_structure& game_status){
    Player win_check_status;
    for(int x = 0; x < game_status.get_field_size(); x++){
        for(int y = 0; y < game_status.get_field_size(); y++){
            if(isempty_box_in_field(game_status, x, y)){
                game_status.set_field_value(x, y);
                if(win_check(game_status) == Player::AI)
                    return true;
                set_not_players_field(game_status, x, y, game_status.get_player(), Player::EMPTY);
            }
        }
    }
    return false;
}
//"Advanced AI algorithms" puts HUMAN on EMPTY field piece and check if he(HUMAN) wins
bool human_win_check(Game_structure& game_status){
    game_status.set_player(Player::HUMAN);
    for(int x = 0; x < game_status.get_field_size(); x++){
        for(int y = 0; y < game_status.get_field_size(); y++){
            if(isempty_box_in_field(game_status, x, y)){
                game_status.set_field_value(x, y);
                if(win_check(game_status) == Player::HUMAN){
                    set_not_players_field(game_status, x, y, game_status.get_player(), Player::AI);
                    return true;
                }
                set_not_players_field(game_status, x, y, game_status.get_player(), Player::EMPTY);
            }
        }
    }
    game_status.set_player(Player::AI);
    return false;
}

//Creates field depends on size.
int field_size_choise(Game_structure& game_status){
    int size;
    do{
        std::cout << "Enter field size you want to play!(3 - 50)\n>";
        std::cin >> size;

        //Valid input check
        if(!std::cin){
            std::cout << "Are you dumb? How can it be the size?\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue; 
        }
    }while(size < 3 || size > 50);
    game_status.set_field_size(size);
    game_status.create_field(game_status.get_field_size());
    return size;
}
//Prints whose win
void winner_output(Game_structure& game_structure) {
    if (game_structure.get_player() == Player::EMPTY)
        std::cout << "Draw! \n";
    if (game_structure.get_player() == Player::HUMAN)
        std::cout << "You won!\n";
    if (game_structure.get_player() == Player::AI)
        std::cout << "Player::AI won!\n";
}
//Asking player to starn new game
bool want_more(Game_structure& game_status){
    std::cout << "Play again?(yes or no)\n>";
    char answer[50];
    std::cin >> answer;
    if(answer[0] == 'y' || answer[0] == 'Y' || answer[0] == '1')
        return true;
       return false;
    game_status.delete_field();
}
