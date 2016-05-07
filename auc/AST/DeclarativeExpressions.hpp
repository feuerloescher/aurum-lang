/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_DECLARATIVEEXPRESSIONS_HPP
#define AUC_DECLARATIVEEXPRESSIONS_HPP

#include "Expression.hpp"

#include <string>

namespace AST {

class DeclarativeExpr : Expression {

public:
    virtual std::string toString() = 0;

}; // class DeclarativeExpr

} // namespace AST

#endif // AUC_DECLARATIVEEXPRESSIONS_HPP
