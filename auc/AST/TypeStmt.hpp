/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPESTMT_HPP
#define AUC_TYPESTMT_HPP

#include "common.hpp"
#include "ASTPass.hpp"
#include "Type.hpp"

#include <string>

namespace AST {

class TypeStmt {

protected:
    std::string name;
    Type* type;

public:
    TypeStmt(std::string name);

    void runPass(ASTPass& pass);

    std::string getName();
    Type* getType();
    void setType(Type* type);

}; // class TypeStmt

} // namespace AST

#endif // AUC_TYPESTMT_HPP