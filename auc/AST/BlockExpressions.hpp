/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_BLOCKEXPRESSIONS_HPP
#define AUC_BLOCKEXPRESSIONS_HPP

#include "ImperativeExpressions.hpp"

#include <string>

namespace AST {

class BlockExpr : ImperativeExpr {

public:
    virtual std::string toString() = 0;

}; // class BlockExpr

} // namespace AST

#endif // AUC_BLOCKEXPRESSIONS_HPP
