#include "Tokenizer.h"
#include "utils/check.h"
#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

const std::vector<std::string> datatypes = {"int", "float"};

void Tokenizer::tokenize(const std::string &s) {
  int len = s.length();
  std::string tmp = "";

  for (int i = 0; i < len; i++) {
    char c = s.at(i);
    bool binop = Utils::is_binop(c);

    if (c == ' ') {
      this->process_tokens(tmp);
      tmp = "";
      continue;
    } else if (binop) {
      if (!tmp.empty()) {
        this->process_tokens(tmp);
      }
      std::string k(1, c);
      this->m_tokens.emplace_back(
          Token{.type = TokenType::BinaryOp, .value = k});
      tmp = "";
      continue;
    } else if (c == ':') {
      if (!tmp.empty()) {
        this->process_tokens(tmp);
      }
      this->m_tokens.emplace_back(Token{.type = TokenType::Colan});
      tmp = "";
      continue;
    } else if (Utils::contains(datatypes, tmp)) {
      this->process_tokens(tmp);
      tmp = c;
      continue;
    } else if (c == '=') {
      this->m_tokens.emplace_back(Token{.type = TokenType::Eq});
      continue;
    } else if (c == ';') {
      this->m_tokens.emplace_back(Token{.type = TokenType::SemiColan});
      continue;
    }

    tmp += c;
  }

  if (!tmp.empty()) {
    this->process_tokens(tmp);
  }
}

void Tokenizer::process_tokens(std::string &str) {
  if (str.empty() && str == " ") {
    return;
  } else if (str == "let") {
    this->m_tokens.emplace_back(Token{.type = TokenType::Let});
  } else if (str == "mut") {
    this->m_tokens.emplace_back(Token{.type = TokenType::Mut});
  } else if (Utils::contains(datatypes, str)) {
    this->m_tokens.emplace_back(
        Token{.type = TokenType::DataType, .value = str});
  } else {
    try {
      float num = std::stof(str);

      this->m_tokens.emplace_back(
          Token{.type = TokenType::Numeric, .value = str});
    } catch (std::invalid_argument &_) {
      this->m_tokens.emplace_back(
          Token{.type = TokenType::StringLiteral, .value = str});
    }
  }
}
