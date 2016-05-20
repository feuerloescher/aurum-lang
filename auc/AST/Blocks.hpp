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

namespace AST {

class Block : public Statement {

protected:
    StatementList body;

public:
    virtual void runPass(ASTPass& pass) = 0;

    StatementList getBody();

}; // class Block


class IfStmt : public Block {

protected:
    ASTPtr<Expression> condition;

public:
    IfStmt(ASTPtr<Expression> condition);
    virtual void runPass(ASTPass& pass);

}; // class IfStmt


class WhileLoop : public Block {

protected:
    ASTPtr<Expression> condition;

public:
    WhileLoop(ASTPtr<Expression> condition);
    virtual void runPass(ASTPass& pass);

}; // class WhileLoop

} // namespace AST

#endif // AUC_BLOCKS_HPP
