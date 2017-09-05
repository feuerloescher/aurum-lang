/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ASTELEMENT_HPP
#define AUC_ASTELEMENT_HPP

#include "common.hpp"
#include "CodeLocation.hpp"

namespace AST {

class ASTElement {

protected:
    CodeLocation codeLocation;

public:
    explicit ASTElement(CodeLocation codeLocation);
    virtual ~ASTElement() {};

    virtual void runPass(ASTPass& pass) = 0;

    CodeLocation getCodeLocation();

}; // class ASTElement
} // namespace AST

#endif // AUC_ASTELEMENT_HPP
