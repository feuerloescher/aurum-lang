/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ASTPASS_HPP
#define AUC_ASTPASS_HPP

#include "AST/common.hpp"
#include "AST/Errors.hpp"

namespace AST {

class ASTPass {

protected:
    AbstractSyntaxTree& ast;

    void handleError(ASTElement& elem, const ASTError& err);

public:
    ASTPass(AbstractSyntaxTree& ast);
    virtual ~ASTPass() {};

    virtual void run() = 0;

    /// \todo Reorganize; multiple dispatch only for virtual base classes

    template<class T>
    void tryRunOn(T& t) {
        try {
            this->runOn(t);
        } catch (const ASTError& err) {
            handleError(t, err);
        }
    }

    virtual void runOn(FunctionDecl&);
    virtual void runOn(FunctionDef&);

    virtual void runOn(Statement&);
    virtual void runOn(ReturnStmt&);
    virtual void runOn(VariableDefStmt&);
    virtual void runOn(VariableDefAssignStmt&);

    virtual void runOn(Block&);
    virtual void runOn(IfStmt&);
    virtual void runOn(WhileLoop&);

    virtual void runOn(TypeStmt&);
    virtual void runOn(BasicTypeStmt&);

    virtual void runOn(Expression&);
    virtual void runOn(FunctionCallExpr&);
    virtual void runOn(ConstIntExpr&);
    virtual void runOn(VariableExpr&);

}; // class ASTPass

} // namespace AST

#endif // AUC_ASTPASS_HPP
