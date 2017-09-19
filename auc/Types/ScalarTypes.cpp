/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ScalarTypes.hpp"

using namespace type;

ScalarType::ScalarType(std::string name, size_t size) : name(name), size(size) {
}

std::string ScalarType::getName() {
    return name;
}

size_t ScalarType::getSize() {
    return size;
}


VoidType::VoidType() : ScalarType("void", 0) {
}


IntType::IntType(std::string name, size_t bitwidth, bool isSigned)
        : ScalarType(name, bitwidth / 8), isSigned(isSigned) {
    if (bitwidth % 8 != 0) {
        throw std::runtime_error("Bitwidth must be a multiple of 8: " + std::to_string(bitwidth));
    }
}

bool IntType::getSigned() {
    return isSigned;
}
