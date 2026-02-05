#include "game_drawer.h"

Game_drawer::Game_drawer() {}

void Game_drawer::draw_gamefield(string str_gamefield) {
  for (auto field_char: str_gamefield) {
    switch (field_char) {
      case '_':
        cout << SEA << " " << RESET;
        break;
      case 'X':
        cout << SEA_HIT << "X" << RESET;
        break;
      case '0':
        cout << DESTROYED_PRINT << "0" << RESET;
        break;
      case '1':
        cout << DAMAGED_PRINT << "1" << RESET;
        break;
      case '2':
        cout << UNTOUCHED_PRINT << "2" << RESET;
        break;
      case '\n':
        cout << "\n";
      default:
        cout << field_char;
    }
  }
}