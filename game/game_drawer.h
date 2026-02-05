#ifndef NAVAL_WARFARE_GAME_GAME_DRAWER_H_
#define NAVAL_WARFARE_GAME_GAME_DRAWER_H_

#include <string>
#include <iostream>

using namespace std;

#define DESTROYED_PRINT "\x1B[1;41m"
#define DAMAGED_PRINT "\x1B[1;43m"
#define UNTOUCHED_PRINT "\x1B[1;47m"
#define SEA "\x1B[1;44m"
#define SEA_HIT "\x1B[1;30;45m"
#define RESET "\x1B[0m"

class Game_drawer {
 public:
  Game_drawer();
  void draw_gamefield(string str_gamefield);
};

#endif //NAVAL_WARFARE_GAME_GAME_DRAWER_H_
