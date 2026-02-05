#include "out_of_bound.h"

Out_of_bound::Out_of_bound(const std::string& message): message{message} {}

const char* Out_of_bound::what() const noexcept {
  return message.c_str();
}
