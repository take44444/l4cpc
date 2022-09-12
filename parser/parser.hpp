#ifndef PARSER_HPP
#define PARSER_HPP
#include "bits/stdc++.h"
#include "../tokenizer/tokenizer.hpp"

namespace generator {
  class EvalType;
}

namespace parser {
  using namespace tokenizer;
  using namespace generator;
  class PError {
    public:
    Token *token;
    std::string message;
    explicit PError(std::string expected, std::string found, Token *t) : token(t) {
      message = "error: expected " + expected + ", found " + found;
    }
    std::string get_error_string() {
      if (!token) return message;
      std::string ret = "line:" + std::to_string(token->line) +
                        "/pos:" + std::to_string(token->pos) +
                        ": " + message + '\n';
      for (char *p = token->line_begin; *p && *p != '\n'; ret += *p++);
      ret += '\n';
      for (int i_ = 1; i_ < (int)token->pos; i_++) ret += ' ';
      ret += '^';
      for (int i_ = 1; i_ < (int)token->sv.length(); i_++) ret += '~';
      return ret;
    }
  };

  class AST {
    public:
    virtual ~AST() = default;
  };

  class ASTTypeSpec : public AST {
    public:
    Token *op;
    std::shared_ptr<ASTTypeSpec> of;
    int size;
    std::vector<std::shared_ptr<ASTTypeSpec>> args;
    std::shared_ptr<ASTTypeSpec> type_spec;
    Token *s;
    ASTTypeSpec(Token *t) : AST(), op(t) {
      of = nullptr;
      type_spec = nullptr;
      size = 0;
    }
  };

  class ASTExpr : public AST {
    public:
    std::shared_ptr<ASTExpr> left, right;
    std::shared_ptr<EvalType> eval_type;
    bool is_assignable;
    ASTExpr() : AST(), is_assignable(false) {}
  };

  class ASTSimpleExpr : public ASTExpr {
    public:
    Token *op;
    ASTSimpleExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTPrimaryExpr : public ASTExpr {
    public:
    std::shared_ptr<ASTExpr> expr;
    ASTPrimaryExpr() : ASTExpr() {}
  };

  class ASTUnaryExpr : public ASTExpr {
    public:
    Token *op;
    std::shared_ptr<ASTExpr> expr;
    ASTUnaryExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTFuncCallExpr : public ASTExpr {
    public:
    std::shared_ptr<ASTExpr> primary;
    std::vector<std::shared_ptr<ASTExpr>> args;
    Token *op;
    ASTFuncCallExpr(Token *t) : ASTExpr(), op(t) {
      args = std::vector<std::shared_ptr<ASTExpr>>();
    }
  };

  class ASTArrayAccessExpr : public ASTExpr {
    public:
    std::shared_ptr<ASTExpr> primary;
    std::shared_ptr<ASTExpr> expr;
    Token *op;
    ASTArrayAccessExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTStructAccessExpr : public ASTExpr {
    public:
    std::shared_ptr<ASTExpr> primary;
    Token *op;
    ASTStructAccessExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTMultiplicativeExpr : public ASTExpr {
    public:
    Token *op;
    ASTMultiplicativeExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTAdditiveExpr : public ASTExpr {
    public:
    Token *op;
    ASTAdditiveExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTShiftExpr : public ASTExpr {
    public:
    Token *op;
    ASTShiftExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTRelationalExpr : public ASTExpr {
    public:
    Token *op;
    ASTRelationalExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTEqualityExpr : public ASTExpr {
    public:
    Token *op;
    ASTEqualityExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTBitwiseAndExpr : public ASTExpr {
    public:
    ASTBitwiseAndExpr() : ASTExpr() {}
  };

  class ASTBitwiseXorExpr : public ASTExpr {
    public:
    ASTBitwiseXorExpr() : ASTExpr() {}
  };

  class ASTBitwiseOrExpr : public ASTExpr {
    public:
    ASTBitwiseOrExpr() : ASTExpr() {}
  };

  class ASTLogicalAndExpr : public ASTExpr {
    public:
    Token *op;
    ASTLogicalAndExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTLogicalOrExpr : public ASTExpr {
    public:
    Token *op;
    ASTLogicalOrExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTAssignExpr : public ASTExpr {
    public:
    Token *op;
    ASTAssignExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTExprStmt : public AST {
    public:
    std::shared_ptr<AST> expr;
    ASTExprStmt() : AST() {}
  };

  class ASTBreakStmt : public AST {
    public:
    Token *op;
    ASTBreakStmt(Token *t) : AST(), op(t) {}
  };

  class ASTContinueStmt : public AST {
    public:
    Token *op;
    ASTContinueStmt(Token *t) : AST(), op(t) {}
  };

  class ASTReturnStmt : public AST {
    public:
    Token *op;
    std::shared_ptr<AST> expr;
    ASTReturnStmt(Token *t) : AST(), op(t) {}
  };

  class ASTDeclarator : public AST {
    public:
    Token *op;
    ASTDeclarator(Token *t) : AST(), op(t) {}
  };

  class ASTDeclaration : public AST {
    public:
    std::shared_ptr<ASTTypeSpec> declaration_spec;
    std::vector<std::shared_ptr<ASTDeclarator>> declarators;
    ASTDeclaration() : AST() {
      declarators = std::vector<std::shared_ptr<ASTDeclarator>>();
    }
  };

  class ASTSimpleDeclaration : public AST {
    public:
    std::shared_ptr<ASTTypeSpec> type_spec;
    std::shared_ptr<ASTDeclarator> declarator;
    ASTSimpleDeclaration() : AST() {}
  };

  class ASTFfi : public AST {
    public:
    std::shared_ptr<ASTDeclarator> declarator;
    ASTFfi() : AST() {}
  };

  class ASTCompoundStmt : public AST {
    public:
    std::vector<std::shared_ptr<AST>> items;
    ASTCompoundStmt() : AST() {
      items = std::vector<std::shared_ptr<AST>>();
    }
  };

  class ASTElseStmt : public AST {
    public:
    std::shared_ptr<ASTExpr> cond;
    std::shared_ptr<ASTCompoundStmt> true_stmt;
    std::shared_ptr<ASTElseStmt> false_stmt;
    Token *op;
    ASTElseStmt(Token *t) : AST(), cond(nullptr), false_stmt(nullptr), op(t) {}
  };

  class ASTIfStmt : public AST {
    public:
    std::shared_ptr<ASTExpr> cond;
    std::shared_ptr<ASTCompoundStmt> true_stmt;
    std::shared_ptr<ASTElseStmt> false_stmt;
    Token *op;
    ASTIfStmt(Token *t) : AST(), cond(nullptr), false_stmt(nullptr), op(t) {}
  };

  class ASTLoopStmt : public AST {
    public:
    std::shared_ptr<ASTExpr> cond;
    std::shared_ptr<ASTCompoundStmt> true_stmt;
    Token *op;
    ASTLoopStmt(Token *t) : AST(), cond(nullptr), op(t) {}
  };

  class ASTFuncDeclarator : public AST {
    public:
    std::shared_ptr<ASTDeclarator> declarator;
    std::vector<std::shared_ptr<ASTSimpleDeclaration>> args;
    Token *op;
    ASTFuncDeclarator(Token *t) : AST(), op(t) {
      args = std::vector<std::shared_ptr<ASTSimpleDeclaration>>();
    }
  };

  class ASTFuncDeclaration : public AST {
    public:
    std::shared_ptr<ASTTypeSpec> type_spec;
    std::shared_ptr<ASTFuncDeclarator> declarator;
    ASTFuncDeclaration() : AST() {}
  };

  class ASTFuncDef : public AST {
    public:
    std::shared_ptr<ASTFuncDeclaration> declaration;
    std::shared_ptr<ASTCompoundStmt> body;
    ASTFuncDef() : AST() {}
  };

  class ASTStructDef : public AST {
    public:
    std::shared_ptr<ASTDeclarator> declarator;
    std::vector<std::shared_ptr<ASTSimpleDeclaration>> declarations;
    ASTStructDef() : AST() {
      declarations = std::vector<std::shared_ptr<ASTSimpleDeclaration>>();
    }
  };

  class ASTExternalDeclaration : public AST {
    public:
    std::shared_ptr<ASTTypeSpec> declaration_spec;
    std::vector<std::shared_ptr<ASTDeclarator>> declarators;
    ASTExternalDeclaration() : AST() {
      declarators = std::vector<std::shared_ptr<ASTDeclarator>>();
    }
  };

  class ASTTranslationUnit : public AST {
    public:
    std::vector<std::shared_ptr<AST>> external_declarations;
    ASTTranslationUnit() : AST() {
      external_declarations = std::vector<std::shared_ptr<AST>>();
    }
  };

  // parser.cpp
  std::shared_ptr<ASTTranslationUnit> parse(Token **head, PError &err);
  void print_ast(std::shared_ptr<AST> n);

  // utils.cpp
  Token *expect_token_with_str(Token **next, PError &err, std::string str);
  Token *consume_token_with_str(Token **next, std::string str);
  Token *expect_token_with_type(Token **next, PError &err, TokenType type);
  Token *consume_token_with_type(Token **next, TokenType type);
  Token *consume_token_with_indents(Token **next, int indents);
  Token *expect_token_with_indents(Token **next, PError &err, int indents);
}
#endif