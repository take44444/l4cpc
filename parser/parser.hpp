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
    std::vector<std::shared_ptr<ASTTypeSpec>> templates;
    std::vector<std::shared_ptr<ASTTypeSpec>> args;
    std::shared_ptr<ASTTypeSpec> ret_type;
    ASTTypeSpec(Token *t) : AST(), op(t) {
      templates = std::vector<std::shared_ptr<ASTTypeSpec>>();
      ret_type = nullptr;
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

  class ASTFnCallExpr : public ASTExpr {
    public:
    std::shared_ptr<ASTExpr> p;
    std::vector<std::shared_ptr<ASTTypeSpec>> templates;
    std::vector<std::shared_ptr<ASTExpr>> args;
    Token *op;
    ASTFnCallExpr(Token *t) : ASTExpr(), op(t) {
      templates = std::vector<std::shared_ptr<ASTTypeSpec>>();
      args = std::vector<std::shared_ptr<ASTExpr>>();
    }
  };

  class ASTIndexAccessExpr : public ASTExpr {
    public:
    std::shared_ptr<ASTExpr> p;
    std::shared_ptr<ASTExpr> expr;
    Token *op;
    ASTIndexAccessExpr(Token *t) : ASTExpr(), op(t) {}
  };

  class ASTStAccessExpr : public ASTExpr {
    public:
    std::shared_ptr<ASTExpr> p;
    Token *op;
    ASTStAccessExpr(Token *t) : ASTExpr(), op(t) {}
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
    std::shared_ptr<ASTTypeSpec> dtion_spec;
    std::vector<std::shared_ptr<ASTDeclarator>> dtors;
    ASTDeclaration() : AST() {
      dtors = std::vector<std::shared_ptr<ASTDeclarator>>();
    }
  };

  class ASTSimpleDeclaration : public AST {
    public:
    std::shared_ptr<ASTTypeSpec> type_spec;
    std::shared_ptr<ASTDeclarator> dtor;
    ASTSimpleDeclaration() : AST() {}
  };

  class ASTCompoundStmt : public AST {
    public:
    std::vector<std::shared_ptr<AST>> items;
    Token *op;
    ASTCompoundStmt(Token *t) : AST(), op(t) {
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

  class ASTWhileStmt : public AST {
    public:
    std::shared_ptr<ASTExpr> cond;
    std::shared_ptr<ASTCompoundStmt> body;
    Token *op;
    ASTWhileStmt(Token *t) : AST(), cond(nullptr), op(t) {}
  };

  class ASTFnDeclarator : public AST {
    public:
    std::shared_ptr<ASTDeclarator> dtor;
    std::vector<std::shared_ptr<ASTDeclarator>> templates;
    std::vector<std::shared_ptr<ASTSimpleDeclaration>> args;
    Token *op;
    ASTFnDeclarator(Token *t) : AST(), op(t) {
      templates = std::vector<std::shared_ptr<ASTDeclarator>>();
      args = std::vector<std::shared_ptr<ASTSimpleDeclaration>>();
    }
  };

  class ASTFnDeclaration : public AST {
    public:
    std::shared_ptr<ASTTypeSpec> ret_type;
    std::shared_ptr<ASTFnDeclarator> dtor;
    ASTFnDeclaration() : AST() {
      ret_type = nullptr;
    }
  };

  class ASTFnDef : public AST {
    public:
    std::shared_ptr<ASTFnDeclaration> dtion;
    std::shared_ptr<ASTCompoundStmt> body;
    ASTFnDef() : AST() {}
  };

  class ASTMethodDef : public AST {
    public:
    std::shared_ptr<ASTFnDeclaration> dtion;
    std::shared_ptr<ASTCompoundStmt> body;
    ASTMethodDef() : AST() {}
  };

  class ASTStDef : public AST {
    public:
    std::shared_ptr<ASTDeclarator> dtor;
    std::vector<std::shared_ptr<ASTDeclarator>> templates;
    std::vector<std::shared_ptr<ASTSimpleDeclaration>> dtions;
    std::vector<std::shared_ptr<ASTMethodDef>> methods;
    ASTStDef() : AST() {
      templates = std::vector<std::shared_ptr<ASTDeclarator>>();
      dtions = std::vector<std::shared_ptr<ASTSimpleDeclaration>>();
    }
  };

  class ASTExternalDeclaration : public AST {
    public:
    std::shared_ptr<ASTTypeSpec> dtion_spec;
    std::vector<std::shared_ptr<ASTDeclarator>> dtors;
    ASTExternalDeclaration() : AST() {
      dtors = std::vector<std::shared_ptr<ASTDeclarator>>();
    }
  };

  class ASTTranslationUnit : public AST {
    public:
    std::vector<std::shared_ptr<AST>> external_dtions;
    ASTTranslationUnit() : AST() {
      external_dtions = std::vector<std::shared_ptr<AST>>();
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