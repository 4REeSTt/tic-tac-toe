#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game_structure.hpp"

#define WINDOW_NOT_CLOSED\ 
        while (window.pollEvent(event))\
        {\
            if (event.type == sf::Event::Closed)\
                window.close();\
        }



int main()
{
    Player win_status = Player::EMPTY;
    field Fieldclass;

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

        window.clear();
        window.draw(start);
        window.display();
     
        int  button_x{(sf::Mouse::getPosition(window).x)}
            ,button_y{(sf::Mouse::getPosition(window).y)};

        //if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_x > 75.f && button_x < 225.f && button_y > 125.f && button_y > 175.f){
            while(true){
                window.clear();
                window.draw(bg);

                draw_field(Fieldclass,window);

                window.display();

                WINDOW_NOT_CLOSED;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if(human(cross, Fieldclass, window)){
                        if(check_win(Fieldclass) != Player::EMPTY){
                            win_status = Player::HUMAN;
                            break;
                        }
                        if(check_draw(Fieldclass)){
                            win_status = Player::EMPTY;
                            break;
                        }
                        window.clear();
                        window.draw(bg);

                        draw_field(Fieldclass, window);

                        window.display();

                        Fieldclass.setPlayer(Player::AI);

                        ai(Fieldclass, zerro);
                        if(check_win(Fieldclass) != Player::EMPTY){
                            win_status = Player::AI;
                            break;
                        }
                        if(check_draw(Fieldclass)){
                            win_status = Player::EMPTY;
                            break;
                        }
                    }
                }
            }
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(win_status == Player::AI){
                    window.clear();
                    window.draw(aiw);
                    window.display();
                }else if(win_status == Player::HUMAN){
                    window.clear();
                    window.draw(humanW);
                    window.display();
                }else{
                    window.clear();
                    window.draw(draw);
                    window.display();
                }
            }
            Fieldclass.clear();
        //}
    }
    return 0;
    window.clear();
    window.close();
}
        //std::cout << (sf::Mouse::getPosition(window).x /100) << " " << (sf::Mouse::getPosition(window).y /100) << std::endl;
