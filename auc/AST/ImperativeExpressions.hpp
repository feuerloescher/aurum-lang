/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_IMPERATIVEEXPRESSIONS_HPP
#define AUC_IMPERATIVEEXPRESSIONS_HPP

#include "common.hpp"
#include "TypeExpr.hpp"
#include "Expression.hpp"

#include <string>

namespace AST {

class ValueExpr;

class ImperativeExpr : Expression {

protected:
    ImperativeExpr();

public:
    virtual std::string toString() = 0;

}; // class ImperativeExpr

typedef ASTList<ImperativeExpr> ImperativeExprList;

std::string ImpListToString(ImperativeExprList list);


class ReturnExpr : ImperativeExpr {

protected:
    ASTPtr<ValueExpr> value;

    ReturnExpr();

public:
    ReturnExpr(ASTPtr<ValueExpr> value);
    virtual std::string toString();

}; // class ReturnExpr


class VariableDefExpr : ImperativeExpr {

protected:
    std::string name;
    ASTPtr<TypeExpr> type;

    VariableDefExpr();

public:
    VariableDefExpr(std::string name, ASTPtr<TypeExpr> type);
    virtual std::string toString();

}; // class VariableDefExpr


class VariableDefAssignExpr : VariableDefExpr {

protected:
    std::string name;
    ASTPtr<TypeExpr> type;
    ASTPtr<ValueExpr> value;

    VariableDefAssignExpr();

public:
    VariableDefAssignExpr(std::string name, ASTPtr<TypeExpr> type,
        ASTPtr<ValueExpr> value);
    virtual std::string toString();

}; // class VariableDefAssignExpr

} // namespace AST

#endif // AUC_IMPERATIVEEXPRESSIONS_HPP
