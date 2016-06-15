/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_BLOCKS_HPP
#define AUC_BLOCKS_HPP

#include "common.hpp"
#include "Statements.hpp"
#include "Expressions.hpp"
#include "ASTPass.hpp"
#include "ASTMap.hpp"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

namespace AST {

class Block : public Statement {

protected:
    StatementList statements;
    ASTMap<VariableDefStmt> variables;
    Block* parentBlock;
    llvm::BasicBlock* llvmBlock;
    ASTPtr<llvm::IRBuilder<>> irBuilder;

public:
    Block();

    virtual void runPass(ASTPass& pass);

    StatementList& getStatements();
    void push_back(ASTPtr<Statement> statement);

    ASTMap<VariableDefStmt>& getVariables();
    Block* getParentBlock();
    void setParentBlock(Block* block);
    llvm::BasicBlock* getLLVMBlock();
    void setBasicBlock(llvm::BasicBlock* llvmBlock);
    ASTPtr<llvm::IRBuilder<>> getIRBuilder();

}; // class Block


class IfStmt : public Statement {

protected:
    ASTPtr<Expression> condition;
    Block body;

public:
    IfStmt(ASTPtr<Expression> condition);
    virtual void runPass(ASTPass& pass);

    ASTPtr<Expression> getCondition();
    Block& getBody();

}; // class IfStmt


class WhileLoop : public Statement {

protected:
    ASTPtr<Expression> condition;
    Block body;

public:
    WhileLoop(ASTPtr<Expression> condition);
    virtual void runPass(ASTPass& pass);

    ASTPtr<Expression> getCondition();
    Block& getBody();

}; // class WhileLoop

} // namespace AST

#endif // AUC_BLOCKS_HPP
