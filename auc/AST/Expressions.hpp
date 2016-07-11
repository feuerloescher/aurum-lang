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

#include <llvm/IR/Value.h>
#include <string>

namespace AST {

class Expression : public Statement {

protected:
    ASTPtr<Type> type;
    llvm::Value* llvmValue;

public:
    Expression(Block* parentBlock, CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass) = 0;
    ASTPtr<Type> getType();
    void setType(ASTPtr<Type> type);
    llvm::Value* getLLVMValue();
    void setLLVMValue(llvm::Value* llvmValue);

}; // class Expression

typedef ASTList<Expression> ExpressionList;


class FunctionCallExpr : public Expression {

protected:
    std::string name;
    ASTList<Expression> args;
    FunctionDef* functionDef;

public:
    FunctionCallExpr(std::string name, Block* parentBlock,
        CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);
    std::string getName();
    ASTList<Expression>& getArgs();
    FunctionDef* getFunctionDef();
    void setFunctionDef(FunctionDef* functionDef);

}; // class FunctionCallExpr


class MethodCallExpr : public Expression {

protected:
    ASTPtr<Expression> objectExpr;
    std::string name;
    ASTList<Expression> args;
    MethodDef* methodDef;

public:
    MethodCallExpr(ASTPtr<Expression> tmpObjectExpr, std::string name,
        Block* parentBlock, CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);
    ASTPtr<Expression> getObjectExpr();
    std::string getName();
    std::string getMangledName();
    ASTList<Expression>& getArgs();
    MethodDef* getMethodDef();
    void setMethodDef(MethodDef* functionDef);

}; // class MethodCallExpr


class ConstIntExpr : public Expression {

protected:
    std::string valueStr;
    uint64_t numValue;
    ASTPtr<TypeStmt> typeStmt;

public:
    ConstIntExpr(std::string valueStr, uint8_t numValue,
        Block* parentBlock, CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, int8_t numValue,
        Block* parentBlock, CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, uint16_t numValue,
        Block* parentBlock, CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, int16_t numValue,
        Block* parentBlock, CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, uint32_t numValue,
        Block* parentBlock, CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, int32_t numValue,
        Block* parentBlock, CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, uint64_t numValue,
        Block* parentBlock, CodeLocation codeLocation);
    ConstIntExpr(std::string valueStr, int64_t numValue,
        Block* parentBlock, CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

    std::string getValueStr();
    uint64_t getNumValue();
    ASTPtr<TypeStmt> getTypeStmt();

}; // class ConstIntExpr


class VariableExpr : public Expression {

protected:
    std::string name;
    VariableDefStmt* variableDefStmt;

public:
    VariableExpr(std::string name, Block* parentBlock,
        CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    VariableDefStmt* getVariableDefStmt();
    void setVariableDefStmt(VariableDefStmt* variableDefStmt);

}; // class VariableExpr


} // namespace AST

#endif // AUC_EXPRESSIONS_HPP
