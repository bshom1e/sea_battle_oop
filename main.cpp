#include <iostream>
#include "gamefield/gamefield.h"
#include "ships/ship_manager.h"
#include "abilities/ability_manager.h"
#include "game/game.h"
#include "game/user_input.h"
#include "game/game_controller.h"
#include "game/game_interface.h"
#include "game/game_drawer.h"
#include "game/simple_game_drawer.h"

using namespace std;

int main() {
  Game game;
  User_input user_input;
  Game_drawer game_drawer;
  Simple_game_drawer simple_game_drawer;
  Game_controller<User_input> game_controller(game);
//  Game_interface<Simple_game_drawer> game_interface;
  Game_interface<Game_drawer> game_interface;
  while (true) {
//    game_interface.draw_game_interface(simple_game_drawer, game);
    game_interface.draw_game_interface(game_drawer, game);
    game_controller.round(user_input);
  }
//  Game new_game;
//  new_game.game_start();
//  Gamefield gamefield = Gamefield(10, 10);
//  Ship_Manager ship_manager = Ship_Manager(2, {3, 3});
//  ship_manager.place_ships_on_field(&gamefield);
//  FILE* slot = fopen("../saves/slot1.txt", "w+");
  return 0;
}
