/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ABSTRACTSYNTAXTREE_HPP
#define AUC_ABSTRACTSYNTAXTREE_HPP

#include "common.hpp"
#include "DeclarativeExpressions.hpp"
#include "ASTPass.hpp"

namespace AST {

class AbstractSyntaxTree {

protected:
    DeclarativeExprList expressions;

public:
    AbstractSyntaxTree(DeclarativeExprList expressions);

    DeclarativeExprList& getExpressions();

}; // class AbstractSyntaxTree

} // namespace AST

#endif // AUC_ABSTRACTSYNTAXTREE_HPP
