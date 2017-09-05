/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPESTMT_HPP
#define AUC_TYPESTMT_HPP

#include "common.hpp"
#include "ASTElement.hpp"
#include "Type.hpp"

#include <string>

namespace AST {

class TypeStmt : public ASTElement {

protected:
    std::string name;
    TypePtr type;

public:
    TypeStmt(std::string name, CodeLocation codeLocation);
    virtual ~TypeStmt() {};

    void runPass(ASTPass& pass);

    std::string getName();
    TypePtr getType();
    void setType(TypePtr type);

}; // class TypeStmt


} // namespace AST

#endif // AUC_TYPESTMT_HPP
