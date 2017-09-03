/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_DECLARATIONS_HPP
#define AUC_DECLARATIONS_HPP

#include "common.hpp"
#include "ASTElement.hpp"

#include <string>
#include <vector>

namespace AST {

class FunctionDecl : public ASTElement {

protected:
    std::string name;
    TypeStmtPtr returnTypeStmt;
    ASTList<VariableDefStmt> parameters;
    bool exported;

public:
    FunctionDecl(TypeStmtPtr returnTypeStmt, std::string name, CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    TypeStmtPtr getReturnTypeStmt();
    VariableDefStmtList& getParameters();
    bool getExported();
    void setExported(bool exported);

}; // class Declaration


class FunctionDef : public ASTElement {

protected:
    BlockPtr body;
    FunctionDeclPtr funcDecl;

public:
    FunctionDef(FunctionDeclPtr funcDecl, BlockPtr body, CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    FunctionDeclPtr getFunctionDecl();
    BlockPtr getBody();

}; // class FunctionDef


class MethodDef : public ASTElement {
#warning TODO: Replace MethodDef with FunctionDef
protected:
    std::string name;
    TypeStmtPtr returnTypeStmt;
    TypeStmtPtr objectTypeStmt;
    ASTList<VariableDefStmt> parameters;
    BlockPtr body;
    bool exported;

public:
    MethodDef(TypeStmtPtr returnTypeStmt, std::string name,
            TypeStmtPtr objectTypeStmt, CodeLocation codeLocation);

    virtual void runPass(ASTPass& pass);

    std::string getName();
    TypeStmtPtr getReturnTypeStmt();
    TypeStmtPtr getObjectTypeStmt();
    VariableDefStmtList& getParameters();
    BlockPtr getBody();

}; // class MethodDef


} // namespace AST

#endif // AUC_DECLARATIONS_HPP
