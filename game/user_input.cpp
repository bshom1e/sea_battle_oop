#include "user_input.h"

User_input::User_input() : char_commands() {
  char_commands = {'1', '2', '3', '4', '5'};
  string line, command;
  char command_char;
  ifstream in("../saves/game_commands.txt"); // окрываем файл для чтения
  while (getline(in, line)) {
    if (line.empty()) continue;
    command = line.substr(0, line.size() - 1);
    command_char = line[line.size() - 1];
    for (int i = 0; i < STRING_COMMANDS.size(); i++) {
      if (command == STRING_COMMANDS[i]) {
        char_commands[i] = command_char;
      }
    }
  }
  in.close();
  for (int i = 0; i < char_commands.size(); i++) {
    for (int j = i + 1; j < char_commands.size(); j++) {
      if (char_commands[i] == char_commands[j]) {
        string message = "Двойное назначение клавиши:  ";
        message[message.size() - 1] = char_commands[i];
        throw Command_input_error(message);
      }
    }
  }
}

int User_input::get_command() {
  string input;
  while (true) {
    getline(cin, input);
    if (input.size() != 1) continue;
    for (int i = 0; i < char_commands.size(); i++) {
      if (input[0] == char_commands[i]) {
        return i;
      }
    }
  }
}

void User_input::print_commands() {
  cout << "Выберите символ одной из следующих команд:\n";
  for (int i = 0; i < STRING_COMMANDS.size(); i++) {
    cout << STRING_COMMANDS[i] << char_commands[i] << "   ";
  }
  cout << endl;
}

pair<int, int> User_input::get_coordinates() {
  while (true) {
    string user_input;
    cout << "Введите координаты в формате \"x y\": ";
    getline(cin, user_input);
    istringstream iss(user_input);
    int x, y;
    if (!(iss >> x >> y)) {
      cout << "Координаты введены неправильно, попробуйте ввести снова в формате \"x y\": " << endl;
      continue;
    }
    if (iss.rdbuf()->in_avail() != 0) {
      cout << "Координаты введены неправильно. Дополнительные символы после координат." << endl;
      continue;
    }
    return {x, y};
  }
}
