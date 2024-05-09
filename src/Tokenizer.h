#pragma once
#include <cstdio>
#include <string>
#include <vector>

enum TokenType {
  Numeric,
  StringLiteral,
  BinaryOp,
  Let,
  Mut,
  Eq,
  SemiColan,
  Colan,
  DataType
};

struct Token {
  TokenType type;
  std::string value;

  void fmt_print() {
    switch (this->type) {
    case TokenType::Numeric:
      printf("[Numeric: %s]\n", this->value.c_str());
      break;
    case TokenType::StringLiteral:
      printf("[StringLiteral: %s]\n", this->value.c_str());
      break;
    case TokenType::BinaryOp:
      printf("[BinaryOp: %s]\n", this->value.c_str());
      break;
    case TokenType::Let:
      printf("[Let]\n");
      break;
    case TokenType::Mut:
      printf("[Mut]\n");
      break;
    case TokenType::Eq:
      printf("[Eq]\n");
      break;
    case TokenType::SemiColan:
      printf("[SemiColan]\n");
      break;
    case TokenType::Colan:
      printf("[Colan]\n");
      break;
    case TokenType::DataType:
      printf("[DataType: %s]\n", this->value.data());
      break;
    }
  }
};

class Tokenizer {
public:
  void tokenize(const std::string &s);
  std::vector<Token> getTokens() { return this->m_tokens; }

private:
  void process_tokens(std::string &str);

  std::vector<Token> m_tokens = {};
};
