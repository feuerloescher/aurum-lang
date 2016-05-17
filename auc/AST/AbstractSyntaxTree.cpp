/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AbstractSyntaxTree.hpp"

using namespace AST;

AbstractSyntaxTree::AbstractSyntaxTree(DeclarativeExprList expressions)
    : expressions(expressions) {
}

void AbstractSyntaxTree::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void AbstractSyntaxTree::runPassOnChildren(ASTPass& pass) {
    for (ASTPtr<DeclarativeExpr> expression : expressions) {
        expression->runPass(pass);
    }
}