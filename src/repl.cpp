#include "repl.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

void Repl::repl_start() {
  printf("%s %s:\n", this->m_application_name.data(), this->m_version.data());
  while (true) {
    printf("%c ", this->m_prompt_char);
    std::string prompt = "";
    std::getline(std::cin, prompt);

    if (!prompt.empty()) {
      on_command_entered(prompt);
    }
    else {
      continue;
    }
    printf("\n");
  }
}
