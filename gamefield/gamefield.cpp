#include "gamefield.h"

// Конструктор игрового поля, принимает на вход длину и ширину
Gamefield::Gamefield(int width, int height) : field_width(width), field_height(height), field(height, vector<Cell*> (width, nullptr)) {
  amount_of_damage = 1;
  for (size_t y = 0; y < field_height; y++) {
    for (size_t x = 0; x < field_width; x++) {
      field[y][x] = new Cell();
    }
  }
}

// Оператор копирования
Gamefield& Gamefield::operator=(const Gamefield& other) {
  if (this != &other) {
    field_width = other.field_width;
    field_height = other.field_height;
    amount_of_damage = other.amount_of_damage;
    field.clear();
    field.resize(other.field.size());
    for (size_t i = 0; i < other.field.size(); ++i) {
      field[i].resize(other.field[i].size());
      for (size_t j = 0; j < other.field[i].size(); ++j) {
        field[i][j] = move(other.field[i][j]);
      }
    }
  }
  return *this;
}

// Конструктор копирования
Gamefield::Gamefield(const Gamefield& other) : field_width(other.field_width), field_height(other.field_height), amount_of_damage(other.amount_of_damage) {
  field.resize(other.field.size());
  for (size_t i = 0; i < other.field.size(); ++i) {
    field[i].resize(other.field[i].size());
    for (size_t j = 0; j < other.field[i].size(); ++j) {
      field[i][j] = new Cell(*other.field[i][j]);
    }
  }
}

//Оператор перемещения
Gamefield& Gamefield::operator=(Gamefield&& other) noexcept {
  if (this != &other) {
    field_width = other.field_width;
    field_height = other.field_height;
    amount_of_damage = other.amount_of_damage;
    other.field_height = 0;
    other.field_width = 0;
    field = move(other.field);
  }
  return *this;
}

// Конструктор перемещения
Gamefield::Gamefield(Gamefield&& other) noexcept : field_width(other.field_width), field_height(other.field_height), amount_of_damage(other.amount_of_damage), field(move(other.field)) {
  other.field_height = 0;
  other.field_width = 0;
}

// Проверка вхождения координат в поле
bool Gamefield::prove_coords(pair<int, int> coords) {
  int x = coords.first;
  int y = coords.second;
  if (x < 0 || y < 0 || x >= field_width || y >= field_height) {
    throw Out_of_bound("Некорректные координаты: {" + to_string(x) + "; " + to_string(y) + "}. При размерах поля - "
    + to_string(field_width) + "x" + to_string(field_height));
  }
  return true;
}

// Функция проверяет, можно ли поставить сегмент корабля на поданные координаты
bool Gamefield::prove_placeability(pair<int, int> coords) {
  int x_place = coords.first;
  int y_place = coords.second;
  if (!prove_coords(coords)) return false;
  for (int y = max(y_place - 1, 0); y <= min(y_place + 1, field_height - 1); y++) {
    for (int x = max(x_place - 1, 0); x <= min(x_place + 1, field_width - 1); x++) {
      if (field[y][x]->is_shipcell()) {
        return false;
      }
    }
  }
  return true;
}

bool Gamefield::prove_shipcell(pair<int, int> coords) {
  if (prove_coords(coords)) {
    return field[coords.second][coords.first]->is_shipcell();
  }
  return false;
}

// Функция размещения корабля
bool Gamefield::place_ship(Ship* ship, pair<int, int> start_coords, Orientation orientation) {
  vector<ShipPart*> ship_parts = ship->get_ship_parts();
  pair<int, int> coords = start_coords;

  for (int i = 0; i < ship->get_ship_length(); i++) {
    if (!prove_placeability(coords)) {
      throw Ship_placement_error("Корабль не может быть расположен в этом месте {" + to_string(coords.first) + ", " + to_string(coords.second) + "}.");
    }
    if (orientation == HORIZONTAL) {
      coords.first++;
    } else {
      coords.second++;
    }
  }

  coords = start_coords;
  for (int i = 0; i < ship->get_ship_length(); i++) {
    field[coords.second][coords.first]->place_shipcell(ship_parts[i]);
    if (orientation == HORIZONTAL) {
      coords.first++;
    } else {
      coords.second++;
    }
  }
  return true;
}

// Функция удаления корабля
void Gamefield::remove_ship(Ship* ship, pair<int, int> start_coords, Orientation orientation) {
  for (int i = 0; i < ship->get_ship_length(); i++) {
    if (prove_coords(start_coords)) {
      field[start_coords.second][start_coords.first]->remove_shipcell();
    }
    if (orientation == HORIZONTAL) {
      start_coords.first++;
    } else if (orientation == VERTICAL) {
      start_coords.second++;
    }
  }
}

void Gamefield::mul_amount_of_damage(int multiplier) {
  amount_of_damage *= multiplier;
}

// Функция попадания в поле
void Gamefield::field_take_hit(pair<int, int> coords) {
  int x = coords.first;
  int y = coords.second;
  if (prove_coords(coords)) {
    field[y][x]->cell_hit(amount_of_damage);
    amount_of_damage = 1; // Сброс количества урона
  } else {
    throw Attack_out_of_bound("Ошибка: Атака за границы поля {" + to_string(x) + ", " + to_string(y) + "}.");
  }
}

int Gamefield::get_field_width() {
  return field_width;
}

int Gamefield::get_field_height() {
  return field_height;
}

Cell* Gamefield::get_cell(pair<int, int> coords) {
  if (prove_coords(coords)) {
    return field[coords.second][coords.first];
  }
  return nullptr;
}

// Вывод поля
void Gamefield::print_gamefield(bool enemy_flag) {
  for (size_t y = 0; y < field_height; y++) {
    for (size_t x = 0; x < field_width; x++) {
      field[y][x]->print_cell(enemy_flag);
    }
    cout << endl << endl;
  }
  cout << endl;
}

string Gamefield::gamefield_to_string() {
  string gamefield_string;
  gamefield_string += "sizes:" + to_string(field_width) + " " + to_string(field_height) + "\n";
  gamefield_string += "amount_of_damage:" + to_string(amount_of_damage) + "\n";
  gamefield_string += "hits:";
  for (int y = 0; y < field_height; y++) {
    for (int x = 0; x < field_width; x++) {
      if (!field[y][x]->is_shipcell() && field[y][x]->is_hit()) {
        gamefield_string += to_string(x) + " " + to_string(y) + ";";
      }
    }
  }
  gamefield_string += "\n";
  return gamefield_string;
}

void Gamefield::load(string data) {
  istringstream stream(data);
  string line;
   getline(stream, line);
   if (line.find("sizes:") == 0) {
    size_t pos = line.find(':') + 1;
    if (pos != string::npos) {
      istringstream size_stream(line.substr(pos));
      size_stream >> field_width >> field_height;
    }
  }
  getline(stream, line);
  if (line.find("amount_of_damage:") == 0) {
    // Извлечение количества урона
    size_t pos = line.find(':') + 1;
    if (pos != string::npos) {
      amount_of_damage = stoi(line.substr(pos));
    }
  }
  for (size_t y = 0; y < field_height; y++) {
    for (size_t x = 0; x < field_width; x++) {
      field[y][x] = new Cell();
    }
  }
  getline(stream, line);
  if (line.find("hits:") == 0) {
    size_t pos = line.find(':') + 1;
    if (pos != string::npos) {
      string hits_str = line.substr(pos);
      istringstream hit_stream(hits_str);
      string cur_hit;
      while (getline(hit_stream, cur_hit, ';')) {
        if (!cur_hit.empty()) {
          istringstream hit_pair(cur_hit);
          int x, y;
          hit_pair >> x >> y;
          field_take_hit({x, y});
        }
      }
    }
  }
}

string Gamefield::full_gamefield_to_string() {
  string str_gamefield;
  for (int y = 0; y < field_height; y++) {
    for (int x = 0; x < field_width; x++) {
      if (field[y][x]->is_shipcell()) {
        str_gamefield += to_string(field[y][x]->get_shippart()->get_hp());
      } else if (field[y][x]->is_hit()) {
        str_gamefield += "X";
      } else {
        str_gamefield += "_";
      }
      str_gamefield += " ";
    }
    str_gamefield += "\n";
  }
  return str_gamefield;
}