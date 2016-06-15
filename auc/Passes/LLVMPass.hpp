/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_LLVMPASS_HPP
#define AUC_LLVMPASS_HPP

#include "AST/ASTPass.hpp"
#include "AST/common.hpp"

#include <llvm/IR/LLVMContext.h>

namespace Passes {

/// Generate LLVM Intermediate Representation
class LLVMPass : public AST::ASTPass {

protected:
    llvm::LLVMContext llvmContext;

public:
    LLVMPass(AST::AbstractSyntaxTree& ast);

    virtual void run();

    virtual void runOn(AST::FunctionDef&);

    virtual void runOn(AST::ReturnStmt&);
    virtual void runOn(AST::VariableDefStmt&);
    virtual void runOn(AST::VariableDefAssignStmt&);

    virtual void runOn(AST::Block&);
    virtual void runOn(AST::IfStmt&);
    virtual void runOn(AST::WhileLoop&);

    virtual void runOn(AST::TypeStmt&);

    virtual void runOn(AST::FunctionCallExpr&);
    virtual void runOn(AST::ConstUInt32Expr&);
    virtual void runOn(AST::VariableExpr&);
    virtual void runOn(AST::UnaryOpExpr&);
    virtual void runOn(AST::BinaryOpExpr&);
    virtual void runOn(AST::UnaryAssignOpExpr&);
    virtual void runOn(AST::BinaryAssignOpExpr&);

}; // class LLVMPass

} // namespace Passes

#endif // AUC_LLVMPASS_HPP