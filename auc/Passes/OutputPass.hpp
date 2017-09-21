/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_OUTPUTPASS_HPP
#define AUC_OUTPUTPASS_HPP

#include "ASTPass.hpp"
#include "AST/common.hpp"

#include <ostream>

namespace Passes {

/// Print an AST as C code to an output stream
class OutputPass : public AST::ASTPass {

    std::ostream& stream;
    uint16_t indentWidth;

    OutputPass();
    std::ostream& indent();

public:
    OutputPass(AST::AbstractSyntaxTree& ast, std::ostream& stream);
    virtual ~OutputPass() {};

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

}; // class OutputPass

} // namespace Passes

#endif // AUC_OUTPUTPASS_HPP
