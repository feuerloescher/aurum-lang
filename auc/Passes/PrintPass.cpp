/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "PrintPass.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/DeclarativeExpressions.hpp"
#include "AST/ImperativeExpressions.hpp"
#include "AST/BlockExpressions.hpp"
#include "AST/TypeExpr.hpp"
#include "AST/ValueExpressions.hpp"

using namespace AST;
using namespace Passes;

PrintPass::PrintPass(std::ostream& stream) : stream(stream) {
    indentWidth = 0;
}

std::ostream& PrintPass::indent() {
    for (int i = 0; i < indentWidth; i++) {
        stream << "  ";
    }
    return stream;
}

void PrintPass::runOn(AbstractSyntaxTree& ast) {
    stream << "AbstractSyntaxTree {";
    indentWidth++;
    for (ASTPtr<DeclarativeExpr> expr : ast.getExpressions()) {
        stream << "\n";
        indent();
        expr->runPass(*this);
        stream << "\n";
    }
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(FunctionDeclExpr& expr) {
    stream << "FunctionDeclExpr(" << expr.getName();
    for (ASTPtr<VariableDefExpr> innerExpr : expr.getParameters()) {
        stream << "; ";
        innerExpr->runPass(*this);
    }
    stream << ") {\n";
    indentWidth++;
    for (ASTPtr<ImperativeExpr> innerExpr : expr.getBody()) {
        indent();
        innerExpr->runPass(*this);
        stream << "\n";
    }
    indentWidth--;
    indent() << "}";
}

void PrintPass::runOn(ReturnExpr& expr) {
    stream << "ReturnExpr(";
    expr.getValue()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(VariableDefExpr& expr) {
    stream << "VariableDefExpr(";
    expr.getType()->runPass(*this);
    stream << " " << expr.getName() << ")";
}
void PrintPass::runOn(VariableDefAssignExpr& expr) {
    stream << "VariableDefAssignExpr(";
    expr.getType()->runPass(*this);
    stream << " " << expr.getName() << " = ";
    expr.getValue()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(IfExpr& expr) {
    stream << "IfExpr {\n";
    indentWidth++;
    for (ASTPtr<ImperativeExpr> innerExpr : expr.getBody()) {
        indent();
        innerExpr->runPass(*this);
        stream << "\n";
    }
    indentWidth--;
    indent() << "}";
}

void PrintPass::runOn(WhileLoopExpr& expr) {
    stream << "WhileLoopExpr {\n";
    indentWidth++;
    for (ASTPtr<ImperativeExpr> innerExpr : expr.getBody()) {
        indent();
        innerExpr->runPass(*this);
        stream << "\n";
    }
    indentWidth--;
    indent() << "}";
}

void PrintPass::runOn(TypeExpr& expr) {
    stream << "TypeExpr(" << expr.getName() << ")";
}

void PrintPass::runOn(FunctionCallExpr& expr) {
    stream << "FunctionCallExpr(";
    indentWidth++;
    for (ASTPtr<ValueExpr> innerExpr : expr.getParameters()) {
        indent();
        innerExpr->runPass(*this);
        stream << "\n";
    }
    indentWidth--;
    indent() << ")\n";
}

void PrintPass::runOn(ConstIntExpr& expr) {
    stream << "ConstIntExpr(" << expr.getValue() << ")";
}

void PrintPass::runOn(VariableExpr& expr) {
    stream << "VariableExpr(" << expr.getName() << ")";
}

void PrintPass::runOn(UnaryOpExpr& expr) {
    stream << "UnaryOpExpr(" << expr.getName();
    expr.getOperand()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(BinaryOpExpr& expr) {
    stream << "BinaryOpExpr(";
    expr.getOperand1()->runPass(*this);
    stream << " " << expr.getName() << " ";
    expr.getOperand2()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(UnaryAssignOpExpr& expr) {
    stream << "UnaryAssignOpExpr(" << expr.getName();
    expr.getVariable()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(BinaryAssignOpExpr& expr) {
    stream << "BinaryAssignOpExpr(";
    expr.getVariable()->runPass(*this);
    stream << " " << expr.getName() << " ";
    expr.getOperand()->runPass(*this);
    stream << ")";
}
