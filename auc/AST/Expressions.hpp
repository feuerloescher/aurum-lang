/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_EXPRESSIONS_HPP
#define AUC_EXPRESSIONS_HPP

#include "common.hpp"
#include "Statements.hpp"
#include "CodeLocation.hpp"

#include <string>

namespace AST {

class Expression : public Statement {

protected:
    TypePtr type;

public:
    Expression(CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass) = 0;
    TypePtr getType();
    void setType(TypePtr type);

}; // class Expression



class FunctionCallExpr : public Expression {

protected:
    std::string name;
    ASTList<Expression> args;
    FunctionDef* functionDef;

public:
    FunctionCallExpr(std::string name,
            CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);
    std::string getName();
    ASTList<Expression>& getArgs();
    FunctionDef* getFunctionDef();
    void setFunctionDef(FunctionDef* functionDef);

}; // class FunctionCallExpr



class MethodCallExpr : public Expression {

protected:
    ExpressionPtr objectExpr;
    std::string name;
    ASTList<Expression> args;
    MethodDef* methodDef;

public:
    MethodCallExpr(ExpressionPtr tmpObjectExpr, std::string name,
            CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);
    ExpressionPtr getObjectExpr();
    std::string getName();
    std::string getMangledName();
    ASTList<Expression>& getArgs();
    MethodDef* getMethodDef();
    void setMethodDef(MethodDef* functionDef);
    bool isOperator();

}; // class MethodCallExpr



class ConstIntExpr : public Expression {

protected:
    std::string valueStr;
    uint64_t numValue;
    TypeStmtPtr typeStmt;

public:
    ConstIntExpr(std::string valueStr, uint8_t numValue,
            CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, int8_t numValue,
            CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, uint16_t numValue,
            CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, int16_t numValue,
            CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, uint32_t numValue,
            CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, int32_t numValue,
            CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, uint64_t numValue,
            CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, int64_t numValue,
            CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

    std::string getValueStr();
    uint64_t getNumValue();
    TypeStmtPtr getTypeStmt();

}; // class ConstIntExpr



class VariableExpr : public Expression {

protected:
    std::string name;
    VariableDefStmt* variableDefStmt;

public:
    VariableExpr(std::string name,
            CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    VariableDefStmt* getVariableDefStmt();
    void setVariableDefStmt(VariableDefStmt* variableDefStmt);

}; // class VariableExpr



} // namespace AST

#endif // AUC_EXPRESSIONS_HPP
