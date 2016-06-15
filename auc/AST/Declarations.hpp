/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_DECLARATIONS_HPP
#define AUC_DECLARATIONS_HPP

#include "common.hpp"
#include "Blocks.hpp"
#include "ASTPass.hpp"

#include <llvm/IR/Function.h>
#include <string>

namespace AST {

class Declaration {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class Declaration

typedef ASTList<Declaration> DeclarationList;


class FunctionDef : public Declaration {

protected:
    std::string name;
    ASTPtr<TypeStmt> type;
    ASTList<VariableDefStmt> parameters;
    Block body;
    llvm::Function* llvmFunction;

public:
    FunctionDef(std::string name, ASTPtr<TypeStmt> type);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<TypeStmt> getTypeStmt();
    VariableDefStmtList& getParameters();
    Block& getBody();
    llvm::Function* getLLVMFunction();
    void setLLVMFunction(llvm::Function* llvmFunction);

}; // class FunctionDef

} // namespace AST

#endif // AUC_DECLARATIONS_HPP
