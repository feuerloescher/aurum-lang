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
    IdentifierPass(AST::AbstractSyntaxTree& ast);
    virtual ~IdentifierPass() {};

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
    virtual void runOn(AST::ConstIntExpr&);
    virtual void runOn(AST::VariableExpr&);

}; // class IdentifierPass

} // namespace Passes

#endif // AUC_IDENTIFIERPASS_HPP
