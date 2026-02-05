//
// Created by homie on 19.12.24.
//

#ifndef NAVAL_WARFARE_EXCEPTIONS_COMMAND_INPUT_ERROR_H_
#define NAVAL_WARFARE_EXCEPTIONS_COMMAND_INPUT_ERROR_H_

#include <exception>
#include <string>

class Command_input_error: public std::exception
{
 public:
  Command_input_error(const std::string& message);
  const char* what() const noexcept override;
 private:
  std::string message;
};

#endif //NAVAL_WARFARE_EXCEPTIONS_COMMAND_INPUT_ERROR_H_
