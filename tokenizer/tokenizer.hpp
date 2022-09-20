#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "bits/stdc++.h"

namespace tokenizer {
  enum TokenType {
    Delimiter,      // space
    I8Literal,      // 'a'
    I64Constant,    // 0 3 0x07 0b10
    Punctuator,     // , ( ) + { } -> = > & * | && || :
    StringLiteral,  // "hello world"
    Ident,          // vAr_n4m3
    KwBreak,        // break
    KwContinue,     // continue
    KwElif,         // elif
    KwElse,         // else
    KwFn,           // fn
    KwI8,           // i8
    KwI64,          // i64
    KwIf,           // if
    KwNil,          // nil
    KwRep,          // rep
    KwReturn,       // return
    KwSt,           // st
    KwWhile,        // while
    // Unexpected Token
    Unknown,        // unknown
  };

  std::string to_string(TokenType type);
  std::string to_ast_string(TokenType type);

  class Token {
    public:
    int line;
    enum TokenType type;
    Token *next;
    std::string_view sv;
    char *line_begin;
    int pos;
    Token(int l, char *src, char *beg, int len, enum TokenType tp)
    : line(l), type(tp), next(NULL) {
      sv = std::string_view(beg).substr(0, len);
      for (
        line_begin = beg;
        src < line_begin && line_begin[-1] != '\n';
        line_begin--
      );
      for (pos = 0; line_begin + pos <= beg; pos++);
    }
  };

  // tokenizer.cpp
  void print_tokens(Token *head);
  Token *tokenize(std::string &source);
}
#endif