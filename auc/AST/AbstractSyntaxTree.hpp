/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ABSTRACTSYNTAXTREE_HPP
#define AUC_ABSTRACTSYNTAXTREE_HPP

#include "common.hpp"
#include "ASTMap.hpp"
#include "Declarations.hpp"
#include "ASTPass.hpp"
#include "Blocks.hpp"
#include "Type.hpp"

namespace AST {

class AbstractSyntaxTree {

protected:
    DeclarationList declarations;
    ASTMap<FunctionDef> functionDecls;
    ASTMap<Type> types;
    Block rootBlock;

public:
    DeclarationList& getDeclarations();
    ASTMap<FunctionDef>& getFunctionDefs();
    ASTMap<Type>& getTypes();
    Block& getRootBlock();

}; // class AbstractSyntaxTree

} // namespace AST

#endif // AUC_ABSTRACTSYNTAXTREE_HPP
