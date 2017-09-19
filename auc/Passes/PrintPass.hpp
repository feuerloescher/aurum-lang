/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_PRINTPASS_HPP
#define AUC_PRINTPASS_HPP

#include "ASTPass.hpp"
#include "AST/common.hpp"

#include <ostream>

namespace Passes {

/// Print an AST with type information and indentation to an output stream
class PrintPass : public AST::ASTPass {

    std::ostream& stream;
    uint16_t indentWidth;

    PrintPass();
    std::ostream& indent();

public:
    PrintPass(AST::AbstractSyntaxTree& ast, std::ostream& stream);
    virtual ~PrintPass() {};

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

}; // class PrintPass

} // namespace Passes

#endif // AUC_PRINTPASS_HPP
