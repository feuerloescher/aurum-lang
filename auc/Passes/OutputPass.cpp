/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include <AST/Errors.hpp>
#include "OutputPass.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/TypeStmt.hpp"
#include "AST/Expressions.hpp"

using namespace AST;
using namespace Passes;

OutputPass::OutputPass(AbstractSyntaxTree& ast, std::ostream& stream)
        : ASTPass(ast), stream(stream) {
    indentWidth = 0;
}

std::ostream& OutputPass::indent() {
    for (int i = 0; i < indentWidth; i++) {
        stream << "  ";
    }
    return stream;
}

void OutputPass::run() {
    stream << "// Aurum to C transpiled code\n#define uint32 int\n";
    for (ASTElementPtr decl : ast.getASTElements()) {
        stream << "\n";
        indent();
        decl->runPass(*this);
        stream << "\n";
    }
    indent() << "\n// End of C code\n";
}

void OutputPass::runOn(AST::FunctionDecl& funcDecl) {
    throw std::runtime_error("OutputPass::runOn(FunctionDecl) not implemented");
}

void OutputPass::runOn(FunctionDef& func) {
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

void OutputPass::runOn(ReturnStmt& stmt) {
    stream << "return ";
    stmt.getValue()->runPass(*this);
}

void OutputPass::runOn(VariableDefStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stream << " " << stmt.getName();
}

void OutputPass::runOn(VariableDefAssignStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stream << " " << stmt.getName() << " = ";
    stmt.getValue()->runPass(*this);
}

void OutputPass::runOn(Block& stmt) {
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

void OutputPass::runOn(IfStmt& stmt) {
    stream << "if (";
    stmt.getCondition()->runPass(*this);
    stream << ") ";
    stmt.getBody()->runPass(*this);
}

void OutputPass::runOn(WhileLoop& stmt) {
    stream << "while (";
    stmt.getCondition()->runPass(*this);
    stream << ") ";
    stmt.getBody().runPass(*this);
}

void OutputPass::runOn(BasicTypeStmt& stmt) {
    stream << stmt.getName();
    if (stmt.getIsReference()) {
        stream << '&';
    }
}

void OutputPass::runOn(FunctionCallExpr& stmt) {
    stream << stmt.getName() << "(";
    bool first = true;
    auto paramIter = stmt.getFunctionDecl()->getParameters().begin();
    unsigned int i = 0;
    for (ExpressionPtr expr : stmt.getArgs()) {
        if (!first) {
            stream << ", ";
        }
        first = false;
        if ((*paramIter)->getTypeStmt()->getIsReference()) {
            if (expr->getIsReference()) {
                // nothing to do
            } else if (expr->getIsReferenceable()) {
                // take a reference of the expression
                stream << '&';
            } else {
                // this should already be caught in TypePass
                throw AST::ArgumentReferenceError(expr->getCodeLocation(), stmt.getName(), i, (*paramIter)->getName());
            }
        }
        expr->runPass(*this);
        ++paramIter;
        i++;
    }
    stream << ")";
}

void OutputPass::runOn(ConstIntExpr& stmt) {
    stream << stmt.getValueStr();
}

void OutputPass::runOn(VariableExpr& stmt) {
    stream << stmt.getName();
}
