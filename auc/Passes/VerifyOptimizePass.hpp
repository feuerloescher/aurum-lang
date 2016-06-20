/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_VERIFYOPTIMIZEPASS_HPP
#define AUC_VERIFYOPTIMIZEPASS_HPP

#include "AST/ASTPass.hpp"
#include "AST/common.hpp"

#include <llvm/IR/LegacyPassManager.h>

namespace Passes {

/// Verify and optimize LLVM IR
class VerifyOptimizePass : public AST::ASTPass {

protected:
    std::unique_ptr<llvm::legacy::FunctionPassManager> functionPassMgr;
    std::unique_ptr<llvm::legacy::PassManager> modulePassMgr;

public:
    VerifyOptimizePass(AST::AbstractSyntaxTree& ast);

    virtual void run();

    virtual void runOn(AST::FunctionDef&);
    virtual void runOn(AST::MethodDef&);

    virtual void runOn(AST::ReturnStmt&);
    virtual void runOn(AST::VariableDefStmt&);
    virtual void runOn(AST::VariableDefAssignStmt&);

    virtual void runOn(AST::Block&);
    virtual void runOn(AST::IfStmt&);
    virtual void runOn(AST::WhileLoop&);

    virtual void runOn(AST::TypeStmt&);

    virtual void runOn(AST::FunctionCallExpr&);
    virtual void runOn(AST::MethodCallExpr&);
    virtual void runOn(AST::ConstUInt32Expr&);
    virtual void runOn(AST::VariableExpr&);

}; // class VerifyOptimizePass

} // namespace Passes

#endif // AUC_VERIFYOPTIMIZEPASS_HPP
