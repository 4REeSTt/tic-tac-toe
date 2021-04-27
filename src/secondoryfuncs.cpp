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
    for(int step{0}; step < SIZE; step++)
        if(field.getFieldValue_logic((x + vx*step),(y + vy*step)) != field.getPlayer())
            return false;
    return true;
}
