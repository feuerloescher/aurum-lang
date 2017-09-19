/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_SCALARTYPES_HPP
#define AUC_SCALARTYPES_HPP

#include "AST/common.hpp"
#include "Type.hpp"

#include <string>

namespace type {

class ScalarType : public Type {

protected:
    std::string name;
    size_t size; // in bytes

public:
    ScalarType(std::string name, size_t size);

    std::string getName() override;
    size_t getSize() override;

}; // class ScalarType


class VoidType : public ScalarType {

public:
    VoidType();

    virtual ~VoidType() {}

}; // class VoidType


class IntType : public ScalarType {

protected:
    bool isSigned;

public:
    IntType(std::string name, size_t bitwidth, bool isSigned);

    bool getSigned();

}; // class IntType


} // namespace AST

#endif // AUC_SCALARTYPES_HPP
