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

public:
    Expression(CodeLocation codeLocation);
    virtual ~Expression() {};

    virtual void runPass(ASTPass& pass) = 0;
    virtual type::TypePtr getType() = 0;
    virtual bool getIsReferenceable() = 0;

}; // class Expression



class FunctionCallExpr : public Expression {

protected:
    std::string name;
    ASTList<Expression> args;
    FunctionDecl* functionDecl;

public:
    FunctionCallExpr(std::string name,
            CodeLocation codeLocation);
    virtual ~FunctionCallExpr() {};

    void runPass(ASTPass& pass) override;
    type::TypePtr getType() override;
    bool getIsReferenceable() override;
    std::string getName();
    ASTList<Expression>& getArgs();
    FunctionDecl* getFunctionDecl();
    void setFunctionDecl(FunctionDecl* functionDecl);

}; // class FunctionCallExpr



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
    virtual ~ConstIntExpr() {};

    void runPass(ASTPass& pass) override;
    type::TypePtr getType() override;
    bool getIsReferenceable() override;

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
    virtual ~VariableExpr() {};

    void runPass(ASTPass& pass) override;
    type::TypePtr getType() override;
    bool getIsReferenceable() override;

    std::string getName();
    VariableDefStmt* getVariableDefStmt();
    void setVariableDefStmt(VariableDefStmt* variableDefStmt);

}; // class VariableExpr



} // namespace AST

#endif // AUC_EXPRESSIONS_HPP
