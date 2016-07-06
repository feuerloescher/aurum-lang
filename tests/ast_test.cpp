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
    AbstractSyntaxTree ast;

    auto variable = make_shared<VariableDefStmt>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "var", CodeLocation::none);
    auto funcDecl = make_shared<FunctionDef>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "foo", CodeLocation::none);
    funcDecl->getParameters().push_back(variable);
    ast.getDeclarations().push_back(funcDecl);

    auto addOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("var", CodeLocation::none),
        "+", CodeLocation::none);
    addOp->getArgs().push_back(
        make_shared<ConstIntExpr>("5", 5u, CodeLocation::none));
    auto ret = make_shared<ReturnStmt>(addOp, CodeLocation::none);
    funcDecl->getBody().push_back(ret);

    auto mainDecl = make_shared<FunctionDef>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "main", CodeLocation::none);
    mainDecl->setExported(true);
    ast.getDeclarations().push_back(mainDecl);

    auto funcCall = make_shared<FunctionCallExpr>("foo", CodeLocation::none);
    funcCall->getArgs().push_back(
        make_shared<ConstIntExpr>("5", 5u, CodeLocation::none));
    auto defAssignX = make_shared<VariableDefAssignStmt>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "x", funcCall, CodeLocation::none);
    mainDecl->getBody().push_back(defAssignX);

    auto defY = make_shared<VariableDefStmt>(
        make_shared<TypeStmt>("uint32", CodeLocation::none),
        "y", CodeLocation::none);
    mainDecl->getBody().push_back(defY);

    auto assignOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("y", CodeLocation::none),
        "=", CodeLocation::none);
    assignOp->getArgs().push_back(
        make_shared<VariableExpr>("x", CodeLocation::none));
    mainDecl->getBody().push_back(assignOp);

    auto unaryAssignOp = make_shared<MethodCallExpr>(
        make_shared<VariableExpr>("y", CodeLocation::none),
        "++", CodeLocation::none);
    mainDecl->getBody().push_back(unaryAssignOp);

    auto ret2 = make_shared<ReturnStmt>(
        make_shared<VariableExpr>("y", CodeLocation::none), CodeLocation::none);
    mainDecl->getBody().push_back(ret2);

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
