/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_STATEMENTS_HPP
#define AUC_STATEMENTS_HPP

#include "common.hpp"
#include "TypeStmt.hpp"
#include "ASTPass.hpp"

#include <llvm/IR/Instructions.h>
#include <string>

namespace AST {

class Statement {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class Statement

typedef ASTList<Statement> StatementList;


class ReturnStmt : public Statement {

protected:
    ASTPtr<Expression> value;

public:
    ReturnStmt(ASTPtr<Expression> value);
    virtual void runPass(ASTPass& pass);

    ASTPtr<Expression> getValue();

}; // class ReturnStmt


class VariableDefStmt : public Statement {

protected:
    std::string name;
    ASTPtr<TypeStmt> typeStmt;
    llvm::AllocaInst* allocaInst;

public:
    VariableDefStmt(std::string name, ASTPtr<TypeStmt> typeStmt);
    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<TypeStmt> getTypeStmt();
    llvm::AllocaInst* getAllocaInst();
    void setAllocaInst(llvm::AllocaInst* allocaInst);

}; // class VariableDefStmt

typedef ASTList<VariableDefStmt> VariableDefStmtList;


class VariableDefAssignStmt : public VariableDefStmt {

protected:
    ASTPtr<Expression> value;

public:
    VariableDefAssignStmt(std::string name, ASTPtr<TypeStmt> type,
        ASTPtr<Expression> value);
    virtual void runPass(ASTPass& pass);

    ASTPtr<Expression> getValue();

}; // class VariableDefAssignStmt

} // namespace AST

#endif // AUC_STATEMENTS_HPP
