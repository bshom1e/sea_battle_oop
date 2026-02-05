//
// Created by homie on 19.12.24.
//

#ifndef NAVAL_WARFARE_EXCEPTIONS_OUT_OF_BOUND_H_
#define NAVAL_WARFARE_EXCEPTIONS_OUT_OF_BOUND_H_

#include <exception>
#include <string>

class Out_of_bound: public std::exception
{
 public:
  Out_of_bound(const std::string& message);
  const char* what() const noexcept override;
 private:
  std::string message;
};

#endif //NAVAL_WARFARE_EXCEPTIONS_OUT_OF_BOUND_H_
