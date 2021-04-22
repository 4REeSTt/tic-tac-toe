#pragma once

#include <iostream>


enum class Player {
    EMPTY = '_',
    HUMAN = 'X',
    AI = 'O'
};

//basic_fiel_size we coud put int this class(private + setter + getter)
class Game_structure {
public:
    Player get_field_value(int y, int x);
    void   set_field_value(int y, int x);

    Player get_player();
    void   set_player(Player player);

    void   create_field(int size);
    void   delete_field();
    
    void   set_field_size(int size);
    int    get_field_size();
private:
    int basic_field_size;
    Player* Map;
    Player current_player;
};


//Game functions declaring
void human(Game_structure& game_status);
void ai(Game_structure& game_status);
bool ai_win_check(Game_structure& game_status);
bool human_win_check(Game_structure& game_status);
void set_not_players_field(Game_structure& game_status, int x, int y, Player owner,Player other);

bool isvalid(Game_structure& game_status, int x, int y);
bool isempty_box_in_field(Game_structure& game_status, int x,int y);
bool line_check(Game_structure game_status, int x, int y, int vx, int vy);

bool   draw_check(Game_structure& game_status);
Player win_check(Game_structure& game_status);

int  field_size_choise(Game_structure& game_status);
void print(Game_structure& game_status);
void clear_field(Game_structure& game_status);
void winner_output(Game_structure& game_structure);
bool want_more(Game_structure& game_status);




