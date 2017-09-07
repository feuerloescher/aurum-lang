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
#include "AST/TypeStmt.hpp"
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
    stream << "// Aurum to C transpiled code\n#define uint32 int\n";
    for (ASTElementPtr decl : ast.getASTElements()) {
        stream << "\n";
        indent();
        decl->runPass(*this);
        stream << "\n";
    }
    indent() << "\n// End of C code\n";
}

void PrintPass::runOn(AST::FunctionDecl& funcDecl) {
    throw std::runtime_error("PrintPass::runOn(FunctionDecl) not implemented");
}

void PrintPass::runOn(FunctionDef& func) {
    func.getFunctionDecl()->getReturnTypeStmt()->runPass(*this);
    stream << " " << func.getName() << "(";
    bool first = true;
    for (VariableDefStmtPtr innerStmt : func.getFunctionDecl()->getParameters()) {
        if (!first) {
            stream << ", ";
        }
        first = false;
        innerStmt->runPass(*this);
    }
    stream << ") ";
    func.getBody()->runPass(*this);
}

void PrintPass::runOn(ReturnStmt& stmt) {
    stream << "return ";
    stmt.getValue()->runPass(*this);
}

void PrintPass::runOn(VariableDefStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stream << " " << stmt.getName();
}

void PrintPass::runOn(VariableDefAssignStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stream << " " << stmt.getName() << " = ";
    stmt.getValue()->runPass(*this);
}

void PrintPass::runOn(Block& stmt) {
    stream << "{\n";
    indentWidth++;
    for (StatementPtr innerStmt : stmt.getStatements()) {
        indent();
        innerStmt->runPass(*this);
        stream << ";\n";
    }
    indentWidth--;
    indent() << "}";
}

void PrintPass::runOn(IfStmt& stmt) {
    stream << "if (";
    stmt.getCondition()->runPass(*this);
    stream << ") ";
    stmt.getBody()->runPass(*this);
}

void PrintPass::runOn(WhileLoop& stmt) {
    stream << "while (";
    stmt.getCondition()->runPass(*this);
    stream << ") ";
    stmt.getBody().runPass(*this);
}

void PrintPass::runOn(TypeStmt& stmt) {
    stream << stmt.getName();
}

void PrintPass::runOn(FunctionCallExpr& stmt) {
    stream << stmt.getName() << "(";
    bool first = true;
    for (ExpressionPtr expr : stmt.getArgs()) {
        if (!first) {
            stream << ", ";
        }
        first = false;
        expr->runPass(*this);
    }
    stream << ")";
}

void PrintPass::runOn(ConstIntExpr& stmt) {
    stream << stmt.getValueStr();
}

void PrintPass::runOn(VariableExpr& stmt) {
    stream << stmt.getName();
}
