/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Statements.hpp"
#include "Expressions.hpp"

using namespace AST;

Type::Type(std::string name) : name(name) {
}

std::string Type::getName() {
    return name;
}

llvm::Type* Type::getLLVMType() {
    return llvmType;
}
