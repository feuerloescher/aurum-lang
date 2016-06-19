/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_EXPRESSIONS_HPP
#define AUC_EXPRESSIONS_HPP

#include "common.hpp"
#include "Statements.hpp"

#include <llvm/IR/Value.h>
#include <string>

namespace AST {

class Expression : public Statement {

protected:
    ASTPtr<Type> type;
    llvm::Value* llvmValue;

public:
    virtual void runPass(ASTPass& pass) = 0;
    virtual ASTPtr<Type> getType();
    virtual void setType(ASTPtr<Type> type);
    virtual llvm::Value* getLLVMValue();
    virtual void setLLVMValue(llvm::Value* llvmValue);

}; // class Expression

typedef ASTList<Expression> ExpressionList;


class FunctionCallExpr : public Expression {

protected:
    std::string name;
    ASTList<Expression> parameters;
    FunctionDef* functionDef;

public:
    FunctionCallExpr(std::string name);

    virtual void runPass(ASTPass& pass);
    std::string getName();
    ASTList<Expression>& getParameters();
    FunctionDef* getFunctionDef();
    void setFunctionDef(FunctionDef* functionDef);

}; // class FunctionCallExpr


class MethodCallExpr : public Expression {

protected:
    ASTPtr<Expression> objectExpr;
    std::string name;
    ASTList<Expression> parameters;
    MethodDef* methodDef;

public:
    MethodCallExpr(ASTPtr<Expression> tmpObjectExpr, std::string name);

    virtual void runPass(ASTPass& pass);
    ASTPtr<Expression> getObjectExpr();
    std::string getName();
    std::string getMangledName();
    ASTList<Expression>& getParameters();
    MethodDef* getMethodDef();
    void setMethodDef(MethodDef* functionDef);

}; // class MethodCallExpr


class ConstUInt32Expr : public Expression {

protected:
    uint32_t numValue;

public:
    ConstUInt32Expr(uint32_t numValue);

    virtual void runPass(ASTPass& pass);

    uint32_t getNumValue();

}; // class ConstNumberExpr


class VariableExpr : public Expression {

protected:
    std::string name;
    VariableDefStmt* variableDefStmt;

public:
    VariableExpr(std::string name);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    VariableDefStmt* getVariableDefStmt();
    void setVariableDefStmt(VariableDefStmt* variableDefStmt);

}; // class VariableExpr


} // namespace AST

#endif // AUC_EXPRESSIONS_HPP
