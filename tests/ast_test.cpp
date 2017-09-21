/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/Expressions.hpp"
#include "Passes/OutputPass.hpp"
#include "Passes/StdLibPass.hpp"
#include "Passes/IdentifierPass.hpp"
#include "Passes/TypePass.hpp"

#include <iostream>

using namespace AST;
using namespace Passes;
using namespace std;

int main() {
    /// This program returns 'argc! + 1', where argc is the number of arguments
    /// and n! is the factorial of n.

    AbstractSyntaxTree ast;

    auto funcDecl = make_shared<FunctionDecl>(
            make_shared<BasicTypeStmt>("uint32", CodeLocation::none), "factorial", true, CodeLocation::none);
    auto funcDef = make_shared<FunctionDef>(funcDecl, make_shared<Block>(CodeLocation::none), CodeLocation::none);
    auto variable = make_shared<VariableDefStmt>(
            make_shared<BasicTypeStmt>("uint32", CodeLocation::none), "var", CodeLocation::none);
    funcDecl->getParameters().push_back(variable);

    auto cmpOp = make_shared<FunctionCallExpr>("==", CodeLocation::none);
    cmpOp->getArgs().push_back(make_shared<VariableExpr>("var", CodeLocation::none));
    cmpOp->getArgs().push_back(make_shared<ConstIntExpr>("0", 0u, CodeLocation::none));
    auto ifBlock = make_shared<IfStmt>(cmpOp, make_shared<Block>(CodeLocation::none), CodeLocation::none);
    auto ret = make_shared<ReturnStmt>(make_shared<ConstIntExpr>("1", 1u, CodeLocation::none), CodeLocation::none);
    ifBlock->getBody()->push_back(ret);
    funcDef->getBody()->push_back(ifBlock);

    auto subOp = make_shared<FunctionCallExpr>("-", CodeLocation::none);
    subOp->getArgs().push_back(make_shared<VariableExpr>("var", CodeLocation::none));
    subOp->getArgs().push_back(make_shared<ConstIntExpr>("1", 1u, CodeLocation::none));
    auto recurseOp = make_shared<FunctionCallExpr>("factorial", CodeLocation::none);
    recurseOp->getArgs().push_back(subOp);
    auto mulOp = make_shared<FunctionCallExpr>("*", CodeLocation::none);
    mulOp->getArgs().push_back(make_shared<VariableExpr>("var", CodeLocation::none));
    mulOp->getArgs().push_back(recurseOp);
    auto ret2 = make_shared<ReturnStmt>(mulOp, CodeLocation::none);
    funcDef->getBody()->push_back(ret2);

    auto mainDecl = make_shared<FunctionDef>(
            make_shared<FunctionDecl>(make_shared<BasicTypeStmt>("uint32", CodeLocation::none), "main", true,
                    CodeLocation::none), make_shared<Block>(CodeLocation::none), CodeLocation::none);
    mainDecl->setExported(true);
    auto argcDef = make_shared<VariableDefStmt>(
            make_shared<BasicTypeStmt>("uint32", CodeLocation::none), "argc", CodeLocation::none);
    mainDecl->getFunctionDecl()->getParameters().push_back(argcDef);
    ast.getASTElements().push_back(mainDecl);
    /// factorial() is forward referenced
    ast.getASTElements().push_back(funcDef);

    auto funcCall = make_shared<FunctionCallExpr>("factorial", CodeLocation::none);
    funcCall->getArgs().push_back(make_shared<VariableExpr>("argc", CodeLocation::none));
    auto defAssignX = make_shared<VariableDefAssignStmt>(
            make_shared<BasicTypeStmt>("uint32", CodeLocation::none), "x", funcCall, CodeLocation::none);
    mainDecl->getBody()->push_back(defAssignX);

    auto defY = make_shared<VariableDefStmt>(
            make_shared<BasicTypeStmt>("uint32", CodeLocation::none), "y", CodeLocation::none);
    mainDecl->getBody()->push_back(defY);

    auto assignOp = make_shared<FunctionCallExpr>("=", CodeLocation::none);
    assignOp->getArgs().push_back(make_shared<VariableExpr>("y", CodeLocation::none));
    assignOp->getArgs().push_back(make_shared<VariableExpr>("x", CodeLocation::none));
    mainDecl->getBody()->push_back(assignOp);

    auto unaryAssignOp = make_shared<FunctionCallExpr>("++", CodeLocation::none);
    unaryAssignOp->getArgs().push_back(make_shared<VariableExpr>("y", CodeLocation::none));
    mainDecl->getBody()->push_back(unaryAssignOp);

    auto ret3 = make_shared<ReturnStmt>(make_shared<VariableExpr>("y", CodeLocation::none), CodeLocation::none);
    mainDecl->getBody()->push_back(ret3);

    StdLibPass stdLibPass(ast);
    stdLibPass.run();

    IdentifierPass identifier(ast);
    identifier.run();

    TypePass typePass(ast);
    typePass.run();

    OutputPass printer(ast, cout);
    printer.run();

    return 0;
}
