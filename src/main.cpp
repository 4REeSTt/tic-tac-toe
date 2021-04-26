#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

const int  SIZE{3};




enum class Player{
    EMPTY,
    HUMAN,
    AI
};




class field{
public:
    void setFieldValue(sf::Sprite sprt, int x, int y, Player player){
        s_field[x*SIZE + y] = sprt;
        flag_field[x*SIZE + y] = true;
        s_field[x*SIZE + y].setPosition(sf::Vector2f((x*100.f),(y*100.f)));
        logic_field[x*SIZE + y] = player; 
    }
    sf::Sprite getFieldValue_print(int x, int y){
        return s_field[x*SIZE + y];
    }
    Player getFieldValue_logic(int x,int y){
        return logic_field[x*SIZE + y];
    }
    void clear(){
        for(int i{0}; i < SIZE; i++){
            for(int j{0}; j < SIZE; j++){
                flag_field[i*SIZE + j] = false;
                logic_field[i*SIZE + j] = Player::EMPTY;
            }
        }
    }

    bool check_flag(int x, int y){
        return flag_field[x*SIZE + y];
    }

    Player getPlayer(){
        return current_player;
    }
    void setPlayer(Player player){
        current_player = player;
    }
private:
    sf::Sprite s_field[SIZE*SIZE];
    bool flag_field[SIZE*SIZE]{0};
    Player logic_field[SIZE*SIZE];
    Player current_player;
    
}Fieldclass;

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
bool check_draw(field& field){
    for(int x{0}; x < SIZE; x++){
        for(int y{0}; y < SIZE; y++){
            if(field.getFieldValue_logic(x, y) == Player::EMPTY);
                return false;
        }
    }
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
    }
    return true;
}


Player check_win(field& field){
    for(int i{0}; i < SIZE; i++){
        for(int j{0}; j < SIZE; j++){
            if(line_check(field, i, j, 1, 0)) return field.getPlayer();
            if(line_check(field, i, j, 0, 1)) return field.getPlayer();
            if(line_check(field, i, j, 1, 1)) return field.getPlayer();
            if(line_check(field, i, j,-1, 1)) return field.getPlayer();
        }
    }
    return Player::EMPTY;
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



int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!",sf::Style::None);
    sf::Texture Background;
    sf::Texture Cross;
    sf::Texture Start;
    sf::Texture Zerro;
    if(!Background.loadFromFile("res/field.png") || !Cross.loadFromFile("res/cross.png") || !Zerro.loadFromFile("res/zerro.png") || !Start.loadFromFile("res/start.png"))
        return -1;
    sf::Sprite bg(Background);
    sf::Sprite cross(Cross);
    sf::Sprite zerro(Zerro);
    sf::Sprite start(Start);

    Fieldclass.clear();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
start:
        while(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            window.clear();
            window.draw(start);
            window.display();
        }
        while(true){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            Fieldclass.setPlayer(Player::HUMAN);
            int x, y;
            x = (sf::Mouse::getPosition(window).x /100);
            y = (sf::Mouse::getPosition(window).y /100);
            if(isvalid(x, y) && isempty(Fieldclass, x, y)){
                Fieldclass.setFieldValue(cross, x, y, Player::HUMAN);
                window.display();
                if(check_win(Fieldclass) != Player::EMPTY) break;
                if(check_draw(Fieldclass))break;

                window.clear();
                window.draw(bg);
                for(int i{0}; i < SIZE; i++){
                    for(int j{0}; j < SIZE; j++){
                        if(Fieldclass.check_flag(i,j))
                            window.draw(Fieldclass.getFieldValue_print(i,j));
                    }
                }
                window.display();

                Fieldclass.setPlayer(Player::AI);
                ai(Fieldclass, zerro);
                if(check_win(Fieldclass) != Player::EMPTY) break;
                if(check_draw(Fieldclass))break;
            }
        }
        window.clear();
        window.draw(bg);
        for(int i{0}; i < SIZE; i++){
            for(int j{0}; j < SIZE; j++){
                if(Fieldclass.check_flag(i,j))
                    window.draw(Fieldclass.getFieldValue_print(i,j));
            }
        }
        window.display();
        
        }
        window.clear();
        break; 
        window.close();
        //std::cout << (sf::Mouse::getPosition(window).x /100) << " " << (sf::Mouse::getPosition(window).y /100) << std::endl;
        
        //const int M{3};
        //sf::Sprite field_s[9];
        //for(int i{0}; i < 3; i++){
        //    for(int j{0}; j < 3; j++){
        //        field_s[i*M + j] = cross;
        //        field_s[i*M + j].setPosition(sf::Vector2f((j*100.f),(i*100.f)));
        //    }
        //}



    }

    return 0;
}
