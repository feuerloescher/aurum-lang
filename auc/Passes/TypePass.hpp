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
    TypePass(AST::AbstractSyntaxTree& ast);
    virtual ~TypePass() {};

    virtual void run();

    virtual void runOn(AST::FunctionDecl&);
    virtual void runOn(AST::FunctionDef&);

    virtual void runOn(AST::ReturnStmt&);
    virtual void runOn(AST::VariableDefStmt&);
    virtual void runOn(AST::VariableDefAssignStmt&);

    virtual void runOn(AST::Block&);
    virtual void runOn(AST::IfStmt&);
    virtual void runOn(AST::WhileLoop&);

    virtual void runOn(AST::BasicTypeStmt&);

    virtual void runOn(AST::FunctionCallExpr&);
    virtual void runOn(AST::ConstIntExpr&);
    virtual void runOn(AST::VariableExpr&);

}; // class TypePass

} // namespace Passes

#endif // AUC_TYPEPASS_HPP
