/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_DECLARATIONS_HPP
#define AUC_DECLARATIONS_HPP

#include "common.hpp"
#include "Blocks.hpp"

#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <string>
#include <vector>

namespace AST {

class Declaration {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class Declaration

typedef ASTList<Declaration> DeclarationList;


class FunctionDef : public Declaration {

protected:
    std::string name;
    ASTPtr<TypeStmt> returnTypeStmt;
    ASTList<VariableDefStmt> parameters;
    Block body;
    llvm::Function* llvmFunction;
    std::vector<llvm::Type*> parameterLLVMTypes;

public:
    FunctionDef(std::string name, ASTPtr<TypeStmt> returnTypeStmt);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<TypeStmt> getReturnTypeStmt();
    VariableDefStmtList& getParameters();
    Block& getBody();
    llvm::Function* getLLVMFunction();
    void setLLVMFunction(llvm::Function* llvmFunction);
    std::vector<llvm::Type*>& getParameterLLVMTypes();

}; // class FunctionDef


class MethodDef : public Declaration {

protected:
    std::string name;
    ASTPtr<TypeStmt> returnTypeStmt;
    ASTPtr<TypeStmt> objectTypeStmt;
    ASTList<VariableDefStmt> parameters;
    Block body;
    llvm::Function* llvmFunction;
    std::vector<llvm::Type*> parameterLLVMTypes;

public:
    MethodDef(ASTPtr<TypeStmt> returnTypeStmt, std::string name,
        ASTPtr<TypeStmt> objectTypeStmt);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<TypeStmt> getReturnTypeStmt();
    ASTPtr<TypeStmt> getObjectTypeStmt();
    VariableDefStmtList& getParameters();
    Block& getBody();
    llvm::Function* getLLVMFunction();
    void setLLVMFunction(llvm::Function* llvmFunction);
    std::vector<llvm::Type*>& getParameterLLVMTypes();

}; // class MethodDef

} // namespace AST

#endif // AUC_DECLARATIONS_HPP
