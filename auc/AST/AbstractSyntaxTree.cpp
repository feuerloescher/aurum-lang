/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AbstractSyntaxTree.hpp"

using namespace AST;

AbstractSyntaxTree::AbstractSyntaxTree() : irBuilder(llvmContext) {
    llvmModule = llvm::make_unique<llvm::Module>("llvm module", llvmContext);
}

DeclarationList& AbstractSyntaxTree::getDeclarations() {
    return declarations;
}

ASTMap<FunctionDef*>& AbstractSyntaxTree::getFunctionDefs() {
    return functionDefs;
}

ASTMap<ASTPtr<Type>>& AbstractSyntaxTree::getTypes() {
    return types;
}

llvm::IRBuilder<>& AbstractSyntaxTree::getIRBuilder() {
    return irBuilder;
}

llvm::LLVMContext& AbstractSyntaxTree::getLLVMContext() {
    return llvmContext;
}

llvm::Module& AbstractSyntaxTree::getLLVMModule() {
    return *llvmModule;
}
