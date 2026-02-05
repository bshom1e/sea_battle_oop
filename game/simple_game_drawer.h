#ifndef NAVAL_WARFARE_GAME_SIMPLE_GAME_DRAWER_H_
#define NAVAL_WARFARE_GAME_SIMPLE_GAME_DRAWER_H_

#include <string>
#include <iostream>

using namespace std;

class Simple_game_drawer {
 public:
  void draw_gamefield(string str_gamefield) {
    cout << str_gamefield;
  }
};

#endif //NAVAL_WARFARE_GAME_SIMPLE_GAME_DRAWER_H_
