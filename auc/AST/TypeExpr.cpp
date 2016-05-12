/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "TypeExpr.hpp"

#include <sstream>

using namespace AST;

std::string TypeExpr::toString() {
    std::ostringstream str;
    str << "TypeExpr(Name: " << name << ")";
    return str.str();
}
