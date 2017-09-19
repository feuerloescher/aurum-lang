/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPESTMT_HPP
#define AUC_TYPESTMT_HPP

#include "common.hpp"
#include "ASTElement.hpp"
#include "Types/Type.hpp"

#include <string>

namespace AST {

class TypeStmt : public ASTElement {

protected:
    type::TypePtr type;
    bool isReference;

    TypeStmt(CodeLocation codeLocation);

public:
    virtual ~TypeStmt() {};

    type::TypePtr getType();
    void setType(type::TypePtr type);
    bool getIsReference();
    void setIsReference(bool isReference);

}; // class TypeStmt


class BasicTypeStmt : public TypeStmt {

protected:
    std::string name;

public:
    BasicTypeStmt(std::string name, CodeLocation codeLocation);
    virtual ~BasicTypeStmt() {};

    void runPass(ASTPass& pass);

    std::string getName();

}; // class BasicTypeStmt


} // namespace AST

#endif // AUC_TYPESTMT_HPP
