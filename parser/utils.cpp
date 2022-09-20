#include "./parser.hpp"

namespace parser {
  tokenizer::Token *expect_token_with_str(tokenizer::Token **next, PError &err, std::string str) {
    if (!*next) {
      err = PError(str, "EOF", *next);
      return NULL;
    }
    if ((*next)->sv != str) {
      err = PError(str, std::string((*next)->sv), *next);
      return NULL;
    }
    tokenizer::Token *ret = *next;
    *next = (*next)->next;
    return ret;
  }

  tokenizer::Token *consume_token_with_str(tokenizer::Token **next, std::string str) {
    if (!*next) return NULL;
    if ((*next)->sv != str) return NULL;
    tokenizer::Token *ret = *next;
    *next = (*next)->next;
    return ret;
  }

  tokenizer::Token *expect_token_with_type(tokenizer::Token **next, PError &err, tokenizer::TokenType type) {
    if (!*next) {
      err = PError("type " + tokenizer::to_ast_string(type), "EOF", *next);
      return NULL;
    }
    if ((*next)->type != type) {
      err = PError(
        "type " + tokenizer::to_ast_string(type),
        "type " + tokenizer::to_ast_string((*next)->type), *next
      );
      return NULL;
    }
    tokenizer::Token *ret = *next;
    *next = (*next)->next;
    return ret;
  }

  tokenizer::Token *consume_token_with_type(tokenizer::Token **next, tokenizer::TokenType type) {
    if (!*next) return NULL;
    if ((*next)->type != type) return NULL;
    tokenizer::Token *ret = *next;
    *next = (*next)->next;
    return ret;
  }

  template <class T> void print_ast_vec(std::vector<std::shared_ptr<T>> &v, int depth) {
    std::cerr << '[';
    if (v.size() == 0) {
      std::cerr << ']';
      return;
    }
    for (int i=0; i < (int)v.size(); i++) {
      std::cerr << (i ? ",\n" : "\n");
      for (int j_ = 0; j_ < depth + 1; j_++) std::cerr << ' ';
      print_ast_sub(v.at(i), depth + 1);
    }
    std::cerr << std::endl;
    for (int i_ = 0; i_ < depth; i_++) std::cerr << ' ';
    std::cerr << ']';
  }

  void print_ast_sub(std::shared_ptr<AST> n, int depth) {
    if (!n) return;
    if (typeid(*n) == typeid(ASTTypeSpec)) {
      std::shared_ptr<ASTTypeSpec> nn = std::dynamic_pointer_cast<ASTTypeSpec>(n);
      std::cerr << "TypeSpec<" << nn->op->sv << '>';
      return;
    }
    if (typeid(*n) == typeid(ASTSimpleExpr)) {
      std::shared_ptr<ASTSimpleExpr> nn = std::dynamic_pointer_cast<ASTSimpleExpr>(n);
      std::cerr << "SimpleExpr<" << nn->op->sv << '>';
      return;
    }
    if (typeid(*n) == typeid(ASTPrimaryExpr)) {
      std::shared_ptr<ASTPrimaryExpr> nn = std::dynamic_pointer_cast<ASTPrimaryExpr>(n);
      std::cerr << "PrimaryExpr(e=";
      print_ast_sub(nn->expr, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTIndexAccessExpr)) {
      std::shared_ptr<ASTIndexAccessExpr> nn = std::dynamic_pointer_cast<ASTIndexAccessExpr>(n);
      std::cerr << "IndexAccessExpr(p=";
      print_ast_sub(nn->p, depth);
      std::cerr << ", e=";
      print_ast_sub(nn->expr, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTStAccessExpr)) {
      std::shared_ptr<ASTStAccessExpr> nn = std::dynamic_pointer_cast<ASTStAccessExpr>(n);
      std::cerr << "StAccessExpr<" << nn->op->sv << '>';
      std::cerr << "(p=";
      print_ast_sub(nn->p, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTFnCallExpr)) {
      std::shared_ptr<ASTFnCallExpr> nn = std::dynamic_pointer_cast<ASTFnCallExpr>(n);
      std::cerr << "FnCallExpr(p=";
      print_ast_sub(nn->p, depth);
      std::cerr << ", templates=";
      print_ast_vec(nn->templates, depth);
      std::cerr << ", args=";
      print_ast_vec(nn->args, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTMultiplicativeExpr)) {
      std::shared_ptr<ASTMultiplicativeExpr> nn = std::dynamic_pointer_cast<ASTMultiplicativeExpr>(n);
      std::cerr << "MultiplicativeExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTAdditiveExpr)) {
      std::shared_ptr<ASTAdditiveExpr> nn = std::dynamic_pointer_cast<ASTAdditiveExpr>(n);
      std::cerr << "AdditiveExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTShiftExpr)) {
      std::shared_ptr<ASTShiftExpr> nn = std::dynamic_pointer_cast<ASTShiftExpr>(n);
      std::cerr << "ShiftExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTRelationalExpr)) {
      std::shared_ptr<ASTRelationalExpr> nn = std::dynamic_pointer_cast<ASTRelationalExpr>(n);
      std::cerr << "RelationalExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTEqualityExpr)) {
      std::shared_ptr<ASTEqualityExpr> nn = std::dynamic_pointer_cast<ASTEqualityExpr>(n);
      std::cerr << "EqualityExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTBitwiseAndExpr)) {
      std::shared_ptr<ASTBitwiseAndExpr> nn = std::dynamic_pointer_cast<ASTBitwiseAndExpr>(n);
      std::cerr << "BitwiseAndExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTBitwiseXorExpr)) {
      std::shared_ptr<ASTBitwiseXorExpr> nn = std::dynamic_pointer_cast<ASTBitwiseXorExpr>(n);
      std::cerr << "BitwiseXorExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTBitwiseOrExpr)) {
      std::shared_ptr<ASTBitwiseOrExpr> nn = std::dynamic_pointer_cast<ASTBitwiseOrExpr>(n);
      std::cerr << "BitwiseOrExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTLogicalAndExpr)) {
      std::shared_ptr<ASTLogicalAndExpr> nn = std::dynamic_pointer_cast<ASTLogicalAndExpr>(n);
      std::cerr << "LogicalAndExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTLogicalOrExpr)) {
      std::shared_ptr<ASTLogicalOrExpr> nn = std::dynamic_pointer_cast<ASTLogicalOrExpr>(n);
      std::cerr << "LogicalOrExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTAssignExpr)) {
      std::shared_ptr<ASTAssignExpr> nn = std::dynamic_pointer_cast<ASTAssignExpr>(n);
      std::cerr << "AssignExpr(l=";
      print_ast_sub(nn->left, depth);
      std::cerr << ", r=";
      print_ast_sub(nn->right, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTExprStmt)) {
      std::shared_ptr<ASTExprStmt> nn = std::dynamic_pointer_cast<ASTExprStmt>(n);
      std::cerr << "ExprStmt(e=";
      print_ast_sub(nn->expr, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTBreakStmt)) {
      std::shared_ptr<ASTBreakStmt> nn = std::dynamic_pointer_cast<ASTBreakStmt>(n);
      std::cerr << "BreakStmt";
      return;
    }
    if (typeid(*n) == typeid(ASTContinueStmt)) {
      std::shared_ptr<ASTContinueStmt> nn = std::dynamic_pointer_cast<ASTContinueStmt>(n);
      std::cerr << "ContinueStmt";
      return;
    }
    if (typeid(*n) == typeid(ASTReturnStmt)) {
      std::shared_ptr<ASTReturnStmt> nn = std::dynamic_pointer_cast<ASTReturnStmt>(n);
      std::cerr << "ReturnStmt(e=";
      print_ast_sub(nn->expr, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTDeclarator)) {
      std::shared_ptr<ASTDeclarator> nn = std::dynamic_pointer_cast<ASTDeclarator>(n);
      std::cerr << "Declarator<" << nn->op->sv << '>';
      return;
    }
    if (typeid(*n) == typeid(ASTDeclaration)) {
      std::shared_ptr<ASTDeclaration> nn = std::dynamic_pointer_cast<ASTDeclaration>(n);
      std::cerr << "Declaration(ds=";
      print_ast_sub(nn->dtion_spec, depth);
      std::cerr << ", dtors=";
      print_ast_vec(nn->dtors, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTSimpleDeclaration)) {
      std::shared_ptr<ASTSimpleDeclaration> nn = std::dynamic_pointer_cast<ASTSimpleDeclaration>(n);
      std::cerr << "SimpleDeclaration(ts=";
      print_ast_sub(nn->type_spec, depth);
      std::cerr << ", dtor=";
      print_ast_sub(nn->dtor, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTCompoundStmt)) {
      std::shared_ptr<ASTCompoundStmt> nn = std::dynamic_pointer_cast<ASTCompoundStmt>(n);
      std::cerr << "CompoundStmt(items=";
      print_ast_vec(nn->items, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTIfStmt)) {
      std::shared_ptr<ASTIfStmt> nn = std::dynamic_pointer_cast<ASTIfStmt>(n);
      std::cerr << "IfStmt(cond=";
      print_ast_sub(nn->cond, depth);
      std::cerr << ", true-stmt=";
      print_ast_sub(nn->true_stmt, depth);
      if (nn->false_stmt) {
        std::cerr <<", false-stmt=";
        print_ast_sub(nn->false_stmt, depth);
      }
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTElseStmt)) {
      std::shared_ptr<ASTElseStmt> nn = std::dynamic_pointer_cast<ASTElseStmt>(n);
      std::cerr << "ElseStmt(";
      if (nn->cond) {
        std::cerr << "cond=";
        print_ast_sub(nn->cond, depth);
      } else {
        std::cerr << "cond=nil";
      }
      std::cerr << ", true-stmt=";
      print_ast_sub(nn->true_stmt, depth);
      if (nn->false_stmt) {
        std::cerr <<", false-stmt=";
        print_ast_sub(nn->false_stmt, depth);
      }
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTWhileStmt)) {
      std::shared_ptr<ASTWhileStmt> nn = std::dynamic_pointer_cast<ASTWhileStmt>(n);
      std::cerr << "WhileStmt(cond=";
      print_ast_sub(nn->cond, depth);
      std::cerr << ", body=";
      print_ast_sub(nn->body, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTFnDeclarator)) {
      std::shared_ptr<ASTFnDeclarator> nn = std::dynamic_pointer_cast<ASTFnDeclarator>(n);
      std::cerr << "FnDeclarator(fdtor=";
      print_ast_sub(nn->dtor, depth);
      std::cerr << ", templates=";
      print_ast_vec(nn->templates, depth);
      std::cerr << ", args=";
      print_ast_vec(nn->args, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTFnDeclaration)) {
      std::shared_ptr<ASTFnDeclaration> nn = std::dynamic_pointer_cast<ASTFnDeclaration>(n);
      std::cerr << "FnDeclaration(rt=";
      print_ast_sub(nn->ret_type, depth);
      std::cerr << ", dtor=";
      print_ast_sub(nn->dtor, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTFnDef)) {
      std::shared_ptr<ASTFnDef> nn = std::dynamic_pointer_cast<ASTFnDef>(n);
      std::cerr << "FnDef(dtion=";
      print_ast_sub(nn->dtion, depth);
      std::cerr << ", body=";
      print_ast_sub(nn->body, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTMethodDef)) {
      std::shared_ptr<ASTMethodDef> nn = std::dynamic_pointer_cast<ASTMethodDef>(n);
      std::cerr << "MethodDef(dtion=";
      print_ast_sub(nn->dtion, depth);
      std::cerr << ", body=";
      print_ast_sub(nn->body, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTStDef)) {
      std::shared_ptr<ASTStDef> nn = std::dynamic_pointer_cast<ASTStDef>(n);
      std::cerr << "StDef(dtor=";
      print_ast_sub(nn->dtor, depth);
      std::cerr << ", templates=";
      print_ast_vec(nn->templates, depth);
      std::cerr << ", dtions=";
      print_ast_vec(nn->dtions, depth);
      std::cerr << ", methods=";
      print_ast_vec(nn->methods, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTExternalDeclaration)) {
      std::shared_ptr<ASTExternalDeclaration> nn = std::dynamic_pointer_cast<ASTExternalDeclaration>(n);
      std::cerr << "ExternalDeclaration(ds=";
      print_ast_sub(nn->dtion_spec, depth);
      std::cerr << ", dtors=";
      print_ast_vec(nn->dtors, depth);
      std::cerr << ')';
      return;
    }
    if (typeid(*n) == typeid(ASTTranslationUnit)) {
      std::shared_ptr<ASTTranslationUnit> nn = std::dynamic_pointer_cast<ASTTranslationUnit>(n);
      std::cerr << "TranslationUnit(eds=";
      print_ast_vec(nn->external_dtions, depth);
      std::cerr << ')';
      return;
    }
  }

  void print_ast(std::shared_ptr<AST> n) {
    print_ast_sub(n, 0);
    std::cerr << std::endl;
  }
}