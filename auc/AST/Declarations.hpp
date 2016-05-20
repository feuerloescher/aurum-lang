/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_DECLARATIONS_HPP
#define AUC_DECLARATIONS_HPP

#include "common.hpp"
#include "Blocks.hpp"
#include "ASTPass.hpp"

#include <string>

namespace AST {

class Declaration {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class Declaration

typedef ASTList<Declaration> DeclarationList;


class FunctionDef : public Declaration {

protected:
    std::string name;
    ASTPtr<Type> type;
    ASTList<VariableDefStmt> parameters;
    Block body;

public:
    FunctionDef(std::string name, ASTPtr<Type> type);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<Type> getType();
    VariableDefStmtList& getParameters();
    Block& getBody();

}; // class FunctionDef

} // namespace AST

#endif // AUC_DECLARATIONS_HPP
