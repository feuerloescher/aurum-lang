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

namespace AST {

class AbstractSyntaxTree {

protected:
    DeclarationList declarations;
    ASTMap<FunctionDef*> functionDefs;
    ASTMap<ASTPtr<Type>> types;
    ASTMap<ASTPtr<MethodDef>> stdLibMethodDefs;


public:
    AbstractSyntaxTree();

    DeclarationList& getDeclarations();
    ASTMap<FunctionDef*>& getFunctionDefs();
    ASTMap<ASTPtr<Type>>& getTypes();
    ASTMap<ASTPtr<MethodDef>>& getStdLibMethodDefs();

}; // class AbstractSyntaxTree

} // namespace AST

#endif // AUC_ABSTRACTSYNTAXTREE_HPP
