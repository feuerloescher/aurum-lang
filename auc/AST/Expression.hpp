/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_EXPRESSION_HPP
#define AUC_EXPRESSION_HPP

#include "common.hpp"

namespace AST {

class ASTPass;

class Expression {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class Expression

} // namespace AST

#endif // AUC_EXPRESSION_HPP
