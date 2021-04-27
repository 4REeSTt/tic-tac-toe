#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game_structure.hpp"

bool isempty(field& field,int x, int y){
   if(field.getFieldValue_logic(x, y) == Player::EMPTY)
       return true;
   return false;
}

 bool isvalid( int x, int y){
    if(x < 0 || x > SIZE -1 )
        return false;
    if(y < 0 || y > SIZE -1 )
        return false;
    return true;
}

bool line_check(field& field, int x, int y, int vx, int vy){
    int out_of_x = x + (SIZE -1)*vx;
    int out_of_y = y + (SIZE -1)*vy;
    if(!isvalid(out_of_x, out_of_y))
        return false;
    for(int step{0}; step < SIZE; step++){
        if(field.getFieldValue_logic((x + vx*step),(y + vy*step)) != field.getPlayer())
            return false;
        field.setWinCombination((x + vx*step),(y + vy*step), step);
    }
    return true;
}

void draw_field(field& field, sf::RenderWindow& window){
    for(int i{0}; i < SIZE; i++)
        for(int j{0}; j < SIZE; j++)
            if(field.getFieldValue_logic(i,j) != Player::EMPTY)
                window.draw(field.getFieldValue_print(i,j));
}


void print_window(sf::RenderWindow& window, sf::Sprite& sprt, field& field){
    window.clear();
    window.draw(sprt);
    draw_field(field, window);
    window.display();
}
