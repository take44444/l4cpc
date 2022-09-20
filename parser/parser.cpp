#include "./parser.hpp"

namespace parser {
  std::shared_ptr<ASTTypeSpec> parse_type_spec(Token **next, PError &err) {
    Token *t;
    if ((t = expect_token_with_type(next, err, KwI64))) {
      return std::make_shared<ASTTypeSpec>(t);
    }
    if ((t = expect_token_with_type(next, err, KwI8))) {
      return std::make_shared<ASTTypeSpec>(t);
    }
    if ((t = expect_token_with_type(next, err, KwFn))) {
      std::shared_ptr<ASTTypeSpec> ret = std::make_shared<ASTTypeSpec>(t);
      if (!expect_token_with_str(next, err, "(")) return nullptr;
      while (!expect_token_with_str(next, err, ")")) {
        std::shared_ptr<ASTTypeSpec> type;
        if (!(type = parse_type_spec(next, err))) return nullptr;
        ret->args.push_back(type);
        if (expect_token_with_str(next, err, ",")) continue;
        // end
        if (!expect_token_with_str(next, err, ")")) return nullptr;
        break;
      }
      // token "->" should be here
      if (!expect_token_with_str(next, err, "->")) return nullptr;
      if (!(ret->ret_type = parse_type_spec(next, err))) return nullptr;
      return ret;
    }
    if ((t = expect_token_with_type(next, err, Ident))) {
      std::shared_ptr<ASTTypeSpec> ret = std::make_shared<ASTTypeSpec>(t);
      if (expect_token_with_str(next, err, "<")) {
        std::shared_ptr<ASTTypeSpec> type;
        while (!expect_token_with_str(next, err, ">")) {
          if (!(type = parse_type_spec(next, err))) return nullptr;
          ret->templates.push_back(type);
          if (expect_token_with_str(next, err, ",")) continue;
          // end
          if (!expect_token_with_str(next, err, ">")) return nullptr;
          break;
        }
      }
      return ret;
    }
    return nullptr;
  }

  std::shared_ptr<ASTTypeSpec> parse_dtion_spec(Token **next, PError &err) {
    // TODO static
    return parse_type_spec(next, err);
  }

  std::shared_ptr<ASTExpr> parse_expr(Token **next, PError &err);

  std::shared_ptr<ASTExpr> parse_primary_expr(Token **next, PError &err) {
    Token *t;
    if (expect_token_with_str(next, err, "(")) {
      std::shared_ptr<ASTPrimaryExpr> ret = std::make_shared<ASTPrimaryExpr>();
      if (!(ret->expr = parse_expr(next, err))) return nullptr;
      if (expect_token_with_str(next, err, ")")) return ret;
    } else if ((t = expect_token_with_type(next, err, I64Constant)) ||
               (t = expect_token_with_type(next, err, I8Literal)) ||
               (t = expect_token_with_type(next, err, StringLiteral)) ||
               (t = expect_token_with_type(next, err, Ident))) {
      return std::make_shared<ASTSimpleExpr>(t);
    }
    return nullptr;
  }

  std::shared_ptr<ASTExpr> parse_assign_expr(Token **next, PError &err);

  std::shared_ptr<ASTExpr> parse_postfix_expr(Token **next, PError &err) {
  // ()
  // []
  // .
    std::shared_ptr<ASTExpr> ret = parse_primary_expr(next, err);
    Token *t, *saved;
    while (ret) {
      saved = *next;
      if ((t = expect_token_with_str(next, err, "["))) {
        // now it is vec-access-expr
        std::shared_ptr<ASTIndexAccessExpr> aa = std::make_shared<ASTIndexAccessExpr>(t);
        aa->p = ret;
        aa->expr = parse_expr(next, err);
        ret = aa;
        if (!expect_token_with_str(next, err, "]")) return nullptr;
        continue;
      }
      if (expect_token_with_str(next, err, ".")) {
        Token *t = expect_token_with_type(next, err, Ident);
        if (!t) return nullptr;
        // now it is st-access-expr
        std::shared_ptr<ASTStAccessExpr> sa = std::make_shared<ASTStAccessExpr>(t);
        sa->p = ret;
        ret = sa;
        continue;
      }
      bool has_template = false;
      std::vector<std::shared_ptr<ASTTypeSpec>> templates;
      if (expect_token_with_str(next, err, "<")) {
        has_template = true;
        std::shared_ptr<ASTTypeSpec> type;
        while (!expect_token_with_str(next, err, ">")) {
          if (!(type = parse_type_spec(next, err))) return nullptr;
          templates.push_back(type);
          if (expect_token_with_str(next, err, ",")) continue;
          // end
          if (!expect_token_with_str(next, err, ">")) {
            *next = saved;
            return ret;
          }
          break;
        }
      }
      if ((t = expect_token_with_str(next, err, "("))) {
        // now it is fntion-call-expr
        std::shared_ptr<ASTFnCallExpr> fc = std::make_shared<ASTFnCallExpr>(t);
        fc->p = ret;
        fc->templates = templates;
        std::shared_ptr<ASTExpr> arg;
        while (!expect_token_with_str(next, err, ")")) {
          if (!(arg = parse_assign_expr(next, err))) return nullptr;
          fc->args.push_back(arg);
          if (expect_token_with_str(next, err, ",")) continue;
          // end
          if (!expect_token_with_str(next, err, ")")) return nullptr;
          break;
        }
        ret = fc;
        continue;
      }
      if (has_template) return nullptr;
      break;
    }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_unary_expr(Token **next, PError &err) {
    // Token *t;
    // if ((t = expect_token_with_str(next, err, "*")) ||
    //     (t = expect_token_with_str(next, err, "&"))) {
    //   std::shared_ptr<ASTUnaryExpr> ret = std::make_shared<ASTUnaryExpr>(t);
    //   ret->expr = parse_unary_expr(next, err);
    //   return ret;
    // }
    return parse_postfix_expr(next, err);
  }

  std::shared_ptr<ASTExpr> parse_multiplicative_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_unary_expr(next, err);
    if (!ret) return nullptr;
    Token *t;
    while ((t = expect_token_with_str(next, err, "*")) ||
           (t = expect_token_with_str(next, err, "/")) ||
           (t = expect_token_with_str(next, err, "%"))) {
      left = ret;
      ret = std::make_shared<ASTMultiplicativeExpr>(t);
      ret->left = left;
      if (!(ret->right = parse_unary_expr(next, err))) return nullptr;
    }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_additive_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_multiplicative_expr(next, err);
    if (!ret) return nullptr;
    Token *t;
    while ((t = expect_token_with_str(next, err, "+")) ||
           (t = expect_token_with_str(next, err, "-"))) {
      left = ret;
      ret = std::make_shared<ASTAdditiveExpr>(t);
      ret->left = left;
      if (!(ret->right = parse_multiplicative_expr(next, err))) return nullptr;
    }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_shift_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_additive_expr(next, err);
    // if (!ret) return nullptr;
    // Token *t;
    // while ((t = expect_token_with_str(next, err, "<<")) ||
    //        (t = expect_token_with_str(next, err, ">>"))) {
    //   left = ret;
    //   ret = std::make_shared<ASTShiftExpr>(t);
    //   ret->left = left;
    //   if (!(ret->right = parse_additive_expr(next, err))) return nullptr;
    // }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_relational_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_shift_expr(next, err);
    if (!ret) return nullptr;
    Token *t;
    while ((t = expect_token_with_str(next, err, "<")) ||
           (t = expect_token_with_str(next, err, ">")) ||
           (t = expect_token_with_str(next, err, "<=")) ||
           (t = expect_token_with_str(next, err, ">="))) {
      left = ret;
      ret = std::make_shared<ASTRelationalExpr>(t);
      ret->left = left;
      if (!(ret->right = parse_shift_expr(next, err))) return nullptr;
    }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_equality_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_relational_expr(next, err);
    if (!ret) return nullptr;
    Token *t;
    while ((t = expect_token_with_str(next, err, "=")) ||
           (t = expect_token_with_str(next, err, "!="))) {
      left = ret;
      ret = std::make_shared<ASTEqualityExpr>(t);
      ret->left = left;
      if (!(ret->right = parse_relational_expr(next, err))) return nullptr;
    }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_bitwise_and_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_equality_expr(next, err);
    // if (!ret) return nullptr;
    // while (expect_token_with_str(next, err, "&")) {
    //   left = ret;
    //   ret = std::make_shared<ASTBitwiseAndExpr>();
    //   ret->left = left;
    //   if (!(ret->right = parse_equality_expr(next, err))) return nullptr;
    // }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_bitwise_xor_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_bitwise_and_expr(next, err);
    // if (!ret) return nullptr;
    // while (expect_token_with_str(next, err, "^")) {
    //   left = ret;
    //   ret = std::make_shared<ASTBitwiseXorExpr>();
    //   ret->left = left;
    //   if (!(ret->right = parse_bitwise_and_expr(next, err))) return nullptr;
    // }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_bitwise_or_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_bitwise_xor_expr(next, err);
    // if (!ret) return nullptr;
    // while (expect_token_with_str(next, err, "|")) {
    //   left = ret;
    //   ret = std::make_shared<ASTBitwiseOrExpr>();
    //   ret->left = left;
    //   if (!(ret->right = parse_bitwise_xor_expr(next, err))) return nullptr;
    // }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_logical_and_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_bitwise_or_expr(next, err);
    if (!ret) return nullptr;
    Token *t;
    while ((t = expect_token_with_str(next, err, "&&"))) {
      left = ret;
      ret = std::make_shared<ASTLogicalAndExpr>(t);
      ret->left = left;
      if (!(ret->right = parse_bitwise_or_expr(next, err))) return nullptr;
    }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_logical_or_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left, ret = parse_logical_and_expr(next, err);
    if (!ret) return nullptr;
    Token *t;
    while ((t = expect_token_with_str(next, err, "||"))) {
      left = ret;
      ret = std::make_shared<ASTLogicalOrExpr>(t);
      ret->left = left;
      if (!(ret->right = parse_logical_and_expr(next, err))) return nullptr;
    }
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_assign_expr(Token **next, PError &err) {
    std::shared_ptr<ASTExpr> left = parse_logical_or_expr(next, err);
    // parse error
    if (!left) return nullptr;
    // if ":" is not here, it is not assignment-expr
    // but it is correct expr
    Token *t;
    if (!(t = expect_token_with_str(next, err, ":"))) return left;
    // now it is assignment-expr
    std::shared_ptr<ASTAssignExpr> ret = std::make_shared<ASTAssignExpr>(t);
    ret->left = left;
    if (!(ret->right = parse_assign_expr(next, err))) return nullptr;
    return ret;
  }

  std::shared_ptr<ASTExpr> parse_expr(Token **next, PError &err) {
    return parse_assign_expr(next, err);
  }

  std::shared_ptr<ASTExprStmt> parse_expr_stmt(Token **next, PError &err) {
    std::shared_ptr<ASTExprStmt> ret = std::make_shared<ASTExprStmt>();
    if (!(ret->expr = parse_expr(next, err))) return nullptr;
    if (!expect_token_with_str(next, err, ";")) return nullptr;
    return ret;
  }

  std::shared_ptr<ASTDeclarator> parse_dtor(Token **next, PError &err) {
    Token *t = expect_token_with_type(next, err, Ident);
    if (!t) return nullptr;
    return std::make_shared<ASTDeclarator>(t);
  }

  std::shared_ptr<ASTDeclaration> parse_dtion(Token **next, PError &err) {
    std::shared_ptr<ASTDeclaration> ret = std::make_shared<ASTDeclaration>();
    if (!(ret->dtion_spec = parse_dtion_spec(next, err))) return nullptr;

    std::shared_ptr<ASTDeclarator> dtor;
    while ((dtor = parse_dtor(next, err))) {
      ret->dtors.push_back(dtor);
      if (expect_token_with_str(next, err, ",")) continue;
      return ret;
    }
    return nullptr;
  }

  std::shared_ptr<ASTSimpleDeclaration> parse_simple_dtion(Token **next, PError &err) {
  // type-specifier dtor
    std::shared_ptr<ASTSimpleDeclaration> ret = std::make_shared<ASTSimpleDeclaration>();
    if (!(ret->type_spec = parse_type_spec(next, err))) return nullptr;
    if (!(ret->dtor = parse_dtor(next, err))) return nullptr;
    return ret;
  }

  std::shared_ptr<ASTCompoundStmt> parse_comp_stmt(Token **next, PError &err);

  std::shared_ptr<ASTElseStmt> parse_else_stmt(Token **next, PError &err) {
    Token *t;
    std::shared_ptr<ASTExpr> expr;
    if ((t = expect_token_with_type(next, err, KwElif))) {
      if (!(expr = parse_expr(next, err))) return nullptr;
    } else if (!(t = expect_token_with_type(next, err, KwElse))) {
      return nullptr;
    }
    std::shared_ptr<ASTElseStmt> ret = std::make_shared<ASTElseStmt>(t);
    ret->cond = expr;
    if (!(ret->true_stmt = parse_comp_stmt(next, err))) return nullptr;
    ret->false_stmt = parse_else_stmt(next, err);
    return ret;
  }

  std::shared_ptr<AST> parse_stmt(Token **next, PError &err) {
    Token *t;
    if ((t = expect_token_with_type(next, err, KwBreak))) {
      if (!expect_token_with_str(next, err, ";")) return nullptr;
      return std::make_shared<ASTBreakStmt>(t);
    }
    if ((t = expect_token_with_type(next, err, KwContinue))) {
      if (!expect_token_with_str(next, err, ";")) return nullptr;
      return std::make_shared<ASTContinueStmt>(t);
    }
    if ((t = expect_token_with_type(next, err, KwReturn))) {
      std::shared_ptr<ASTReturnStmt> ret = std::make_shared<ASTReturnStmt>(t);
      if (!(ret->expr = parse_expr(next, err))) return nullptr;
      if (!expect_token_with_str(next, err, ";")) return nullptr;
      return ret;
    }
    if ((t = expect_token_with_type(next, err, KwIf))) {
      std::shared_ptr<ASTIfStmt> ret = std::make_shared<ASTIfStmt>(t);
      if (!(ret->cond = parse_expr(next, err))) return nullptr;
      if (!(ret->true_stmt = parse_comp_stmt(next, err))) return nullptr;
      Token *saved = *next;
      if (!(ret->false_stmt = parse_else_stmt(next, err))) {
        if (*next != saved) return nullptr;
      }
      return ret;
    }
    if ((t = expect_token_with_type(next, err, KwWhile))) {
      std::shared_ptr<ASTWhileStmt> ret = std::make_shared<ASTWhileStmt>(t);
      if (!(ret->cond = parse_expr(next, err))) return nullptr;
      if (!(ret->body = parse_comp_stmt(next, err))) return nullptr;
      return ret;
    }
    return parse_expr_stmt(next, err);
  }

  std::shared_ptr<ASTCompoundStmt> parse_comp_stmt(Token **next, PError &err) {
    std::shared_ptr<AST> item;
    Token *t;
    if (!(t = expect_token_with_str(next, err, "{"))) return nullptr;
    std::shared_ptr<ASTCompoundStmt> ret = std::make_shared<ASTCompoundStmt>(t);
    while (1) {
      if (expect_token_with_str(next, err, "}")) return ret;
      if (!*next || (*next)->sv == "{") {
        if (!(item = parse_comp_stmt(next, err))) break;
      } else {
        t = *next;
        if ((item = parse_dtion(next, err))) {
          if (!expect_token_with_str(next, err, ";")) break;
        } else {
          *next = t;
          if (!(item = parse_stmt(next, err))) break;
        }
      }
      ret->items.push_back(item);
    }
    return nullptr;
  }

  std::shared_ptr<ASTFnDeclarator> parse_fn_dtor(Token **next, PError &err) {
  // dtor(dtion, ...)
    std::shared_ptr<ASTDeclarator> d;
    std::vector<std::shared_ptr<ASTDeclarator>> templates;
    Token *t;
    if (!(d = parse_dtor(next, err))) return nullptr;
    if (expect_token_with_str(next, err, "<")) {
      std::shared_ptr<ASTDeclarator> t;
      while (!expect_token_with_str(next, err, ">")) {
        if (!(t = parse_dtor(next, err))) return nullptr;
        templates.push_back(t);
        if (expect_token_with_str(next, err, ",")) continue;
        // end
        if (!expect_token_with_str(next, err, ">")) return nullptr;
        break;
      }
    }
    if (!(t = expect_token_with_str(next, err, "("))) return nullptr;
    std::shared_ptr<ASTFnDeclarator> ret = std::make_shared<ASTFnDeclarator>(t);
    ret->dtor = d;
    ret->templates = templates;

    std::shared_ptr<ASTSimpleDeclaration> dtion;
    while (!expect_token_with_str(next, err, ")")) {
      if (!(dtion = parse_simple_dtion(next, err))) return nullptr;
      ret->args.push_back(dtion);
      if (expect_token_with_str(next, err, ",")) continue;
      // end
      if (!expect_token_with_str(next, err, ")")) return nullptr;
      break;
    }
    return ret;
  }

  std::shared_ptr<ASTFnDeclaration> parse_fn_dtion(Token **next, PError &err) {
  // fn-dtor -> type
    std::shared_ptr<ASTFnDeclaration> ret = std::make_shared<ASTFnDeclaration>();
    if (!(ret->dtor = parse_fn_dtor(next, err))) return nullptr;
    if (expect_token_with_str(next, err, "->")) {
      if (!(ret->ret_type = parse_type_spec(next, err))) return nullptr;
    }
    return ret;
  }

  std::shared_ptr<ASTFnDef> parse_fn_def(Token **next, PError &err) {
  // fn-dtion compound-stmt
    if (!expect_token_with_type(next, err, KwFn)) return nullptr;
    std::shared_ptr<ASTFnDef> ret = std::make_shared<ASTFnDef>();
    if (!(ret->dtion = parse_fn_dtion(next, err))) return nullptr;
    if (!(ret->body = parse_comp_stmt(next, err))) return nullptr;
    return ret;
  }

  std::shared_ptr<ASTMethodDef> parse_method_def(Token **next, PError &err) {
  // fn-dtion compound-stmt
    std::shared_ptr<ASTMethodDef> ret = std::make_shared<ASTMethodDef>();
    if (!(ret->dtion = parse_fn_dtion(next, err))) return nullptr;
    if (!(ret->body = parse_comp_stmt(next, err))) return nullptr;
    return ret;
  }

  std::shared_ptr<ASTStDef> parse_st_def(Token **next, PError &err) {
    if (!expect_token_with_type(next, err, KwSt)) return nullptr;
    std::shared_ptr<ASTStDef> ret = std::make_shared<ASTStDef>();
    if (!(ret->dtor = parse_dtor(next, err))) return nullptr;
    if (expect_token_with_str(next, err, "<")) {
      std::shared_ptr<ASTDeclarator> t;
      while (!expect_token_with_str(next, err, ">")) {
        if (!(t = parse_dtor(next, err))) return nullptr;
        ret->templates.push_back(t);
        if (expect_token_with_str(next, err, ",")) continue;
        // end
        if (!expect_token_with_str(next, err, ">")) return nullptr;
        break;
      }
    }
    if (!expect_token_with_str(next, err, "{")) return nullptr;
    Token *saved;
    std::shared_ptr<ASTMethodDef> method;
    std::shared_ptr<ASTSimpleDeclaration> dtion;
    while (*next) {
      if (expect_token_with_str(next, err, "}") && ret->dtions.size()) {
        return ret;
      }
      saved = *next;
      if ((dtion = parse_simple_dtion(next, err))) {
        ret->dtions.push_back(dtion);
        if (!expect_token_with_str(next, err, ";")) return nullptr;
        continue;
      }
      *next = saved;
      if ((method = parse_method_def(next, err))) {
        ret->methods.push_back(method);
        continue;
      }
      break;
    }
    return nullptr;
  }

  std::shared_ptr<ASTExternalDeclaration> parse_external_dtion(Token **next, PError &err) {
    std::shared_ptr<ASTExternalDeclaration> ret = std::make_shared<ASTExternalDeclaration>();
    if (!(ret->dtion_spec = parse_dtion_spec(next, err))) return nullptr;

    std::shared_ptr<ASTDeclarator> dtor;
    while ((dtor = parse_dtor(next, err))) {
      ret->dtors.push_back(dtor);
      if (expect_token_with_str(next, err, ",")) continue;
      // dtion end
      if (expect_token_with_str(next, err, ";")) return ret;
      break;
    }
    return nullptr;
  }

  std::shared_ptr<ASTTranslationUnit> parse_translation_unit(Token **next, PError &err) {
    std::shared_ptr<ASTTranslationUnit> ret = std::make_shared<ASTTranslationUnit>();

    std::shared_ptr<AST> external_dtion;
    Token *saved;
    while (*next) {
      saved = *next;
      external_dtion = parse_st_def(next, err);
      if (!external_dtion && saved != *next) return nullptr;
      if (!external_dtion) external_dtion = parse_fn_def(next, err);
      if (!external_dtion && saved != *next) return nullptr;
      if (!external_dtion) external_dtion = parse_external_dtion(next, err);
      if (!external_dtion) return nullptr;
      ret->external_dtions.push_back(external_dtion);
    }
    return ret;
  }

  void init_parser(Token **head_token) {
    // *head_token can be NULL
    Token *next = *head_token;
    Token *t, *bef;
    while (next) {
      // if next token is Delimiter, remove it and continue
      t = consume_token_with_type(&next, Delimiter);    
      if (!t) break;
      delete t;
    }
    // set new head_token
    *head_token = next;
    // *head_token can be NULL
    while (next) {
      bef = next;
      next = bef->next;
      while (next) {
        // if next token is Delimiter, remove it and continue
        t = consume_token_with_type(&next, Delimiter);
        if (!t) break;
        delete t;
      }
      bef->next = next;
    }
  }

  std::shared_ptr<ASTTranslationUnit> parse(Token **head_token, PError &err) {
    init_parser(head_token);
    Token *next = *head_token;
    return parse_translation_unit(&next, err);
  }
}