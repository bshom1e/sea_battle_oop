#include "ability_manager.h"

AbilityManager::AbilityManager() {
  // Инициализация случайных способностей
  abilities.push_back(new DoubleDamage());
  abilities.push_back(new Scanner());
  abilities.push_back(new Bombard());
}

void AbilityManager::apply_ability(pair<int, int> coords, Gamefield* gamefield) {
  if (abilities.empty()) {
    throw Invalid_ability_usage("Ошибка: Нет доступных способностей.");
  }
  srand(time(nullptr));
  int index = rand() % abilities.size();
  abilities[index]->use(coords, gamefield);
  abilities.erase(abilities.begin() + index);  // Удаляем использованную способность
}

void AbilityManager::add_random_ability() {
  // Добавление случайной способности при уничтожении корабля
  srand(time(nullptr));
  int randomAbility = rand() % 3;
  switch (randomAbility) {
    case DOUBLE_DAMAGE: abilities.push_back(new DoubleDamage()); break;
    case SCANNER: abilities.push_back(new Scanner()); break;
    case BOMBARD: abilities.push_back(new Bombard()); break;
  }
  cout << "Получена новая способность!\n";
}

string AbilityManager::ability_manager_to_string() {
  string ability_manager_string = "abilities_amount:" + to_string(abilities.size()) + "\n";
  for (auto ability : abilities) {
    ability_manager_string += ability->ability_to_string() + " ";
  }
  ability_manager_string += "\n";
  return ability_manager_string;
}

void AbilityManager::load(string data) {
  abilities.clear();
  istringstream stream(data);
  string line;
  int abilities_amount = 0;
  if (getline(stream, line)) {
    size_t pos = line.find(':') + 1;
    if (pos != string::npos) {
      abilities_amount = stoi(line.substr(pos));
    }
  }
  if (getline(stream, line)) {
    istringstream ability_stream(line);
    int ability;
    while (ability_stream >> ability) {
      switch (ability) {
        case DOUBLE_DAMAGE: abilities.push_back(new DoubleDamage()); break;
        case SCANNER: abilities.push_back(new Scanner()); break;
        case BOMBARD: abilities.push_back(new Bombard()); break;
        default: throw Load_error("Ошибка при загрузке: Нет способности" + to_string(ability));
      }
    }
  }
  if (abilities_amount != abilities.size()) {
    throw Load_error("Ошибка при загрузке менеджера способностей");
  }
}