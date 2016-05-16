/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ImperativeExpressions.hpp"
#include "ValueExpressions.hpp"

#include <sstream>

using namespace AST;

void ReturnExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void VariableDefExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void VariableDefAssignExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}
