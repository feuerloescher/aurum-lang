/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AbstractSyntaxTree.hpp"
#include "TypeExpr.hpp"
#include "Expression.hpp"
#include "BlockExpressions.hpp"
#include "DeclarativeExpressions.hpp"
#include "ImperativeExpressions.hpp"
#include "ValueExpressions.hpp"

#include <sstream>

using namespace AST;

std::string AbstractSyntaxTree::toString() {
    std::ostringstream str;
    str << "AbstractSyntaxTree: " << DeclListToString(expressions);
    return str.str();
}
