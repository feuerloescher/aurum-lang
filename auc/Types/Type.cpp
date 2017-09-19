/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Type.hpp"

using namespace type;

AST::ASTMap<AST::FunctionDecl*>& Type::getFunctionDecls() {
    return functionDecls;
}
