#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

const int SIZE{3};

enum class Player{
    EMPTY,
    HUMAN,
    AI
};

//class declaring
class field{
public:
    void setFieldValue(sf::Sprite sprt, int x, int y, Player player);
    sf::Sprite getFieldValue_print(int x, int y);

    Player getFieldValue_logic(int x,int y);
    void setFieldValue_logic(int x,int y, Player player);

    void clear();
    void setPlayer(Player player);
    Player getPlayer();

    void setWinCombination(int x, int y, int iteration);
    int* getWinCombination();
private:
    sf::Sprite s_field[SIZE*SIZE];
    Player logic_field[SIZE*SIZE];
    Player current_player;
    int win_combination[3][2];
};

// functions declaring
bool line_check(field& field, int x, int y, int vx, int vy);
bool isvalid( int x, int y);
bool isempty(field& field,int x, int y);

Player check_win(field& field);
bool check_draw(field& field);

void ai(field& field, sf::Sprite sprt, sf::Sprite sprt_for_human); 
bool ai_win_check(field& field, sf::Sprite sprt, Player player);
bool human_win_check(field& field, sf::Sprite sprt_human, sf::Sprite sprt_ai, Player player);
bool human(sf::Sprite& cross, field& field, sf::RenderWindow& window);

void draw_field(field& field, sf::RenderWindow& window);
void print_window(sf::RenderWindow& window, sf::Sprite& sprt, field& field);
void print_win_combination(sf::RenderWindow& window, sf::Sprite& sprt, sf::Sprite sprt_bg, field& field);
