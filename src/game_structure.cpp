#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game_structure.hpp"


//class functions init
void field::setFieldValue(sf::Sprite sprt, int x, int y, Player player){
    s_field[x*SIZE + y] = sprt;
    s_field[x*SIZE + y].setPosition(sf::Vector2f((x*100.f),(y*100.f)));
    logic_field[x*SIZE + y] = player;
}   

sf::Sprite field::getFieldValue_print(int x, int y){
    return s_field[x*SIZE + y];
}

Player field::getFieldValue_logic(int x,int y){
    return logic_field[x*SIZE + y];
}   
void field::setFieldValue_logic(int x,int y, Player player){
   logic_field[x* SIZE + y] = player;
}

void field::clear(){
    for(int i{0}; i < SIZE; i++){
        for(int j{0}; j < SIZE; j++){
            logic_field[i*SIZE + j] = Player::EMPTY;
        }
    }
}

 Player field::getPlayer(){
    return current_player;
}

void field::setPlayer(Player player){
    current_player = player;
}

void field::setWinCombination(int x, int y, int iteration){
   win_combination[iteration][0] = x;
   win_combination[iteration][1] = y;
}

int* field::getWinCombination(){
    return &win_combination[0][0];
}

void print_win_combination(sf::RenderWindow& window, sf::Sprite& sprt, sf::Sprite sprt_bg, field& field){
    int* arr = field.getWinCombination();
    field.clear();
    field.setFieldValue(sprt, arr[0] , arr[1], field.getPlayer());
    field.setFieldValue(sprt, arr[2] , arr[3], field.getPlayer());
    field.setFieldValue(sprt, arr[4] , arr[5], field.getPlayer());
    
    print_window(window, sprt_bg, field);
}

bool human (sf::Sprite& cross, field& field, sf::RenderWindow& window){
    field.setPlayer(Player::HUMAN);
    int x, y;
    x = (sf::Mouse::getPosition(window).x /100);
    y = (sf::Mouse::getPosition(window).y /100);
    if(isvalid(x, y) && isempty(field, x, y)){
        field.setFieldValue(cross, x, y, Player::HUMAN);
        return true;
        window.display();
    }
    return false;
}

bool ai_win_check(field& field, sf::Sprite sprt, Player player){
    for(int i{0}; i < SIZE; i++)
        for(int j{0}; j < SIZE; j++)
            if(field.getFieldValue_logic(i, j) == Player::EMPTY){
                field.setFieldValue(sprt, i, j, player);
                if(check_win(field) == Player::AI)
                    return true;
                field.setFieldValue_logic(i, j, Player::EMPTY);
            }
    return false;
}

bool human_win_check(field& field, sf::Sprite sprt_human, sf::Sprite sprt_ai, Player player){
    field.setPlayer(Player::HUMAN);
    for(int i{0}; i < SIZE; i++)
        for(int j{0}; j < SIZE; j++)
            if(field.getFieldValue_logic(i, j) == Player::EMPTY){
                field.setFieldValue(sprt_human, i, j, player);
                if(check_win(field) == Player::HUMAN){
                    field.setFieldValue(sprt_ai, i, j, Player::AI);
                    return true;
                } 
                field.setFieldValue_logic(i, j, Player::EMPTY);
        } 
    field.setPlayer(Player::AI);
    return false;
}



void ai(field& field, sf::Sprite sprt, sf::Sprite sprt_for_human){
    field.setPlayer(Player::AI);

    if(ai_win_check(field, sprt, field.getPlayer())) return;
    if(human_win_check(field, sprt_for_human, sprt, Player::HUMAN)) return;

    int x, y;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, SIZE);
    do{
        x = dist(mt);
        y = dist(mt);
    }while(!isempty(field, x, y));
    field.setFieldValue(sprt, x, y, Player::AI);
}


Player check_win(field& field){
    for(int i{0}; i < SIZE; i++)
        for(int j{0}; j < SIZE; j++){
            if(line_check(field, i, j, 1, 0)) return field.getPlayer();
            if(line_check(field, i, j, 0, 1)) return field.getPlayer();
            if(line_check(field, i, j, 1, 1)) return field.getPlayer();
            if(line_check(field, i, j,-1, 1)) return field.getPlayer();
        }
   return Player::EMPTY;
}

bool check_draw(field& field){
    for(int x{0}; x < SIZE; x++)
        for(int y{0}; y < SIZE; y++)
            if(field.getFieldValue_logic(x, y) == Player::EMPTY)
                return false;
    return true;
}

