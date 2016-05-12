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

#include <string>

namespace AST {

class DeclarativeExpr : Expression {

protected:
    DeclarativeExpr();

public:
    virtual std::string toString() = 0;

}; // class DeclarativeExpr

typedef ASTList<DeclarativeExpr> DeclarativeExprList;

std::string DeclListToString(DeclarativeExprList list);


class FunctionDeclExpr : DeclarativeExpr {

protected:
    std::string name;
    ImperativeExprList body;

    FunctionDeclExpr();

public:
    FunctionDeclExpr(std::string name, ASTPtr<ImperativeExprList> body);
    virtual std::string toString();

}; // class FunctionDeclExpr

} // namespace AST

#endif // AUC_DECLARATIVEEXPRESSIONS_HPP
