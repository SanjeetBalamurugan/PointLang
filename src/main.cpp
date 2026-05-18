#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>

#include "Tokenizer.h"
#include "repl.h"

void ParseTokens(std::vector<Token>& Tokens, const std::string& line, const bool isFMT) {
  Tokenizer tok;
  tok.tokenize(line);
  for (Token tkn : tok.getTokens()) {
    if (isFMT) tkn.fmt_print();
    Tokens.emplace_back(tkn);
  }
}

class PointRepl : public Repl {
private:
  void on_command_entered(const std::string &curr_prompt) override {
    if (curr_prompt.empty() || curr_prompt == " ") {
      return;
    }
    ParseTokens(this->m_tokens, curr_prompt, true);
  }

  std::vector<Token> m_tokens = {};
};

void RunPointFile(std::vector<Token>& Tokens, char* argv[]) {
  const char* file_path = argv[1];
  std::ifstream file_stream(file_path);
  std::string line = "";
  std::vector<std::string> lines = {};

  while (getline(file_stream, line)) {
    lines.emplace_back(line);
  }

  file_stream.close();
  for (auto l:lines) {
    ParseTokens(Tokens, l, true);
  }
}

int main(int argc, char *argv[]) {
  std::string app_name = "Point Repl";
  std::string version = "1.0";

  std::vector<Token> progTokens = {};

  if (argc > 1) {
    RunPointFile(progTokens, argv);
  } else {
    PointRepl repl;
    repl.repl_start();
  }

  return 0;
}
