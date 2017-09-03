/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_SCALARTYPES_HPP
#define AUC_SCALARTYPES_HPP

#include "common.hpp"
#include "Type.hpp"

#include <string>

namespace AST {

class ScalarType : public Type {

public:
    ScalarType(std::string name);

}; // class ScalarType



class IntType : public ScalarType {

protected:
    unsigned int width;
    bool isSigned;

public:
    IntType(std::string name, unsigned int width, bool isSigned);

    bool getSigned();

}; // class IntType


} // namespace AST

#endif // AUC_SCALARTYPES_HPP
