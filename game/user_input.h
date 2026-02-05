#ifndef NAVAL_WARFARE_GAME_USER_INPUT_H_
#define NAVAL_WARFARE_GAME_USER_INPUT_H_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include "../exceptions/command_input_error.h"

using namespace std;

class User_input {
 private:
  vector<string> STRING_COMMANDS = {"Attack command:", "Ability command:", "Save command:", "Load command:", "Exit game:"};
  vector<char> char_commands;
 public:
  User_input();
  int get_command();
  pair<int, int> get_coordinates();
  void print_commands();
};

#endif //NAVAL_WARFARE_GAME_USER_INPUT_H_
