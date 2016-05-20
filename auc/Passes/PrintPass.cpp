/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "PrintPass.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/Type.hpp"
#include "AST/Expressions.hpp"

using namespace AST;
using namespace Passes;

PrintPass::PrintPass(AbstractSyntaxTree& ast, std::ostream& stream)
    : ASTPass(ast), stream(stream) {
    indentWidth = 0;
}

std::ostream& PrintPass::indent() {
    for (int i = 0; i < indentWidth; i++) {
        stream << "  ";
    }
    return stream;
}

void PrintPass::run() {
    stream << "AbstractSyntaxTree {";
    indentWidth++;
    for (ASTPtr<Declaration> decl : ast.getDeclarations()) {
        stream << "\n";
        indent();
        decl->runPass(*this);
        stream << "\n";
    }
    indentWidth--;
    indent() << "}\n";
}

void PrintPass::runOn(FunctionDef& decl) {
    stream << "FunctionDef(";
    decl.getType()->runPass(*this);
    stream << " " << decl.getName() << "(";
    bool first = true;
    for (ASTPtr<VariableDefStmt> innerStmt : decl.getParameters()) {
        if (!first) {
            stream << ", ";
        }
        first = false;
        innerStmt->runPass(*this);
    }
    stream << ")) ";
    decl.getBody().runPass(*this);
}

void PrintPass::runOn(ReturnStmt& stmt) {
    stream << "ReturnStmt(";
    stmt.getValue()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(VariableDefStmt& stmt) {
    stream << "VariableDefStmt(";
    stmt.getType()->runPass(*this);
    stream << " " << stmt.getName() << ")";
}

void PrintPass::runOn(VariableDefAssignStmt& stmt) {
    stream << "VariableDefAssignStmt(";
    stmt.getType()->runPass(*this);
    stream << " " << stmt.getName() << " = ";
    stmt.getValue()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(Block& stmt) {
    stream << "{\n";
    indentWidth++;
    for (ASTPtr<Statement> innerStmt : stmt.getStatements()) {
        indent();
        innerStmt->runPass(*this);
        stream << "\n";
    }
    indentWidth--;
    indent() << "}";
}

void PrintPass::runOn(IfStmt& stmt) {
    stream << "IfStmt(";
    stmt.getCondition()->runPass(*this);
    stream << ") ";
    stmt.getBody().runPass(*this);
}

void PrintPass::runOn(WhileLoop& stmt) {
    stream << "WhileLoop(";
    stmt.getCondition()->runPass(*this);
    stream << ") ";
    stmt.getBody().runPass(*this);
}

void PrintPass::runOn(Type& stmt) {
    stream << "Type(" << stmt.getName() << ")";
}

void PrintPass::runOn(FunctionCallExpr& stmt) {
    stream << "FunctionCallExpr(" << stmt.getName() << "(";
    bool first = true;
    for (ASTPtr<Expression> expr : stmt.getParameters()) {
        if (!first) {
            stream << ", ";
        }
        first = false;
        expr->runPass(*this);
    }
    stream << "))";
}

void PrintPass::runOn(ConstIntExpr& stmt) {
    stream << "ConstIntExpr(" << stmt.getValue() << ")";
}

void PrintPass::runOn(VariableExpr& stmt) {
    stream << "VariableExpr(" << stmt.getName() << ")";
}

void PrintPass::runOn(UnaryOpExpr& stmt) {
    stream << "UnaryOpExpr(" << stmt.getName();
    stmt.getOperand()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(BinaryOpExpr& stmt) {
    stream << "BinaryOpExpr(";
    stmt.getOperand1()->runPass(*this);
    stream << " " << stmt.getName() << " ";
    stmt.getOperand2()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(UnaryAssignOpExpr& stmt) {
    stream << "UnaryAssignOpExpr(" << stmt.getName();
    stmt.getVariable()->runPass(*this);
    stream << ")";
}

void PrintPass::runOn(BinaryAssignOpExpr& stmt) {
    stream << "BinaryAssignOpExpr(";
    stmt.getVariable()->runPass(*this);
    stream << " " << stmt.getName() << " ";
    stmt.getOperand()->runPass(*this);
    stream << ")";
}
