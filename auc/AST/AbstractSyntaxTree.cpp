/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AbstractSyntaxTree.hpp"

using namespace AST;
using namespace type;

AbstractSyntaxTree::AbstractSyntaxTree() {
}

ASTElementList& AbstractSyntaxTree::getASTElements() {
    return astElements;
}

ASTMap<FunctionDef*>& AbstractSyntaxTree::getFunctionDefs() {
    return functionDefs;
}

ASTMap<TypePtr>& AbstractSyntaxTree::getTypes() {
    return types;
}

ASTList<FunctionDecl>& AbstractSyntaxTree::getStdLibFunctionDecls() {
    return stdLibFunctionDecls;
}

ASTMap<FunctionDefPtr>& AbstractSyntaxTree::getStdLibFunctionDefs() {
    return stdLibFunctionDefs;
}
