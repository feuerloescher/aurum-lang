/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Type.hpp"

#include <sstream>

using namespace AST;

Type::Type(std::string name) : name(name) {
}

void Type::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string Type::getName() {
    return name;
}
