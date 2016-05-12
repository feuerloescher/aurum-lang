/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_EXPRESSION_HPP
#define AUC_EXPRESSION_HPP

#include "common.hpp"

#include <string>

namespace AST {

class Expression {

public:
    virtual std::string toString() = 0;

}; // class Expression

} // namespace AST

#endif // AUC_EXPRESSION_HPP
