#include "./tokenizer.hpp"

namespace tokenizer {
  std::string to_string(TokenType type) {
    switch (type)
    {
      case Delimiter:
        return "Delimiter";
      case I8Literal:
        return "I8Literal";
      case I64Constant:
        return "I64Constant";
      case Punctuator:
        return "Punctuator";
      case StringLiteral:
        return "StringLiteral";
      case Ident:
        return "Ident";
      case KwBreak:
        return "KwBreak";
      case KwContinue:
        return "KwContinue";
      case KwElif:
        return "KwElif";
      case KwElse:
        return "KwElse";
      case KwFn:
        return "KwFn";
      case KwI8:
        return "KwI8";
      case KwI64:
        return "KwI64";
      case KwIf:
        return "KwIf";
      case KwNil:
        return "KwNil";
      case KwRep:
        return "KwRep";
      case KwReturn:
        return "KwReturn";
      case KwSt:
        return "KwSt";
      case KwWhile:
        return "KwWhile";
      case Unknown:
        return "Unknown";
      default:
        return "????";
    }
  }

  std::string to_ast_string(TokenType type) {
    switch (type)
    {
      case I8Literal:
        return "i8-literal";
      case I64Constant:
        return "i64-constant";
      case Punctuator:
        return "punctuator";
      case StringLiteral:
        return "string-literal";
      case Ident:
        return "identifier";
      case KwBreak:
        return "break-statement";
      case KwContinue:
        return "continue-statement";
      case KwElif:
        return "elif-statement";
      case KwElse:
        return "else-statement";
      case KwFn:
        return "type-specifier";
      case KwI8:
        return "type-specifier";
      case KwI64:
        return "type-specifier";
      case KwIf:
        return "if-statement";
      case KwNil:
        return "nil";
      case KwRep:
        return "rep-statement";
      case KwReturn:
        return "return-statement";
      case KwSt:
        return "type-specifier";
      case KwWhile:
        return "while-statement";
      default:
        return "unknown";
    }
  }

  Token *create_next_token_sub(char *src, char *p, int &line) {
    assert(line);
    if (!*p) return NULL;
    if ('0' <= *p && *p <= '9') {
      int len = 0;
      while ('0' <= p[len] && p[len] <= '9') len++;
      return new Token(line, src, p, len, I64Constant);
    }
    if (('A' <= *p && *p <= 'Z') || ('a' <= *p && *p <= 'z') || *p == '_') {
      int len = 0;
      while (('A' <= p[len] && p[len] <= 'Z') ||
             ('a' <= p[len] && p[len] <= 'z') || p[len] == '_' ||
             ('0' <= p[len] && p[len] <= '9')) len++;
      Token *ret = new Token(line, src, p, len, Ident);
      if (ret->sv == "break") ret->type = KwBreak;            // break
      else if (ret->sv == "continue") ret->type = KwContinue; // continue
      else if (ret->sv == "elif") ret->type = KwElif;         // elif
      else if (ret->sv == "else") ret->type = KwElse;         // else
      else if (ret->sv == "fn") ret->type = KwFn;             // fn
      else if (ret->sv == "i8") ret->type = KwI8;             // i8
      else if (ret->sv == "i64") ret->type = KwI64;           // i64
      else if (ret->sv == "if") ret->type = KwIf;             // if
      else if (ret->sv == "nil") ret->type = KwNil;           // nil
      else if (ret->sv == "rep") ret->type = KwRep;           // rep
      else if (ret->sv == "return") ret->type = KwReturn;     // return
      else if (ret->sv == "st") ret->type = KwSt;             // st
      else if (ret->sv == "while") ret->type = KwWhile;       // while
      return ret;
    }
    if ('"' == *p) {
      int len = 1;
      while (p[len] && p[len] != '"') len++;
      if (p[len] != '"') return new Token(line, src, p, len, Unknown);
      return new Token(line, src, p, ++len, StringLiteral);
    }
    if ('!' == *p && p[1] == '=') {
      return new Token(line, src, p, 2, Punctuator);                         // !=
    }
    if ('&' == *p && p[1] == '&') {
      if (p[1] == '&') return new Token(line, src, p, 2, Punctuator);        // &&
    }
    if ('|' == *p) {
      if (p[1] == '|') return new Token(line, src, p, 2, Punctuator);        // ||
    }
    if ('<' == *p) {
      if (p[1] == '=') return new Token(line, src, p, 2, Punctuator);        // <=
      return new Token(line, src, p, 1, Punctuator);                         // <
    }
    if ('>' == *p) {
      if (p[1] == '=') return new Token(line, src, p, 2, Punctuator);        // >=
      return new Token(line, src, p, 1, Punctuator);                         // >
    }
    if ('-' == *p && p[1] == '>') {
      return new Token(line, src, p, 2, Punctuator);                         // ->
    }
    if ('\n' == *p) {
      line++;
      return new Token(line-1, src, p, 1, Delimiter);
    }
    if (' ' == *p || '\r' == *p) {
      return new Token(line, src, p, 1, Delimiter);
    }
    if (':' == *p || ';' == *p ||
        '{' == *p || '}' == *p ||
        // '^' == *p || '~' == *p ||
        '=' == *p || '!' == *p ||
        '+' == *p || '-' == *p ||
        '/' == *p || '*' == *p || '%' == *p ||
        '(' == *p || ')' == *p ||
        '[' == *p || ']' == *p || '.' == *p ||
        ',' == *p) {
      return new Token(line, src, p, 1, Punctuator);
    }
    return new Token(line, src, p, 1, Unknown);
  }

  Token *create_next_token(char *src, char *p, int &line) {
    Token *ret = create_next_token_sub(src, p, line);
    return ret;
  }

  void print_tokens(Token *head) {
    for (Token *next = head; next != NULL; next = next->next) {
      std::cerr << "code: ";
      if (next->sv.front() == ' ')
        std::cerr << next->sv.length() << " spaces ";
      else if (next->sv == "\n")
        std::cerr << "LF ";
      else
        std::cerr << next->sv << " ";
      std::cerr << "type: " << to_string(next->type) << std::endl;      
    }
  }

  Token *tokenize(std::string &source) {
    Token *head = NULL;
    Token **next = &head;
    int l = 1;
    char *p = &source[0];
    for (Token *t=create_next_token(&source[0], p, l);t!=NULL;) {
      *next = t;
      next = &t->next;
      p += t->sv.length();
      t = create_next_token(&source[0], p, l);
    }
    return head;
  }
}