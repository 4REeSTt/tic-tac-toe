#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

const int SIZE{3};

enum class Player{
    EMPTY,
    HUMAN,
    AI
};

//class reclaring
class field{
public:
    void setFieldValue(sf::Sprite sprt, int x, int y, Player player);
    sf::Sprite getFieldValue_print(int x, int y);
    Player getFieldValue_logic(int x,int y);

    void clear();

    bool check_flag(int x, int y);
    
    void setPlayer(Player player);
    Player getPlayer();
private:
    sf::Sprite s_field[SIZE*SIZE];
    bool flag_field[SIZE*SIZE]{0};
    Player logic_field[SIZE*SIZE];
    Player current_player;

};

// functions declaring
bool line_check(field& field, int x, int y, int vx, int vy);
Player check_win(field& field);
bool check_draw(field& field);
bool isvalid( int x, int y);
bool isempty(field& field,int x, int y);
void ai(field& field, sf::Sprite sprt); 
bool human(sf::Sprite& cross, field& field, sf::RenderWindow& window);

void draw_field(field& field, sf::RenderWindow& window);
