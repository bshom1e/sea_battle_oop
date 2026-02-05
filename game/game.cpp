#include "game.h"

Game::Game() {
  game_status = NOT_STARTED;
  game_state = new Game_state();
  player_gamefield = nullptr;
  computer_gamefield = nullptr;
  player_ship_manager = nullptr;
  computer_ship_manager = nullptr;
  player_ability_manager = nullptr;
}

void Game::new_computer_enemy() {
  computer_gamefield = new Gamefield(10, 10);
  computer_ship_manager = new Ship_Manager(1, {1});
  computer_ship_manager->place_ships_on_field(computer_gamefield);
}

void Game::new_game() {
  player_gamefield = new Gamefield(10, 10);
  player_ship_manager = new Ship_Manager(1, {1});
  player_ability_manager = new AbilityManager();
  player_ship_manager->place_ships_on_field(player_gamefield);
  new_computer_enemy();
}

void Game::game_save() {
  game_state->save_game_state(player_ship_manager, player_gamefield, player_ability_manager, computer_ship_manager, computer_gamefield);
}

void Game::game_load() {
  game_state->load_game_state();
  player_ship_manager->load(game_state->get_datapack(PLAYER_SHIP_MANAGER_DATA));
  player_gamefield->load(game_state->get_datapack(PLAYER_GAMEFIELD_DATA));
  player_ship_manager->place_ships_on_field(player_gamefield);
  player_ability_manager->load(game_state->get_datapack(PLAYER_ABILITY_MANAGER_DATA));
  computer_ship_manager->load(game_state->get_datapack(COMPUTER_SHIP_MANAGER_DATA));
  computer_gamefield->load(game_state->get_datapack(COMPUTER_GAMEFIELD_DATA));
  computer_ship_manager->place_ships_on_field(computer_gamefield);
}

void Game::player_attack(pair<int, int> coords) {
  computer_gamefield->field_take_hit(coords);
  if (computer_ship_manager->update_all_ship_destruction_flags()) {
    player_ability_manager->add_random_ability();
  }
}

void Game::player_use_ability(pair<int, int> coords) {
  player_ability_manager->apply_ability(coords, computer_gamefield);
  if (computer_ship_manager->update_all_ship_destruction_flags()) {
    player_ability_manager->add_random_ability();
  }
}

void Game::computer_move() {
  srand(time(nullptr));
  int x = rand() % player_gamefield->get_field_width();
  int y = rand() % player_gamefield->get_field_height();
  pair<int, int> action_coordinates = {x, y};
  player_gamefield->field_take_hit(action_coordinates);
  if (player_ship_manager->update_all_ship_destruction_flags()) {
    cout << "Потеря! Противник уничтожил корабль!" << endl;
  }
}

GameStatus Game::update_game_status() {
  if (computer_ship_manager->is_all_destroyed()) {
    game_status = VICTORY;
  } else if (player_ship_manager->is_all_destroyed()) {
    game_status = FAILURE;
  } else {
    game_status = IN_PROCESS;
  }
  return game_status;
}

string Game::get_full_gamefield_string(Gamers gamer) {
  if (gamer == PLAYER) {
    return player_gamefield->full_gamefield_to_string();
  } else if (gamer == COMPUTER) {
    return computer_gamefield->full_gamefield_to_string();
  }
  return "";
}