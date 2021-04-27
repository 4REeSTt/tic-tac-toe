#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game_structure.hpp"

#define WINDOW_NOT_CLOSED                   \ 
                                            \
    while (window.pollEvent(event))         \
    {                                       \
        if (event.type == sf::Event::Closed)\
            window.close();                 \
    }

#define WIN_DRAW_CHECK(player)                  \ 
                                                \
    if(check_win(Fieldclass) != Player::EMPTY){ \
        win_status = player;                    \
        break;                                  \
    }                                           \
    if(check_draw(Fieldclass)){                 \
        win_status = Player::EMPTY;             \
        break;                                  \
    }



int main(){
    Player win_status = Player::EMPTY;
    field Fieldclass;
    int timer = 0;

    //Render all images
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!",sf::Style::None);
    sf::Texture Background, Start;
    sf::Texture Cross, Zerro;
    sf::Texture AIW, HumanW, Draw;
    if(!Background.loadFromFile("res/field.png") 
            || !Cross.loadFromFile("res/cross.png") 
            || !Zerro.loadFromFile("res/zerro.png") 
            || !Start.loadFromFile("res/start.png")
            || !AIW.loadFromFile("res/AIW.png")
            || !HumanW.loadFromFile("res/humanW.png")
            || !Draw.loadFromFile("res/Draw.png"))
        return -1;

    sf::Sprite bg(Background), start(Start);
    sf::Sprite cross(Cross), zerro(Zerro);
    sf::Sprite aiw(AIW), humanW(HumanW), draw(Draw);
    start.setPosition(sf::Vector2f(75.f, 125.f));

    Fieldclass.clear();
   
    //Game loop
    while(window.isOpen()){
        sf::Event event;
        WINDOW_NOT_CLOSED;

        print_window(window, start, Fieldclass);

        //For check button on
        int  button_x{(sf::Mouse::getPosition(window).x)}
            ,button_y{(sf::Mouse::getPosition(window).y)};

//If button if pressed - Start new  game
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && (button_x > 75.f) && (button_x < 225.f) && (button_y > 125.f) && (button_y < 175.f)){
            while(timer < 500){
                print_window(window, bg, Fieldclass);
                timer++;
            }
            timer = 0;

//Current game loop
            while(true){
                WINDOW_NOT_CLOSED;
                print_window(window, bg, Fieldclass);

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if(human(cross, Fieldclass, window)){

                        WIN_DRAW_CHECK(Player::HUMAN);
                        print_window(window, bg, Fieldclass);

                        ai(Fieldclass, zerro, cross);
                        WIN_DRAW_CHECK(Player::AI)
                    }
                }
            }

            while(timer < 1500){
                int* a = Fieldclass.getWinCombination();
                if(win_status != Player::EMPTY) 
                    print_win_combination(window, ((Fieldclass.getPlayer() == Player::HUMAN)? cross : zerro), bg, Fieldclass);
                timer++;
            }
            timer = 0; 
            
            Fieldclass.clear();

//Winner out put
            do{
                WINDOW_NOT_CLOSED;
                if(win_status == Player::AI)
                    print_window(window, aiw, Fieldclass);
                else if(win_status == Player::HUMAN)
                    print_window(window, humanW, Fieldclass);
                else
                    print_window(window, draw, Fieldclass);
                
                timer++;
            }while( timer < 1500);
            timer = 0;
        }
    }
    window.clear();
    window.close();
    return 0;
}
        //std::cout << (sf::Mouse::getPosition(window).x /100) << " " << (sf::Mouse::getPosition(window).y /100) << std::endl;
