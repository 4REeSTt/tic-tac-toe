# tic-tac-toe

terminal version is on branch `terminal vercion`(I know that version)

Gui version ain't done yet. You can play but no Start of the game, no Win Loose Draw massages, and bugs with draw.

###### To start on linux:
1. Download SFML using your package manager
2. In the terminal make shure you are in main folder `tic-tac-toe/`
3. Run `cmake -B build`
4. Run `make -C build` (make shure you have ***make***)
5. Run `./build/src/test` to start the game

###### If you have SFML and make(linux):

    $ git clone https://github.com/4REeSTt/tic-tac-toe.git
    $ cd tic-tac-toe/
    $ cmake -B build/
    $ make -C build/
    $ ./build/src/test
  
###### To start on windows: http://www.sfml-dev.org/download/sfml/2.4.0
1. Install SFML package https://www.sfml-dev.org/download/sfml/2.5.1/ and place it in C:\ folder
2. You can try run it in IDE, don't forget to add libs from bin folder(SFML) to folder with .exe (you can just copy and paste all of them)
3. If you run in terminal with MinWG make gcc, run as same as linux
   - run `cmake -B build -G "MinGW Makefiles"`
   - run `make -C build`
   - but don't forget 2nd and add(libs) to ./build/src after compitation(make)
   - `./build/src/test`



###### Pictures

All pictures is in res/  

![field](/res/field.png) ![](/res/cross.png) ![](/res/zerro.png) ![](res/start.png)
