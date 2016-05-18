/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_VALUEEXPRESSIONS_HPP
#define AUC_VALUEEXPRESSIONS_HPP

#include "common.hpp"
#include "ImperativeExpressions.hpp"
#include "ASTPass.hpp"

#include <string>

namespace AST {

class ValueExpr : public ImperativeExpr {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class ValueExpr

typedef ASTList<ValueExpr> ValueExprList;


class FunctionCallExpr : public ValueExpr {

protected:
    std::string name;
    ASTList<ValueExpr> parameters;

    FunctionCallExpr();

public:
    virtual void runPass(ASTPass& pass);
    ASTList<ValueExpr>& getParameters();

}; // class FunctionCallExpr


class ConstIntExpr : public ValueExpr {

protected:
    uint32_t value;

    ConstIntExpr();

public:
    ConstIntExpr(uint32_t value);

    virtual void runPass(ASTPass& pass);

    uint32_t getValue();

}; // class ConstNumberExpr


class VariableExpr : public ValueExpr {

protected:
    std::string name;

    VariableExpr();

public:
    VariableExpr(std::string name);

    virtual void runPass(ASTPass& pass);

    std::string getName();

}; // class VariableExpr


class UnaryOpExpr : public ValueExpr {

protected:
    std::string name;
    ASTPtr<ValueExpr> operand;

    UnaryOpExpr();

public:
    UnaryOpExpr(std::string name, ASTPtr<ValueExpr> operand);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<ValueExpr> getOperand();

}; // class UnaryOpExpr


class BinaryOpExpr : public ValueExpr {

protected:
    std::string name;
    ASTPtr<ValueExpr> operand1;
    ASTPtr<ValueExpr> operand2;

    BinaryOpExpr();

public:
    BinaryOpExpr(std::string name, ASTPtr<ValueExpr> operand1,
        ASTPtr<ValueExpr> operand2);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<ValueExpr> getOperand1();
    ASTPtr<ValueExpr> getOperand2();

}; // class BinaryOpExpr


class UnaryAssignOpExpr : public ValueExpr {

protected:
    std::string name;
    ASTPtr<VariableExpr> variable;

    UnaryAssignOpExpr();

public:
    UnaryAssignOpExpr(std::string name, ASTPtr<VariableExpr> variable);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<VariableExpr> getVariable();

}; // class UnaryAssignOpExpr


class BinaryAssignOpExpr : public ValueExpr {

protected:
    std::string name;
    ASTPtr<VariableExpr> variable;
    ASTPtr<ValueExpr> operand;

    BinaryAssignOpExpr();

public:
    BinaryAssignOpExpr(std::string name, ASTPtr<VariableExpr> variable,
        ASTPtr<ValueExpr> operand);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<VariableExpr> getVariable();
    ASTPtr<ValueExpr> getOperand();

}; // class BinaryAssignOpExpr

} // namespace AST

#endif // AUC_VALUEEXPRESSIONS_HPP
