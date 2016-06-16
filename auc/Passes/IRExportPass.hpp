/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_IREXPORTPASS_HPP
#define AUC_IREXPORTPASS_HPP

#include "AST/common.hpp"
#include "AST/AbstractSyntaxTree.hpp"

namespace Passes {

/// Export the generated LLVM Intermediate Representation code
class IRExportPass {

protected:
    AST::AbstractSyntaxTree& ast;

public:
    IRExportPass(AST::AbstractSyntaxTree& ast);

    void run();

}; // class IRExportPass

} // namespace Passes

#endif // AUC_IREXPORTPASS_HPP
