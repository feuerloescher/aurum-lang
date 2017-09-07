/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Type.hpp"

using namespace AST;

Type::Type(std::string name) : name(name) {
}

std::string Type::getName() {
    return name;
}

ASTMap<FunctionDecl*>& Type::getFunctionDecls() {
    return functionDecls;
}

TypePtr Type::voidType = std::make_shared<Type>("void");
