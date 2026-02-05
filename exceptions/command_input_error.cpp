#include "command_input_error.h"

#include <exception>
#include <string>

Command_input_error::Command_input_error(const std::string &message) : message{message} {}

const char* Command_input_error::what() const noexcept {
  return message.c_str();
}
