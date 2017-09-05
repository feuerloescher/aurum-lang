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

class Declaration : public ASTElement {
protected:
    bool exported;

public:
    Declaration(bool exported, CodeLocation codeLocation);
    virtual ~Declaration() {}

    bool getExported();
    void setExported(bool exported);

};

class FunctionDecl : public Declaration {

protected:
    std::string name;
    TypeStmtPtr returnTypeStmt;
    ASTList<VariableDefStmt> parameters;

public:
    FunctionDecl(TypeStmtPtr returnTypeStmt, std::string name, bool exported, CodeLocation codeLocation);
    virtual ~FunctionDecl() {};

    virtual void runPass(ASTPass& pass);

    std::string getName();
    TypeStmtPtr getReturnTypeStmt();
    VariableDefStmtList& getParameters();

}; // class Declaration


class FunctionDef : public Declaration {

protected:
    FunctionDeclPtr funcDecl;
    BlockPtr body;

public:
    FunctionDef(FunctionDeclPtr funcDecl, BlockPtr body, CodeLocation codeLocation);
    virtual ~FunctionDef() {}

    virtual void runPass(ASTPass& pass);

    std::string getName();
    FunctionDeclPtr getFunctionDecl();
    BlockPtr getBody();

}; // class FunctionDef


class MethodDef : public Declaration {
#warning TODO: Replace MethodDef with FunctionDef
protected:
    std::string name;
    TypeStmtPtr returnTypeStmt;
    TypeStmtPtr objectTypeStmt;
    ASTList<VariableDefStmt> parameters;
    BlockPtr body;

public:
    MethodDef(TypeStmtPtr returnTypeStmt, std::string name,
            TypeStmtPtr objectTypeStmt, bool exported, CodeLocation codeLocation);
    virtual ~MethodDef() {}

    virtual void runPass(ASTPass& pass);

    std::string getName();
    TypeStmtPtr getReturnTypeStmt();
    TypeStmtPtr getObjectTypeStmt();
    VariableDefStmtList& getParameters();
    BlockPtr getBody();

}; // class MethodDef


} // namespace AST

#endif // AUC_DECLARATIONS_HPP
