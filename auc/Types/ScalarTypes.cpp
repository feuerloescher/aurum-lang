/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ScalarTypes.hpp"

using namespace AST;

ScalarType::ScalarType(std::string name)
        : Type(name) {
}

IntType::IntType(std::string name, unsigned int width, bool isSigned)
        : ScalarType(name), width(width), isSigned(isSigned) {
}

bool IntType::getSigned() {
    return isSigned;
}