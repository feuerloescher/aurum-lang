/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AbstractSyntaxTree.hpp"

using namespace AST;

DeclarationList& AbstractSyntaxTree::getDeclarations() {
    return declarations;
}

ASTMap<FunctionDef>& AbstractSyntaxTree::getFunctionDefs() {
    return functionDecls;
}

ASTMap<Type>& AbstractSyntaxTree::getTypes() {
    return types;
}

Block& AbstractSyntaxTree::getRootBlock() {
    return rootBlock;
}
