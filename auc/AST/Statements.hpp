/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_IMPERATIVEEXPRESSIONS_HPP
#define AUC_IMPERATIVEEXPRESSIONS_HPP

#include "common.hpp"
#include "Type.hpp"
#include "ASTPass.hpp"

#include <string>

namespace AST {

class Statement {

public:
    virtual void runPass(ASTPass& pass) = 0;

}; // class Statement

typedef ASTList<Statement> StatementList;


class ReturnStmt : public Statement {

protected:
    ASTPtr<Expression> value;

public:
    ReturnStmt(ASTPtr<Expression> value);
    virtual void runPass(ASTPass& pass);

    ASTPtr<Expression> getValue();

}; // class ReturnStmt


class VariableDefStmt : public Statement {

protected:
    std::string name;
    ASTPtr<Type> type;

public:
    VariableDefStmt(std::string name, ASTPtr<Type> type);
    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<Type> getType();

}; // class VariableDefStmt

typedef ASTList<VariableDefStmt> VariableDefStmtList;


class VariableDefAssignStmt : public Statement {

protected:
    std::string name;
    ASTPtr<Type> type;
    ASTPtr<Expression> value;

public:
    VariableDefAssignStmt(std::string name, ASTPtr<Type> type,
        ASTPtr<Expression> value);
    virtual void runPass(ASTPass& pass);

    std::string getName();
    ASTPtr<Type> getType();
    ASTPtr<Expression> getValue();

}; // class VariableDefAssignStmt

} // namespace AST

#endif // AUC_IMPERATIVEEXPRESSIONS_HPP
