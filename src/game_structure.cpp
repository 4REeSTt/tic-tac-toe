#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game_structure.hpp"


//class functions init
void field::setFieldValue(sf::Sprite sprt, int x, int y, Player player){
    s_field[x*SIZE + y] = sprt;
    flag_field[x*SIZE + y] = true;
    s_field[x*SIZE + y].setPosition(sf::Vector2f((x*100.f),(y*100.f)));
    logic_field[x*SIZE + y] = player;
}   

sf::Sprite field::getFieldValue_print(int x, int y){
    return s_field[x*SIZE + y];
}

Player field::getFieldValue_logic(int x,int y){
    return logic_field[x*SIZE + y];
}   

void field::clear(){
    for(int i{0}; i < SIZE; i++){
        for(int j{0}; j < SIZE; j++){
            flag_field[i*SIZE + j] = false;
            logic_field[i*SIZE + j] = Player::EMPTY;
        }
    }
}

bool field::check_flag(int x, int y){
    return flag_field[x*SIZE + y];
}

 Player field::getPlayer(){
    return current_player;
}

void field::setPlayer(Player player){
    current_player = player;
}



void ai(field& field, sf::Sprite sprt){
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


void draw_field(field& field, sf::RenderWindow& window){
    for(int i{0}; i < SIZE; i++)
        for(int j{0}; j < SIZE; j++)
            if(field.check_flag(i,j))
                window.draw(field.getFieldValue_print(i,j));
}
