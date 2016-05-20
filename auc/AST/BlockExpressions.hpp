/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_BLOCKEXPRESSIONS_HPP
#define AUC_BLOCKEXPRESSIONS_HPP

#include "common.hpp"
#include "ImperativeExpressions.hpp"
#include "ValueExpressions.hpp"
#include "ASTPass.hpp"

namespace AST {

class BlockExpr : public ImperativeExpr {

protected:
    ImperativeExprList body;

public:
    virtual void runPass(ASTPass& pass) = 0;

    ImperativeExprList getBody();

}; // class BlockExpr


class IfExpr : public BlockExpr {

protected:
    ASTPtr<ValueExpr> condition;

public:
    IfExpr(ASTPtr<ValueExpr> condition);
    virtual void runPass(ASTPass& pass);

}; // class IfExpr


class WhileLoopExpr : public BlockExpr {

protected:
    ASTPtr<ValueExpr> condition;

public:
    WhileLoopExpr(ASTPtr<ValueExpr> condition);
    virtual void runPass(ASTPass& pass);

}; // class WhileLoopExpr

} // namespace AST

#endif // AUC_BLOCKEXPRESSIONS_HPP
