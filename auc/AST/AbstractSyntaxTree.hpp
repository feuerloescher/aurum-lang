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
#include "Types/Type.hpp"

namespace AST {

class AbstractSyntaxTree {

protected:
    ASTElementList astElements;
    ASTMap<FunctionDef*> functionDefs;
    ASTMap<type::TypePtr> types;
#warning TODO: add a voidType shared_ptr for quicker access

    // storage for shared_ptrs (no Statements in AST that hold the shared_ptrs)
    ASTList<FunctionDecl> stdLibFunctionDecls;
    ASTMap<FunctionDefPtr> stdLibFunctionDefs;


public:
    AbstractSyntaxTree();

    ASTElementList& getASTElements();
    ASTMap<FunctionDef*>& getFunctionDefs();
    ASTMap<type::TypePtr>& getTypes();
    ASTList<FunctionDecl>& getStdLibFunctionDecls();
    ASTMap<FunctionDefPtr>& getStdLibFunctionDefs();

}; // class AbstractSyntaxTree

} // namespace AST

#endif // AUC_ABSTRACTSYNTAXTREE_HPP
