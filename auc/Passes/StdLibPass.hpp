/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_STDLIBPASS_HPP
#define AUC_STDLIBPASS_HPP

#include "AST/common.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/ASTMap.hpp"

namespace Passes {

/// Register builtin types and functions of the language
class StdLibPass {

protected:
    AST::AbstractSyntaxTree& ast;
    AST::ASTMap<AST::TypePtr>& types;

    void addScalarTypes();

public:
    StdLibPass(AST::AbstractSyntaxTree& ast);
    virtual ~StdLibPass() {};

    void run();

}; // class StdLibPass

} // namespace Passes

#endif // AUC_STDLIBPASS_HPP
