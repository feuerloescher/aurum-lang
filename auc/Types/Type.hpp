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

namespace type {

class Type {

protected:
    AST::ASTMap<AST::FunctionDecl*> functionDecls;

public:
    virtual ~Type() {}

    virtual std::string getName() = 0;
    virtual size_t getSize() = 0;
    AST::ASTMap<AST::FunctionDecl*>& getFunctionDecls();

}; // class Type
typedef std::shared_ptr<Type> TypePtr;


} // namespace AST

#endif // AUC_TYPE_HPP
