/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/Type.hpp"
#include "AST/Expressions.hpp"
#include "Passes/PrintPass.hpp"

#include <iostream>

using namespace AST;
using namespace Passes;
using namespace std;

int main() {
    AbstractSyntaxTree ast;

    auto variable = make_shared<VariableDefStmt>("var",
        make_shared<Type>("int"));
    auto funcDecl = make_shared<FunctionDecl>("foo", make_shared<Type>("int"));
    funcDecl->getParameters().push_back(variable);
    ast.getExpressions().push_back(funcDecl);

    auto binaryOp = make_shared<BinaryOpExpr>("+",
        make_shared<VariableExpr>("var"), make_shared<ConstIntExpr>(5));
    auto ret = make_shared<ReturnStmt>(binaryOp);
    funcDecl->getBody().push_back(ret);

    auto mainDecl = make_shared<FunctionDecl>("main", make_shared<Type>("int"));
    ast.getExpressions().push_back(mainDecl);

    auto funcCall = make_shared<FunctionCallExpr>("foo");
    funcCall->getParameters().push_back(make_shared<ConstIntExpr>(5));
    auto defAssignX = make_shared<VariableDefAssignStmt>("x",
        make_shared<Type>("int"), funcCall);
    mainDecl->getBody().push_back(defAssignX);

    auto defY = make_shared<VariableDefStmt>("y", make_shared<Type>("int"));
    mainDecl->getBody().push_back(defY);

    auto unaryOp = make_shared<UnaryOpExpr>("-",
        make_shared<VariableExpr>("x"));
    auto binaryAssignOp = make_shared<BinaryAssignOpExpr>("=",
        make_shared<VariableExpr>("y"), unaryOp);
    mainDecl->getBody().push_back(binaryAssignOp);

    auto unaryAssignOp = make_shared<UnaryAssignOpExpr>("++",
        make_shared<VariableExpr>("y"));
    mainDecl->getBody().push_back(unaryAssignOp);

    ASTPtr<VariableExpr> varY3{new VariableExpr("y")};
    auto ret2 = make_shared<ReturnStmt>(make_shared<VariableExpr>("y"));
    mainDecl->getBody().push_back(ret2);

    PrintPass printer(std::cout);
    printer.runOn(ast);
    return 0;
}
