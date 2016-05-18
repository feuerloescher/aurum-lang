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
    ASTPtr<ConstIntExpr> constInt{new ConstIntExpr(2)};
    ASTPtr<ReturnExpr> ret{new ReturnExpr(constInt)};
    ASTPtr<FunctionDeclExpr> funcDecl{new FunctionDeclExpr("two", typeInt,
        VariableDefExprList{}, ImperativeExprList{ret})};

    ASTPtr<TypeExpr> typeInt2{new TypeExpr("int")};
    ASTPtr<ConstIntExpr> constInt2{new ConstIntExpr(5)};
    ASTPtr<VariableDefAssignExpr> defAssignX{
        new VariableDefAssignExpr("x", typeInt2, constInt2)};

    ASTPtr<TypeExpr> typeInt3{new TypeExpr("int")};
    ASTPtr<VariableDefExpr> defY{
        new VariableDefExpr("y", typeInt3)};

    ASTPtr<VariableExpr> varX{new VariableExpr("x")};
    ASTPtr<VariableExpr> varY{new VariableExpr("y")};

    ASTPtr<UnaryOpExpr> unaryOp{new UnaryOpExpr("-", varX)};
    ASTPtr<BinaryAssignOpExpr> binaryAssignOp{
        new BinaryAssignOpExpr("=", varY, unaryOp)};

    ASTPtr<VariableExpr> varY2{new VariableExpr("y")};
    ASTPtr<UnaryAssignOpExpr> unaryAssignOp{new UnaryAssignOpExpr("++", varY2)};

    ASTPtr<VariableExpr> varY3{new VariableExpr("y")};
    ASTPtr<ReturnExpr> ret2{new ReturnExpr(varY3)};

    ASTPtr<TypeExpr> typeInt4{new TypeExpr("int")};
    ASTPtr<FunctionDeclExpr> funcDecl2{
        new FunctionDeclExpr("main", typeInt4, VariableDefExprList{},
        ImperativeExprList{
            defAssignX, defY, binaryAssignOp, unaryAssignOp, ret2})};
    AbstractSyntaxTree ast(DeclarativeExprList{funcDecl, funcDecl2});

    PrintPass printer(std::cout);
    printer.runOn(ast);
    return 0;
}
