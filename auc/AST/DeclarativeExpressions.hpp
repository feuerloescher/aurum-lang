/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_DECLARATIVEEXPRESSIONS_HPP
#define AUC_DECLARATIVEEXPRESSIONS_HPP

#include "common.hpp"
#include "Expression.hpp"
#include "ImperativeExpressions.hpp"
#include "ASTPass.hpp"

#include <string>

namespace AST {

class DeclarativeExpr : public Expression {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class DeclarativeExpr

typedef ASTList<DeclarativeExpr> DeclarativeExprList;


class FunctionDeclExpr : public DeclarativeExpr {

protected:
    std::string name;
    ImperativeExprList body;

    FunctionDeclExpr();

public:
    FunctionDeclExpr(std::string name, ImperativeExprList body);

    virtual void runPass(ASTPass& pass);
    virtual void runPassOnChildren(ASTPass& pass);

    std::string getName();

}; // class FunctionDeclExpr

} // namespace AST

#endif // AUC_DECLARATIVEEXPRESSIONS_HPP
