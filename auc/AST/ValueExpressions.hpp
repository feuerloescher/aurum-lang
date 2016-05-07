/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_VALUEEXPRESSIONS_HPP
#define AUC_VALUEEXPRESSIONS_HPP

#include "ImperativeExpressions.hpp"

#include <string>

namespace AST {

class ValueExpr : ImperativeExpr {

public:
    virtual std::string toString() = 0;

}; // class ValueExpr

} // namespace AST

#endif // AUC_VALUEEXPRESSIONS_HPP
