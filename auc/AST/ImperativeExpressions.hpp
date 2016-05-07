/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_IMPERATIVEEXPRESSIONS_HPP
#define AUC_IMPERATIVEEXPRESSIONS_HPP

#include "Expression.hpp"

#include <string>

namespace AST {

class ImperativeExpr : Expression {

public:
    virtual std::string toString() = 0;

}; // class ImperativeExpr

} // namespace AST

#endif // AUC_IMPERATIVEEXPRESSIONS_HPP
