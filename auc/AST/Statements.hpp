/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_STATEMENTS_HPP
#define AUC_STATEMENTS_HPP

#include "common.hpp"
#include "ASTElement.hpp"
#include "TypeStmt.hpp"

#include <string>

namespace AST {

class Statement : public ASTElement {

protected:

public:
    Statement(CodeLocation codeLocation);

}; // class Statement



class ReturnStmt : public Statement {

protected:
    ExpressionPtr value;

public:
    ReturnStmt(ExpressionPtr value, CodeLocation codeLocation);
    virtual void runPass(ASTPass& pass);

    ExpressionPtr getValue();

}; // class ReturnStmt



class VariableDefStmt : public Statement {

protected:
    TypeStmtPtr typeStmt;
    std::string name;

public:
    VariableDefStmt(TypeStmtPtr typeStmt, std::string name, CodeLocation codeLocation);
    virtual void runPass(ASTPass& pass);

    std::string getName();
    TypeStmtPtr getTypeStmt();

}; // class VariableDefStmt



class VariableDefAssignStmt : public VariableDefStmt {

protected:
    ExpressionPtr value;

public:
    VariableDefAssignStmt(TypeStmtPtr type, std::string name,
            ExpressionPtr value, CodeLocation codeLocation);
    virtual void runPass(ASTPass& pass);

    ExpressionPtr getValue();

}; // class VariableDefAssignStmt


} // namespace AST

#endif // AUC_STATEMENTS_HPP
