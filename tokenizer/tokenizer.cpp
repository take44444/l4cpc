#include "./tokenizer.hpp"

namespace tokenizer {
  std::string to_string(TokenType type) {
    switch (type)
    {
      case Delimiter:
        return "Delimiter";
      case Punctuator:
        return "Punctuator";
      case NumberConstant:
        return "NumberConstant";
      case StringLiteral:
        return "StringLiteral";
      case Ident:
        return "Ident";
      case KwArray:
        return "KwArray";
      case KwBreak:
        return "KwBreak";
      case KwChar:
        return "KwChar";
      case KwContinue:
        return "KwContinue";
      case KwElif:
        return "KwElif";
      case KwElse:
        return "KwElse";
      case KwFunc:
        return "KwFunc";
      case KwFuncptr:
        return "KwFuncptr";
      case KwIf:
        return "KwIf";
      case KwLoop:
        return "KwLoop";
      case KwNullptr:
        return "KwNullptr";
      case KwNum:
        return "KwNum";
      case KwPtr:
        return "KwPtr";
      case KwReturn:
        return "KwReturn";
      case KwStruct:
        return "KwStruct";
      case Unknown:
        return "Unknown";
      default:
        return "????";
    }
  }

  std::string to_ast_string(TokenType type) {
    switch (type)
    {
      case Punctuator:
        return "punctuator";
      case NumberConstant:
        return "number-constant";
      case StringLiteral:
        return "string-literal";
      case Ident:
        return "identifier";
      case KwArray:
        return "type-specifier";
      case KwBreak:
        return "break-statement";
      case KwChar:
        return "type-specifier";
      case KwContinue:
        return "continue-statement";
      case KwElif:
        return "statement";
      case KwElse:
        return "else-statement";
      case KwFunc:
        return "external-declaration";
      case KwFuncptr:
        return "type-specifier";
      case KwIf:
        return "if-statement";
      case KwLoop:
        return "loop-statement";
      case KwNullptr:
        return "nullptr";
      case KwNum:
        return "type-specifier";
      case KwPtr:
        return "type-specifier";
      case KwReturn:
        return "return-statement";
      case KwStruct:
        return "type-specifier";
      default:
        return "unknown";
    }
  }

  Token *create_next_token_sub(char *src, char *p, int &line, bool is_indent) {
    assert(line);
    if (!*p) return NULL;
    if ('0' <= *p && *p <= '9') {
      int len = 0;
      while ('0' <= p[len] && p[len] <= '9') len++;
      return new Token(line, src, p, len, NumberConstant);
    }
    if (('A' <= *p && *p <= 'Z') || ('a' <= *p && *p <= 'z') || *p == '_') {
      int len = 0;
      while (('A' <= p[len] && p[len] <= 'Z') ||
             ('a' <= p[len] && p[len] <= 'z') || p[len] == '_' ||
             ('0' <= p[len] && p[len] <= '9')) len++;
      Token *ret = new Token(line, src, p, len, Ident);
      if (ret->sv == "array") ret->type = KwArray;            // array
      // else if (ret->sv == "break") ret->type = KwBreak;       // break
      else if (ret->sv == "char") ret->type = KwChar;         // char
      // else if (ret->sv == "continue") ret->type = KwContinue; // continue
      else if (ret->sv == "elif") ret->type = KwElif;         // elif
      else if (ret->sv == "else") ret->type = KwElse;         // else
      else if (ret->sv == "func") ret->type = KwFunc;         // func
      else if (ret->sv == "funcptr") ret->type = KwFuncptr;   // funcptr
      else if (ret->sv == "if") ret->type = KwIf;             // if
      // else if (ret->sv == "loop") ret->type = KwLoop;         // loop
      // else if (ret->sv == "nullptr") ret->type = KwNullptr;   // nullptr
      else if (ret->sv == "num") ret->type = KwNum;           // num
      else if (ret->sv == "ptr") ret->type = KwPtr;           // ptr
      else if (ret->sv == "return") ret->type = KwReturn;     // return
      else if (ret->sv == "struct") ret->type = KwStruct;     // struct
      return ret;
    }
    if ('"' == *p) {
      int len = 1;
      while (p[len] && p[len] != '"') len++;
      if (p[len] != '"') return new Token(line, src, p, len, Unknown);
      return new Token(line, src, p, ++len, StringLiteral);
    }
    // if ('!' == *p && p[1] == '=') {
    //   return new Token(line, src, p, 2, Punctuator);                         // !=
    // }
    if ('&' == *p) {
      // if (p[1] == '&') return new Token(line, src, p, 2, Punctuator);        // &&
      return new Token(line, src, p, 1, Punctuator);                         // &
    }
    // if ('|' == *p) {
    //   if (p[1] == '|') return new Token(line, src, p, 2, Punctuator);        // ||
    //   return new Token(line, src, p, 2, Punctuator);                         // |
    // }
    // if ('<' == *p) {
    //   if (p[1] == '=') return new Token(line, src, p, 2, Punctuator);        // <=
    //   return new Token(line, src, p, 1, Punctuator);                         // <
    // }
    // if ('>' == *p) {
    //   if (p[1] == '=') return new Token(line, src, p, 2, Punctuator);        // >=
    //   return new Token(line, src, p, 1, Punctuator);                         // >
    // }
    if ('-' == *p) {
      if (p[1] == '>') return new Token(line, src, p, 2, Punctuator);        // ->
      return new Token(line, src, p, 1, Punctuator);                         // -
    }
    if ('\r' == *p) {
      return new Token(line, src, p, 1, Delimiter);
    }
    if ('\n' == *p) {
      line++;
      if ('\n' == p[1]) return new Token(line-1, src, p, 1, Delimiter);
      return new Token(line-1, src, p, 1, Punctuator);
    }
    if (' ' == *p) {
      if (!is_indent) return new Token(line, src, p, 1, Delimiter);
      int len = 0;
      while (' ' == p[len]) {
        if (' ' == p[++len]) len++;
        else return new Token(line, src, p, len, Unknown);
      }
      return new Token(line, src, p, len, Punctuator);
    }
    if (':' == *p ||
        // '^' == *p || '~' == *p || '=' == *p ||
        '+' == *p ||
        // '/' == *p || '*' == *p || '%' == *p ||
        '(' == *p || ')' == *p ||
        '[' == *p || ']' == *p || '.' == *p ||
        ',' == *p) {
      return new Token(line, src, p, 1, Punctuator);
    }
    return new Token(line, src, p, 1, Unknown);
  }

  Token *create_next_token(char *src, char *p, int &line) {
    static bool is_indent = true;
    Token *ret = create_next_token_sub(src, p, line, is_indent);
    is_indent = ret != NULL &&
                ret->sv == "\n" && ret->type == Punctuator;
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