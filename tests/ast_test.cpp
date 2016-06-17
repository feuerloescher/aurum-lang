/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AST/AbstractSyntaxTree.hpp"
#include "AST/ScalarTypes.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/TypeStmt.hpp"
#include "AST/Expressions.hpp"
#include "Passes/PrintPass.hpp"
#include "Passes/StdLibPass.hpp"
#include "Passes/IdentifierPass.hpp"
#include "Passes/TypePass.hpp"
#include "Passes/LLVMPass.hpp"
#include "Passes/IRExportPass.hpp"

#include <iostream>

using namespace AST;
using namespace Passes;
using namespace std;

int main() {
    AbstractSyntaxTree ast;

    auto variable = make_shared<VariableDefStmt>("var",
        make_shared<TypeStmt>("uint32"));
    auto funcDecl = make_shared<FunctionDef>("foo",
        make_shared<TypeStmt>("uint32"));
    funcDecl->getParameters().push_back(variable);
    ast.getDeclarations().push_back(funcDecl);

    auto addOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("var"), "+");
    addOp->getParameters().push_back(make_shared<ConstUInt32Expr>(5));
    auto ret = make_shared<ReturnStmt>(addOp);
    funcDecl->getBody().push_back(ret);

    auto mainDecl = make_shared<FunctionDef>("main",
        make_shared<TypeStmt>("uint32"));
    ast.getDeclarations().push_back(mainDecl);

    auto funcCall = make_shared<FunctionCallExpr>("foo");
    funcCall->getParameters().push_back(make_shared<ConstUInt32Expr>(5));
    auto defAssignX = make_shared<VariableDefAssignStmt>("x",
        make_shared<TypeStmt>("uint32"), funcCall);
    mainDecl->getBody().push_back(defAssignX);

    auto defY = make_shared<VariableDefStmt>("y",
        make_shared<TypeStmt>("uint32"));
    mainDecl->getBody().push_back(defY);

    auto negateOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("x"), "-");
    auto assignOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("y"), "=");
    assignOp->getParameters().push_back(negateOp);
    mainDecl->getBody().push_back(assignOp);

    auto unaryAssignOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("y"), "++");
    mainDecl->getBody().push_back(unaryAssignOp);

    ASTPtr<VariableExpr> varY3{new VariableExpr("y")};
    auto ret2 = make_shared<ReturnStmt>(make_shared<VariableExpr>("y"));
    mainDecl->getBody().push_back(ret2);

    StdLibPass stdLibPass(ast);
    stdLibPass.run();

    IdentifierPass identifier(ast);
    identifier.run();

    TypePass typePass(ast);
    typePass.run();

    PrintPass printer(ast, std::cout);
    printer.run();

    LLVMPass llvmPass(ast);
    llvmPass.run();

    IRExportPass exportPass(ast);
    exportPass.run();
    return 0;
}
