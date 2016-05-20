/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_DECLARATIVEEXPRESSIONS_HPP
#define AUC_DECLARATIVEEXPRESSIONS_HPP

#include "common.hpp"
#include "Statements.hpp"
#include "ASTPass.hpp"

#include <string>

namespace AST {

class Declaration {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class Declaration

typedef ASTList<Declaration> DeclarationList;


class FunctionDecl : public Declaration {

protected:
    std::string name;
    ASTPtr<Type> type;
    ASTList<VariableDefStmt> parameters;
    StatementList body;

public:
    FunctionDecl(std::string name, ASTPtr<Type> type);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<Type> getType();
    VariableDefStmtList& getParameters();
    StatementList& getBody();

}; // class FunctionDecl

} // namespace AST

#endif // AUC_DECLARATIVEEXPRESSIONS_HPP
