#include "Tokenizer.h"
#include "utils/check.h"
#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

const std::vector<std::string> datatypes = {"int", "float"};

void Tokenizer::tokenize(const std::string &s) {
  std::string tmp = "";
  
  for (int i = 0; i < s.length(); i++) {
     char c = s.at(i);
     bool binop = Utils::is_binop(c);

     if (c == ' ' || binop || c == ':' || c == '=' || c == ';') {
       if (!tmp.empty()) {
        this->process_tokens(tmp);
        tmp = "";
      }

      if (binop) {
        this->m_tokens.emplace_back(Token{.type = TokenType::BinaryOp, .value = std::string(1, c)});
      } else if (c == ':') {
        this->m_tokens.emplace_back(Token{.type = TokenType::Colon});
      } else if (c == '=') {
        this->m_tokens.emplace_back(Token{.type = TokenType::Eq});
      } else if (c == ';') {
        this->m_tokens.emplace_back(Token{.type = TokenType::SemiColon});
      }
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
