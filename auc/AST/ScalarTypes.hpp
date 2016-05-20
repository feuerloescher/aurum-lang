/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_SCALARTYPES_HPP
#define AUC_SCALARTYPES_HPP

#include "common.hpp"
#include "Type.hpp"

namespace AST {

class ScalarType : public Type {

}; // class ScalarType


class IntType : public ScalarType {

public:
    virtual std::string getName();

}; // class IntType

} // namespace AST

#endif // AUC_SCALARTYPES_HPP
