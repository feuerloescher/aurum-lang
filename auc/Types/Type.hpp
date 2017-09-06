/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPE_HPP
#define AUC_TYPE_HPP

#include "AST/common.hpp"
#include "AST/ASTMap.hpp"

#include <string>

namespace AST {

/// \todo Implement reference types for function/method call-by-reference
class Type {

protected:
    std::string name;
    ASTMap<MethodDef*> methodDefs;

public:
    Type(std::string name);

    std::string getName();
    ASTMap<MethodDef*>& getMethodDefs();

}; // class Type


} // namespace AST

#endif // AUC_TYPE_HPP