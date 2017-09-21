/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_IDENTIFIERPASS_HPP
#define AUC_IDENTIFIERPASS_HPP

#include "ASTPass.hpp"
#include "AST/Declarations.hpp"
#include "AST/common.hpp"

namespace Passes {

/// Resolve string identifiers of variables and functions
class IdentifierPass : public AST::ASTPass {

protected:
    AST::Block* currentBlock;
    bool onlyInsertDeclarations;

public:
    explicit IdentifierPass(AST::AbstractSyntaxTree& ast);
    virtual ~IdentifierPass() {};

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

}; // class IdentifierPass

} // namespace Passes

#endif // AUC_IDENTIFIERPASS_HPP
