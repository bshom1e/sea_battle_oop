#ifndef NAVAL_WARFARE_GAME_GAME_CONTROLLER_H_
#define NAVAL_WARFARE_GAME_GAME_CONTROLLER_H_

#include "game.h"

enum Game_commands {
  ATTACK_COMMAND,
  ABILITY_COMMAND,
  SAVE_COMMAND,
  LOAD_COMMAND,
  END_COMMAND
};

template <class InputManager>
class Game_controller {
 private:
  Game& game_;
 public:
  Game_controller(Game& game) : game_(game) {
    game_.new_game();
  }

  void round(InputManager input_manager) {
    cout << "Ваш ход!\n";
    input_manager.print_commands();
    switch (input_manager.get_command()) {
      case ATTACK_COMMAND:
        game_.player_attack(input_manager.get_coordinates());
        break;
      case ABILITY_COMMAND:
        game_.player_use_ability(input_manager.get_coordinates());
        break;
      case SAVE_COMMAND:
        game_.game_save();
        return;
        break;
      case LOAD_COMMAND:
        game_.game_load();
        return;
        break;
      case END_COMMAND:
        cout << "Бой окончен. Спасибо за игру!\n";
        break;
      default:
        cout << "Неизвестная команда. Повторите ввод.\n";
    }
    if (game_.update_game_status() == VICTORY) {
      cout << "Поздравляем, победа! Ищем нового противника\n";
      game_.new_computer_enemy();
      return;
    }
    cout << "Ход компьютера!\n";
    game_.computer_move();
    if (game_.update_game_status() == FAILURE) {
      cout << "Вы проиграли! Начинаем новую игру\n";
      game_.new_game();
      return;
    }
  }
};

#endif //NAVAL_WARFARE_GAME_GAME_CONTROLLER_H_
