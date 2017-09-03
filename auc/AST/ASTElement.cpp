/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ASTElement.hpp"

using namespace AST;

ASTElement::ASTElement(CodeLocation codeLocation)
        : codeLocation(codeLocation) {
}

CodeLocation ASTElement::getCodeLocation() {
    return codeLocation;
}
