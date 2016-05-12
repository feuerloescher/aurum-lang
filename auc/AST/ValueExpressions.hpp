/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_VALUEEXPRESSIONS_HPP
#define AUC_VALUEEXPRESSIONS_HPP

#include "common.hpp"
#include "ImperativeExpressions.hpp"

#include <string>

namespace AST {

class ValueExpr : ImperativeExpr {

protected:
    ValueExpr();

public:
    virtual std::string toString() = 0;

}; // class ValueExpr

typedef ASTList<ValueExpr> ValueExprList;

std::string ParamListToString(ValueExprList list);


class FunctionCallExpr : ValueExpr {

protected:
    std::string name;
    ASTList<ValueExpr> parameters;

    FunctionCallExpr();

public:
    virtual std::string toString();

}; // class FunctionCallExpr


class ConstIntExpr : ValueExpr {

protected:
    uint32_t value;

    ConstIntExpr();

public:
    virtual std::string toString();

}; // class ConstNumberExpr


class VariableExpr : ValueExpr {

protected:
    std::string name;

    VariableExpr();

public:
    VariableExpr(std::string name);

    virtual std::string toString();

}; // class VariableExpr


class UnaryOpExpr : ValueExpr {

protected:
    std::string name;
    ASTPtr<ValueExpr> operand;

    UnaryOpExpr();

public:
    virtual std::string toString();

}; // class UnaryOpExpr


class BinaryOpExpr : ValueExpr {

protected:
    std::string name;
    ASTPtr<ValueExpr> operand1;
    ASTPtr<ValueExpr> operand2;

    BinaryOpExpr();

public:
    virtual std::string toString();

}; // class BinaryOpExpr


class UnaryAssignOpExpr : ValueExpr {

protected:
    ASTPtr<VariableExpr> variable;
    std::string name;

    UnaryAssignOpExpr();

public:
    virtual std::string toString();

}; // class UnaryAssignOpExpr


class BinaryAssignOpExpr : ValueExpr {

protected:
    ASTPtr<VariableExpr> variable;
    std::string name;
    ASTPtr<ValueExpr> operand;

    BinaryAssignOpExpr();

public:
    virtual std::string toString();

}; // class BinaryAssignOpExpr

} // namespace AST

#endif // AUC_VALUEEXPRESSIONS_HPP
