/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ASTPASS_HPP
#define AUC_ASTPASS_HPP

#include "common.hpp"

namespace AST {

class AbstractSyntaxTree;

class Declaration;
class FunctionDef;

class Statement;
class ReturnStmt;
class VariableDefStmt;
class VariableDefAssignStmt;

class Block;
class IfStmt;
class WhileLoop;

class TypeStmt;

class Expression;
class FunctionCallExpr;
class ConstUInt32Expr;
class VariableExpr;
class UnaryOpExpr;
class BinaryOpExpr;
class UnaryAssignOpExpr;
class BinaryAssignOpExpr;

class ASTPass {

protected:
    AbstractSyntaxTree& ast;

public:
    ASTPass(AbstractSyntaxTree& ast);

    virtual void run() = 0;

    /// \todo Reorganize; multiple dispatch only for virtual base classes

    virtual void runOn(Declaration&);
    virtual void runOn(FunctionDef&);

    virtual void runOn(Statement&);
    virtual void runOn(ReturnStmt&);
    virtual void runOn(VariableDefStmt&);
    virtual void runOn(VariableDefAssignStmt&);

    virtual void runOn(Block&);
    virtual void runOn(IfStmt&);
    virtual void runOn(WhileLoop&);

    virtual void runOn(TypeStmt&);

    virtual void runOn(Expression&);
    virtual void runOn(FunctionCallExpr&);
    virtual void runOn(ConstUInt32Expr&);
    virtual void runOn(VariableExpr&);
    virtual void runOn(UnaryOpExpr&);
    virtual void runOn(BinaryOpExpr&);
    virtual void runOn(UnaryAssignOpExpr&);
    virtual void runOn(BinaryAssignOpExpr&);

}; // class ASTPass

} // namespace AST

#endif // AUC_ASTPASS_HPP
