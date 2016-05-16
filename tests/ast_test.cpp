/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AST/AbstractSyntaxTree.hpp"
#include "AST/ValueExpressions.hpp"

#include <iostream>

using namespace AST;

int main() {
    AbstractSyntaxTree ast;
    std::cout << ast.toString() << std::endl;
    VariableExpr varExpr("var");
    return 0;
}
