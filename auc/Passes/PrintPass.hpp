/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_PRINTPASS_HPP
#define AUC_PRINTPASS_HPP

#include "AST/ASTPass.hpp"

#include <ostream>

namespace Passes {

class PrintPass : public AST::ASTPass {

    std::ostream& stream;
    uint16_t indentWidth;

    PrintPass();
    std::ostream& indent();

public:
    PrintPass(std::ostream& stream);

    virtual void runOn(AST::AbstractSyntaxTree& ast);

    virtual void runOn(AST::FunctionDecl& expr);

    virtual void runOn(AST::ReturnStmt& expr);
    virtual void runOn(AST::VariableDefStmt& expr);
    virtual void runOn(AST::VariableDefAssignStmt& expr);

    virtual void runOn(AST::IfStmt& expr);
    virtual void runOn(AST::WhileLoop& expr);

    virtual void runOn(AST::Type& expr);

    virtual void runOn(AST::FunctionCallExpr& expr);
    virtual void runOn(AST::ConstIntExpr& expr);
    virtual void runOn(AST::VariableExpr& expr);
    virtual void runOn(AST::UnaryOpExpr& expr);
    virtual void runOn(AST::BinaryOpExpr& expr);
    virtual void runOn(AST::UnaryAssignOpExpr& expr);
    virtual void runOn(AST::BinaryAssignOpExpr& expr);

}; // class PrintPass

} // namespace Passes

#endif // AUC_PRINTPASS_HPP
