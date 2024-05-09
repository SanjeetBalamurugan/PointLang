#pragma once

#include <algorithm>
#include <cstdio>
#include <string>

class Repl {
public:
  Repl() = default;

  std::string get_application_name() const { return this->m_application_name; }
  char get_prompt_char() const { return this->m_prompt_char; }
  std::string get_version() const { return this->m_version; }

  virtual void on_command_entered(const std::string &curr_prompt) = 0;
  void repl_start();

  virtual ~Repl(){};

protected:
  std::string m_application_name = "Repl";
  char m_prompt_char = '>';
  std::string m_version = "1.0";
};
