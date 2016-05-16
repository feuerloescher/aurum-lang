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
    indent() << "AbstractSyntaxTree {\n";
    indentWidth++;
    ast.runPassOnChildren(*this);
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(FunctionDeclExpr& expr) {
    indent() << "FunctionDeclExpr(" << expr.getName() << ") {\n";
    indentWidth++;
    expr.runPassOnChildren(*this);
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(ReturnExpr& expr) {
    indent() << "ReturnExpr\n";
}

void PrintPass::runOn(VariableDefExpr& expr) {
    indent() << "VariableDefExpr\n";
}
void PrintPass::runOn(VariableDefAssignExpr& expr) {
    indent() << "VariableDefAssignExpr\n";
}

void PrintPass::runOn(IfExpr& expr) {
    indent() << "IfExpr {\n";
    indentWidth++;
    expr.runPassOnChildren(*this);
    indentWidth--;
}

void PrintPass::runOn(WhileLoopExpr& expr) {
    indent() << "WhileLoopExpr {\n";
    indentWidth++;
    expr.runPassOnChildren(*this);
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(TypeExpr& expr) {
    indent() << "TypeExpr\n";
}

void PrintPass::runOn(FunctionCallExpr& expr) {
    indent() << "FunctionCallExpr {\n";
    indentWidth++;
    expr.runPassOnChildren(*this);
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(ConstIntExpr& expr) {
    indent() << "ConstIntExpr\n";
}

void PrintPass::runOn(VariableExpr& expr) {
    indent() << "VariableExpr(" << expr.getName() << ")\n";
}

void PrintPass::runOn(UnaryOpExpr& expr) {
    indent() << "UnaryOpExpr {\n";
    indentWidth++;
    expr.runPassOnChildren(*this);
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(BinaryOpExpr& expr) {
    indent() << "BinaryOpExpr {\n";
    indentWidth++;
    expr.runPassOnChildren(*this);
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(UnaryAssignOpExpr& expr) {
    indent() << "UnaryAssignOpExpr {\n";
    indentWidth++;
    expr.runPassOnChildren(*this);
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(BinaryAssignOpExpr& expr) {
    indent() << "BinaryAssignOpExpr(" << expr.getName() << ") {\n";
    indentWidth++;
    expr.runPassOnChildren(*this);
    indentWidth--;
    indent() << "}\n";
}
