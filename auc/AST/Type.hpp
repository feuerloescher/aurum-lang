/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPEEXPR_HPP
#define AUC_TYPEEXPR_HPP

#include "common.hpp"
#include "ASTPass.hpp"

#include <string>

namespace AST {

class Type {

protected:
    std::string name;

public:
    Type(std::string name);

    void runPass(ASTPass& pass);

    std::string getName();

}; // class Type

} // namespace AST

#endif // AUC_TYPEEXPR_HPP
