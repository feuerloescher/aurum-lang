/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AST/AbstractSyntaxTree.hpp"
#include "AST/ValueExpressions.hpp"
#include "Passes/PrintPass.hpp"

#include <iostream>

using namespace AST;
using namespace Passes;

int main() {
    ASTPtr<VariableExpr> varExpr1{new VariableExpr("var1")};
    ASTPtr<VariableExpr> varExpr2{new VariableExpr("var2")};
    ASTPtr<BinaryAssignOpExpr> opExpr{
        new BinaryAssignOpExpr("+=", varExpr1, varExpr2)};
    ASTPtr<FunctionDeclExpr> funcExpr{
        new FunctionDeclExpr("main", ImperativeExprList{opExpr})};
    AbstractSyntaxTree ast(DeclarativeExprList{funcExpr});

    PrintPass printer(std::cout);
    printer.runOn(ast);
    return 0;
}
