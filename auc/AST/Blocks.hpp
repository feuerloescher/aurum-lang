/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_BLOCKS_HPP
#define AUC_BLOCKS_HPP

#include "common.hpp"
#include "Statements.hpp"
#include "ASTMap.hpp"
#include "CodeLocation.hpp"

namespace AST {

class Block : public Statement {

protected:
    StatementList statements;
    ASTMap<VariableDefStmt*> variables;

public:
    Block(CodeLocation codeLocation);
    virtual ~Block() {};

    virtual void runPass(ASTPass& pass);

    StatementList& getStatements();

    void push_back(StatementPtr statement);

    ASTMap<VariableDefStmt*>& getVariables();

}; // class Block


class IfStmt : public Statement {

protected:
    ExpressionPtr condition;
    BlockPtr body;

public:
    IfStmt(ExpressionPtr condition, BlockPtr body, CodeLocation codeLocation);
    virtual ~IfStmt() {};

    virtual void runPass(ASTPass& pass);

    ExpressionPtr getCondition();

    BlockPtr& getBody();

}; // class IfStmt


class WhileLoop : public Statement {

protected:
    ExpressionPtr condition;
    Block body;

public:
    WhileLoop(ExpressionPtr condition,
            CodeLocation codeLocation);
    virtual ~WhileLoop() {};

    virtual void runPass(ASTPass& pass);

    ExpressionPtr getCondition();

    Block& getBody();

}; // class WhileLoop

} // namespace AST

#endif // AUC_BLOCKS_HPP
