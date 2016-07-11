/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_DECLARATIONS_HPP
#define AUC_DECLARATIONS_HPP

#include "common.hpp"
#include "Blocks.hpp"
#include "ASTElement.hpp"

#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <string>
#include <vector>

namespace AST {

class Declaration : public ASTElement {

protected:
    std::string name;
    ASTPtr<TypeStmt> returnTypeStmt;
    ASTList<VariableDefStmt> parameters;
    Block body;
    llvm::Function* llvmFunction;
    std::vector<llvm::Type*> parameterLLVMTypes;
    bool exported;

public:
    Declaration(ASTPtr<TypeStmt> returnTypeStmt, std::string name,
        CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass) = 0;

    std::string getName();
    ASTPtr<TypeStmt> getReturnTypeStmt();
    VariableDefStmtList& getParameters();
    Block& getBody();
    llvm::Function* getLLVMFunction();
    void setLLVMFunction(llvm::Function* llvmFunction);
    std::vector<llvm::Type*>& getParameterLLVMTypes();
    bool getExported();
    void setExported(bool exported);

}; // class Declaration

typedef ASTList<Declaration> DeclarationList;


class FunctionDef : public Declaration {

protected:

public:
    FunctionDef(ASTPtr<TypeStmt> returnTypeStmt, std::string name,
        CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

}; // class FunctionDef


class MethodDef : public Declaration {

protected:
    ASTPtr<TypeStmt> objectTypeStmt;

public:
    MethodDef(ASTPtr<TypeStmt> returnTypeStmt, std::string name,
        ASTPtr<TypeStmt> objectTypeStmt, CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

    ASTPtr<TypeStmt> getObjectTypeStmt();

}; // class MethodDef

} // namespace AST

#endif // AUC_DECLARATIONS_HPP
