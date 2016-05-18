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
#include "ASTPass.hpp"

#include <string>

namespace AST {

class ValueExpr;

class ImperativeExpr : public Expression {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class ImperativeExpr

typedef ASTList<ImperativeExpr> ImperativeExprList;


class ReturnExpr : public ImperativeExpr {

protected:
    ASTPtr<ValueExpr> value;

    ReturnExpr();

public:
    ReturnExpr(ASTPtr<ValueExpr> value);
    virtual void runPass(ASTPass& pass);

    ASTPtr<ValueExpr> getValue();

}; // class ReturnExpr


class VariableDefExpr : public ImperativeExpr {

protected:
    std::string name;
    ASTPtr<TypeExpr> type;

    VariableDefExpr();

public:
    VariableDefExpr(std::string name, ASTPtr<TypeExpr> type);
    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<TypeExpr> getType();

}; // class VariableDefExpr

typedef ASTList<VariableDefExpr> VariableDefExprList;


class VariableDefAssignExpr : public ImperativeExpr {

protected:
    std::string name;
    ASTPtr<TypeExpr> type;
    ASTPtr<ValueExpr> value;

    VariableDefAssignExpr();

public:
    VariableDefAssignExpr(std::string name, ASTPtr<TypeExpr> type,
        ASTPtr<ValueExpr> value);
    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<TypeExpr> getType();
    ASTPtr<ValueExpr> getValue();

}; // class VariableDefAssignExpr

} // namespace AST

#endif // AUC_IMPERATIVEEXPRESSIONS_HPP
