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

    virtual void runOn(AST::FunctionDeclExpr& expr);

    virtual void runOn(AST::ReturnExpr& expr);
    virtual void runOn(AST::VariableDefExpr& expr);
    virtual void runOn(AST::VariableDefAssignExpr& expr);

    virtual void runOn(AST::IfExpr& expr);
    virtual void runOn(AST::WhileLoopExpr& expr);

    virtual void runOn(AST::TypeExpr& expr);

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
