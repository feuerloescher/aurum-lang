/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_STATEMENTS_HPP
#define AUC_STATEMENTS_HPP

#include "common.hpp"
#include "ASTElement.hpp"

#include <string>

namespace AST {

class Statement : public ASTElement {

protected:
    Block* parentBlock;

public:
    Statement(Block* parentBlock, CodeLocation codeLocation);

    Block* getParentBlock();

}; // class Statement

typedef ASTList<Statement> StatementList;


class ReturnStmt : public Statement {

protected:
    ASTPtr<Expression> value;

public:
    ReturnStmt(ASTPtr<Expression> value, Block* parentBlock,
        CodeLocation codeLocation);
    virtual void runPass(ASTPass& pass);

    ASTPtr<Expression> getValue();

}; // class ReturnStmt


class VariableDefStmt : public Statement {

protected:
    ASTPtr<TypeStmt> typeStmt;
    std::string name;

public:
    VariableDefStmt(ASTPtr<TypeStmt> typeStmt, std::string name,
        Block* parentBlock, CodeLocation codeLocation);
    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<TypeStmt> getTypeStmt();

}; // class VariableDefStmt

typedef ASTList<VariableDefStmt> VariableDefStmtList;


class VariableDefAssignStmt : public VariableDefStmt {

protected:
    ASTPtr<Expression> value;

public:
    VariableDefAssignStmt(ASTPtr<TypeStmt> type, std::string name,
        ASTPtr<Expression> value, Block* parentBlock,
        CodeLocation codeLocation);
    virtual void runPass(ASTPass& pass);

    ASTPtr<Expression> getValue();

}; // class VariableDefAssignStmt

} // namespace AST

#endif // AUC_STATEMENTS_HPP
