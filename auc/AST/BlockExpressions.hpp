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

#include <string>

namespace AST {

class BlockExpr : ImperativeExpr {

protected:
    ImperativeExprList body;

    BlockExpr();

public:
    virtual std::string toString() = 0;

}; // class BlockExpr


class IfExpr : public BlockExpr {

protected:
    ASTPtr<ValueExpr> condition;

    IfExpr();

public:
    IfExpr(ASTPtr<ValueExpr> condition, ASTPtr<ImperativeExprList> body);
    virtual std::string toString();

}; // class IfExpr


class WhileLoopExpr : public IfExpr {

protected:
    WhileLoopExpr();

public:
    WhileLoopExpr(ASTPtr<ValueExpr> condition, ASTPtr<ImperativeExprList> body);
    virtual std::string toString();

}; // class WhileLoopExpr

} // namespace AST

#endif // AUC_BLOCKEXPRESSIONS_HPP
