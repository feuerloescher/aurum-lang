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

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace AST {

class AbstractSyntaxTree {

protected:
    DeclarationList declarations;
    ASTMap<FunctionDef*> functionDecls;
    ASTMap<ASTPtr<Type>> types;

    llvm::LLVMContext llvmContext;
    llvm::IRBuilder<> irBuilder;
    std::unique_ptr<llvm::Module> llvmModule;


public:
    AbstractSyntaxTree();

    DeclarationList& getDeclarations();
    ASTMap<FunctionDef*>& getFunctionDefs();
    ASTMap<ASTPtr<Type>>& getTypes();
    llvm::LLVMContext& getLLVMContext();
    llvm::IRBuilder<>& getIRBuilder();
    llvm::Module& getLLVMModule();

}; // class AbstractSyntaxTree

} // namespace AST

#endif // AUC_ABSTRACTSYNTAXTREE_HPP
