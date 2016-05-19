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
    AbstractSyntaxTree ast(DeclarativeExprList{});

    ASTPtr<VariableDefExpr> variable{
        new VariableDefExpr("var", ASTPtr<TypeExpr>{new TypeExpr("int")})};
    ASTPtr<FunctionDeclExpr> funcDecl{new FunctionDeclExpr("foo",
        ASTPtr<TypeExpr>{new TypeExpr("int")},
        VariableDefExprList{variable}, ImperativeExprList{})};
    ast.getExpressions().push_back(funcDecl);

    ASTPtr<ConstIntExpr> constInt{new ConstIntExpr(5)};
    ASTPtr<BinaryOpExpr> binaryOp{new BinaryOpExpr("+",
        ASTPtr<VariableExpr>{new VariableExpr("var")},
        constInt)};
    ASTPtr<ReturnExpr> ret{new ReturnExpr(binaryOp)};
    funcDecl->getBody().push_back(ret);

    ASTPtr<TypeExpr> typeInt2{new TypeExpr("int")};
    ASTPtr<FunctionDeclExpr> funcDecl2{
        new FunctionDeclExpr("main", typeInt2, VariableDefExprList{},
        ImperativeExprList{})};
    ast.getExpressions().push_back(funcDecl2);

    ASTPtr<TypeExpr> typeInt3{new TypeExpr("int")};
    ASTPtr<FunctionCallExpr> funcCall{new FunctionCallExpr("foo",
        ASTList<ValueExpr>{ASTPtr<ValueExpr>{new ConstIntExpr(5)}})};
    ASTPtr<VariableDefAssignExpr> defAssignX{
        new VariableDefAssignExpr("x", typeInt3, funcCall)};
    funcDecl2->getBody().push_back(defAssignX);

    ASTPtr<TypeExpr> typeInt4{new TypeExpr("int")};
    ASTPtr<VariableDefExpr> defY{
        new VariableDefExpr("y", typeInt4)};
    funcDecl2->getBody().push_back(defY);

    ASTPtr<VariableExpr> varX{new VariableExpr("x")};
    ASTPtr<VariableExpr> varY{new VariableExpr("y")};
    ASTPtr<UnaryOpExpr> unaryOp{new UnaryOpExpr("-", varX)};
    ASTPtr<BinaryAssignOpExpr> binaryAssignOp{
        new BinaryAssignOpExpr("=", varY, unaryOp)};
    funcDecl2->getBody().push_back(binaryAssignOp);

    ASTPtr<VariableExpr> varY2{new VariableExpr("y")};
    ASTPtr<UnaryAssignOpExpr> unaryAssignOp{new UnaryAssignOpExpr("++", varY2)};
    funcDecl2->getBody().push_back(unaryAssignOp);

    ASTPtr<VariableExpr> varY3{new VariableExpr("y")};
    ASTPtr<ReturnExpr> ret2{new ReturnExpr(varY3)};
    funcDecl2->getBody().push_back(ret2);

    PrintPass printer(std::cout);
    printer.runOn(ast);
    return 0;
}
