/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_STDLIBPASS_HPP
#define AUC_STDLIBPASS_HPP

#include "AST/common.hpp"
#include "AST/AbstractSyntaxTree.hpp"

namespace Passes {

/// Resolve and check types of expressions
class StdLibPass {

protected:
    AST::AbstractSyntaxTree& ast;

public:
    StdLibPass(AST::AbstractSyntaxTree& ast);

    void run();
    void addStdLibTypes();

}; // class StdLibPass

} // namespace Passes

#endif // AUC_STDLIBPASS_HPP
