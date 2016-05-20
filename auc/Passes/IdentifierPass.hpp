/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_IDENTIFIERPASS_HPP
#define AUC_IDENTIFIERPASS_HPP

#include "AST/ASTPass.hpp"
#include "AST/Declarations.hpp"
#include "AST/common.hpp"

namespace Passes {

class IdentifierPass : public AST::ASTPass {

public:
    IdentifierPass(AST::AbstractSyntaxTree& ast);

    virtual void run();

    virtual void runOn(AST::FunctionDecl& expr);

    virtual void runOn(AST::ReturnStmt& expr);
    virtual void runOn(AST::VariableDefStmt& expr);
    virtual void runOn(AST::VariableDefAssignStmt& expr);

    virtual void runOn(AST::IfStmt& expr);
    virtual void runOn(AST::WhileLoop& expr);

    virtual void runOn(AST::FunctionCallExpr& expr);
    virtual void runOn(AST::ConstIntExpr& expr);
    virtual void runOn(AST::VariableExpr& expr);
    virtual void runOn(AST::UnaryOpExpr& expr);
    virtual void runOn(AST::BinaryOpExpr& expr);
    virtual void runOn(AST::UnaryAssignOpExpr& expr);
    virtual void runOn(AST::BinaryAssignOpExpr& expr);

}; // class IdentifierPass

} // namespace Passes

#endif // AUC_IDENTIFIERPASS_HPP
