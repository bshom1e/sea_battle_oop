#ifndef NAVAL_WARFARE_GAME_GAME_INTERFACE_H_
#define NAVAL_WARFARE_GAME_GAME_INTERFACE_H_

#include "game.h"

template <class DrawManager>
class Game_interface {
 private:
 public:
  Game_interface() = default;
  void draw_game_interface(DrawManager draw_manager, Game game) {
    cout << "Ваше поле:\n";
    draw_manager.draw_gamefield(game.get_full_gamefield_string(PLAYER));
    cout << "Поле противника\n";
    draw_manager.draw_gamefield(game.get_full_gamefield_string(COMPUTER));
  }
};

#endif //NAVAL_WARFARE_GAME_GAME_INTERFACE_H_
