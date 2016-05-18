/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AST/AbstractSyntaxTree.hpp"
#include "AST/ValueExpressions.hpp"
#include "AST/TypeExpr.hpp"
#include "Passes/PrintPass.hpp"

#include <iostream>

using namespace AST;
using namespace Passes;

int main() {
    ASTPtr<TypeExpr> typeInt{new TypeExpr("int")};
    ASTPtr<ConstIntExpr> constInt{new ConstIntExpr(5)};
    ASTPtr<VariableDefAssignExpr> defAssignX{
        new VariableDefAssignExpr("x", typeInt, constInt)};

    ASTPtr<TypeExpr> typeInt2{new TypeExpr("int")};
    ASTPtr<VariableDefExpr> defY{
        new VariableDefExpr("y", typeInt2)};

    ASTPtr<VariableExpr> varX{new VariableExpr("x")};
    ASTPtr<VariableExpr> varY{new VariableExpr("y")};

    ASTPtr<UnaryOpExpr> unaryOp{new UnaryOpExpr("-", varX)};
    ASTPtr<BinaryAssignOpExpr> assignOp{
        new BinaryAssignOpExpr("=", varY, unaryOp)};

    ASTPtr<VariableExpr> varY2{new VariableExpr("y")};
    ASTPtr<ReturnExpr> ret{new ReturnExpr(varY2)};

    ASTPtr<FunctionDeclExpr> funcExpr{
        new FunctionDeclExpr("main", ImperativeExprList{
            defAssignX, defY, assignOp, ret})};
    AbstractSyntaxTree ast(DeclarativeExprList{funcExpr});

    PrintPass printer(std::cout);
    printer.runOn(ast);
    return 0;
}
