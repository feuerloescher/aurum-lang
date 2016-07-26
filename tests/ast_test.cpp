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
#include "Passes/VerifyOptimizePass.hpp"
#include "Passes/IRExportPass.hpp"

#include <fstream>
#include <iostream>
#include <llvm/Support/raw_ostream.h>

using namespace AST;
using namespace Passes;
using namespace std;

int main() {
    /// This program returns 'argc! + 1', where argc is the number of arguments
    /// and n! is the factorial of n.

    AbstractSyntaxTree ast;

    auto funcDecl = make_shared<FunctionDef>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "factorial", CodeLocation::none);
    auto variable = make_shared<VariableDefStmt>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "var", &funcDecl->getBody(), CodeLocation::none);
    funcDecl->getParameters().push_back(variable);

    auto cmpOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("var", &funcDecl->getBody(),
        CodeLocation::none), "==", &funcDecl->getBody(), CodeLocation::none);
    cmpOp->getArgs().push_back(
        make_shared<ConstIntExpr>("0", 0u, &funcDecl->getBody(),
        CodeLocation::none));
    auto ifBlock = make_shared<IfStmt>(cmpOp, &funcDecl->getBody(),
        CodeLocation::none);
    auto ret = make_shared<ReturnStmt>(make_shared<ConstIntExpr>("1", 1u,
        &ifBlock->getBody(), CodeLocation::none), &ifBlock->getBody(),
        CodeLocation::none);
    ifBlock->getBody().push_back(ret);
    funcDecl->getBody().push_back(ifBlock);

    auto subOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("var", &funcDecl->getBody(),
        CodeLocation::none), "-", &funcDecl->getBody(), CodeLocation::none);
    subOp->getArgs().push_back(
        make_shared<ConstIntExpr>("1", 1u, &funcDecl->getBody(),
        CodeLocation::none));
    auto recurseOp = make_shared<FunctionCallExpr>(
        "factorial", &funcDecl->getBody(), CodeLocation::none);
    recurseOp->getArgs().push_back(subOp);
    auto mulOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("var", &funcDecl->getBody(),
        CodeLocation::none), "*", &funcDecl->getBody(), CodeLocation::none);
    mulOp->getArgs().push_back(recurseOp);
    auto ret2 = make_shared<ReturnStmt>(mulOp, &funcDecl->getBody(),
        CodeLocation::none);
    funcDecl->getBody().push_back(ret2);

    auto mainDecl = make_shared<FunctionDef>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "main", CodeLocation::none);
    mainDecl->setExported(true);
    auto argcDef = make_shared<VariableDefStmt>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "argc", &mainDecl->getBody(), CodeLocation::none);
    mainDecl->getParameters().push_back(argcDef);
    ast.getDeclarations().push_back(mainDecl);
    /// factorial() is forward referenced
    ast.getDeclarations().push_back(funcDecl);

    auto funcCall = make_shared<FunctionCallExpr>("factorial",
        &mainDecl->getBody(), CodeLocation::none);
    funcCall->getArgs().push_back(make_shared<VariableExpr>("argc",
        &mainDecl->getBody(), CodeLocation::none));
    auto defAssignX = make_shared<VariableDefAssignStmt>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "x", funcCall, &mainDecl->getBody(), CodeLocation::none);
    mainDecl->getBody().push_back(defAssignX);

    auto defY = make_shared<VariableDefStmt>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "y", &mainDecl->getBody(), CodeLocation::none);
    mainDecl->getBody().push_back(defY);

    auto assignOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("y", &mainDecl->getBody(),
        CodeLocation::none), "=", &mainDecl->getBody(), CodeLocation::none);
    assignOp->getArgs().push_back(
        make_shared<VariableExpr>("x", &mainDecl->getBody(),
        CodeLocation::none));
    mainDecl->getBody().push_back(assignOp);

    auto unaryAssignOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("y", &mainDecl->getBody(),
        CodeLocation::none), "++", &mainDecl->getBody(), CodeLocation::none);
    mainDecl->getBody().push_back(unaryAssignOp);

    auto ret3 = make_shared<ReturnStmt>(
        make_shared<VariableExpr>("y", &mainDecl->getBody(),
        CodeLocation::none), &mainDecl->getBody(), CodeLocation::none);
    mainDecl->getBody().push_back(ret3);

    PrintPass printer(ast, cout);
    printer.run();

    StdLibPass stdLibPass(ast);
    stdLibPass.run();

    IdentifierPass identifier(ast);
    identifier.run();

    TypePass typePass(ast);
    typePass.run();

    LLVMPass llvmPass(ast);
    llvmPass.run();

    VerifyOptimizePass verOptPass(ast);
    verOptPass.run();

    std::error_code ec;
    llvm::raw_fd_ostream out("ast_test.bc", ec, (llvm::sys::fs::OpenFlags) 0);
    IRExportPass exportPass(ast, out);
    exportPass.run();
    out.close();

    return 0;
}
