#include <iostream>
#include <random>
#include <algorithm>

//Set field values for game
enum PLAYER {
    HUMAN = 'X',
    AI    = 'O',
    EMPTY = '_'
};
//Set game structure
typedef struct{
    int sz_Y;
    int sz_X;
    PLAYER** map;
    int to_win;
}Field;

//Secondory funcrions
#define CHK_DOT(x, sz) ((x) >= 0 && (x) < (sz))
#define POINT_ITEM(a, r, c) (*((*(a + r)) + c))

char getval(PLAYER** array, int row, int col){
    return POINT_ITEM(array, row, col);
}
void setval(PLAYER** array, const int row, const int col, PLAYER value){
    POINT_ITEM(array, row, col) = value;
}
int isvalid(Field &field, int x, int y){
    return CHK_DOT(x, field.sz_X) && CHK_DOT(y, field.sz_Y);
}
int isempty(Field &field, int x, int y){
    return getval(field.map, y, x) == EMPTY;
}
//Check draw position
int isdraw(Field &field){
    for(int y = 0; y < field.sz_Y; y++)
        for(int x = 0; x < field.sz_X; x++)
            if(isempty(field, x, y))
                return 0;
    return 1;
}

int field_size;
//Start new game
void init(Field &field){
    
    field.to_win = field_size;
    field.sz_Y   = field_size;
    field.sz_X   = field_size;
    field.map    = (PLAYER **) new PLAYER*[field.sz_Y];
    for(int y = 0; y < field.sz_Y; y++){
        *(field.map + y) =(PLAYER*) new PLAYER[field.sz_X];
        for(int x = 0; x <field.sz_X; x++){
            setval(field.map, y, x, EMPTY);
        }
    }
}

//Print current field
void print(Field &field){
    //#include <windows.h>
    //ststem("cls")
#if _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
    std::cout << ("-------\n");
    for(int i = 0; i < field.sz_Y; i++){
        std::cout << "|";
        for(int j = 0; j < field.sz_Y; j++){
            std::cout << getval(field.map, i, j) << "|";
        }
        std::cout << std::endl;
    }
}

//HUMAN's turn
void human(Field &field){
    int x, y;
    do{
        std::cout << "Enter X and Y (from 1 to " << field.sz_Y << ") sep by space >>";
        std::cin >> x >> y;
        x--; y--;
    }while(!isvalid(field, x, y) || !isempty(field, x, y));
    setval(field.map, y, x, HUMAN);
}


//Check wining combination
int line_chk(Field &field, int y, int x, int vx, int vy, int len, PLAYER c){
    const int end_x = x + (len - 1) * vx;
    const int end_y = y + (len - 1) * vy;
    if(!isvalid(field, end_x, end_y))
        return 0;
    for(int i = 0; i < len; i++)
        if(getval(field.map, (y + i*vy), (x + i*vx)) != c)
            return 0;
    return 1;
}

//Check last turn was winnig
int win_chk(Field &field, PLAYER c){
    for(int y = 0; y < field.sz_X; y++){
        for(int x = 0; x < field.sz_Y; x++){
            if(line_chk(field, y, x, 1,  0, field.to_win, c)) return 1;
            if(line_chk(field, y, x, 1,  1, field.to_win, c)) return 1;
            if(line_chk(field, y, x, 0,  1, field.to_win, c)) return 1;
            if(line_chk(field, y, x, 1, -1, field.to_win, c)) return 1;
        }
    }
    return 0;
}
//Advanced AI
int ai_win_chk(Field &field){
    for(int y = 0; y < field.sz_Y; y++){
        for(int x = 0; x < field.sz_X; x++){
            if(isempty(field, x, y)){
                setval(field.map, y, x, AI);
                if(win_chk(field, AI))
                    return 1;
                setval(field.map, y, x, EMPTY);
            }
        }
    }
    return 0;
}

int hum_win_chk(Field &field){
    for(int y = 0; y < field.sz_Y; y++){
        for(int x = 0; x < field.sz_X; x++){
            if(isempty(field, x, y)){
                setval(field.map, y, x, HUMAN);
                if (win_chk(field, HUMAN)){
                    setval(field.map, y, x, AI);
                    return 1;
                }
                setval(field.map, y, x, EMPTY);
            }
        }
    }
    return 0;
}
//AI's turn
void ai(Field &field){
    if(ai_win_chk(field))
        return;
    if(hum_win_chk(field))
        return;
    int x, y;
    //C++11 <random>
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double>dist(0, 3);
    do{
        x = dist(mt);
        y = dist(mt);
    }while(!isempty(field, x, y));
    setval(field.map, y, x, AI);
}





//Check current position
int game_chk(Field &field, PLAYER dot, const std::string &win_String){
    if(win_chk(field, dot)){
        std::cout << win_String << std::endl;
        return 1;
    }
    if(isdraw(field)){
        std::cout << "draw" << std::endl;
        return 1;
    }
    return 0;
}


//Game cycle
void tictactoe(){
    Field field;
    while(true){
        do{
            std::cout << "Enter size of field \n> ";
            std::cin >> field_size;
        }while(field_size < 3);
        init (field);
        print(field);
        while(true){
            human(field);
            print(field);
            if(game_chk(field, HUMAN, "Human win!")) break;
            ai   (field);
            print(field);
            if(game_chk(field, AI, "AI win!")) break;
        }
        std::string answer;
        std::cout << "Play again? ";
        std::cin >> answer;
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if(answer.find('y') != 0)
            break;
    }
}


int main(){
    tictactoe();
    return 0; 
}
