/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPEEXPR_HPP
#define AUC_TYPEEXPR_HPP

#include "common.hpp"
#include "Expression.hpp"
#include "ASTPass.hpp"

#include <string>

namespace AST {

class TypeExpr : public Expression {

protected:
    std::string name;

public:
    TypeExpr(std::string name);

    virtual void runPass(ASTPass& pass);

    std::string getName();

}; // class TypeExpr

} // namespace AST

#endif // AUC_TYPEEXPR_HPP
