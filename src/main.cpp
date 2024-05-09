#include <cstdio>
#include <vector>

#include "Tokenizer.h"
#include "repl.h"

class PointRepl : public Repl {
private:
  void on_command_entered(const std::string &curr_prompt) override {
    if (curr_prompt.empty() || curr_prompt == " ") {
      return;
    }
    Tokenizer tok;
    tok.tokenize(curr_prompt);
    for (Token tkn : tok.getTokens()) {
      tkn.fmt_print();
      this->m_tokens.emplace_back(tkn);
    }
  }

  std::vector<Token> m_tokens = {};
};

int main(int argc, char *argv[]) {
  std::string app_name = "Point Repl";
  std::string version = "1.0";

  PointRepl repl;
  repl.repl_start();

  return 0;
}
