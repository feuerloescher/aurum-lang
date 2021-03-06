/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPEPASS_HPP
#define AUC_TYPEPASS_HPP

#include "ASTPass.hpp"
#include "AST/common.hpp"

namespace Passes {

/// Resolve and check types of expressions
class TypePass : public AST::ASTPass {

public:
    explicit TypePass(AST::AbstractSyntaxTree& ast);
    virtual ~TypePass() {};

    void run() override;

    void runOn(AST::FunctionDecl&) override;
    void runOn(AST::FunctionDef&) override;

    void runOn(AST::ReturnStmt&) override;
    void runOn(AST::VariableDefStmt&) override;
    void runOn(AST::VariableDefAssignStmt&) override;

    void runOn(AST::Block&) override;
    void runOn(AST::IfStmt&) override;
    void runOn(AST::WhileLoop&) override;

    void runOn(AST::BasicTypeStmt&) override;

    void runOn(AST::FunctionCallExpr&) override;
    void runOn(AST::ConstIntExpr&) override;
    void runOn(AST::VariableExpr&) override;

}; // class TypePass

} // namespace Passes

#endif // AUC_TYPEPASS_HPP
