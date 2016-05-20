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
class FunctionDecl;

class Statement;
class ReturnStmt;
class VariableDefStmt;
class VariableDefAssignStmt;

class Block;
class IfStmt;
class WhileLoop;

class Type;

class Expression;
class FunctionCallExpr;
class ConstIntExpr;
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

    void runOn(Declaration& expr);
    virtual void runOn(FunctionDecl& expr);

    void runOn(Statement& expr);
    virtual void runOn(ReturnStmt& expr);
    virtual void runOn(VariableDefStmt& expr);
    virtual void runOn(VariableDefAssignStmt& expr);

    void runOn(Block& expr);
    virtual void runOn(IfStmt& expr);
    virtual void runOn(WhileLoop& expr);

    virtual void runOn(Type& expr);

    void runOn(Expression& expr);
    virtual void runOn(FunctionCallExpr& expr);
    virtual void runOn(ConstIntExpr& expr);
    virtual void runOn(VariableExpr& expr);
    virtual void runOn(UnaryOpExpr& expr);
    virtual void runOn(BinaryOpExpr& expr);
    virtual void runOn(UnaryAssignOpExpr& expr);
    virtual void runOn(BinaryAssignOpExpr& expr);

}; // class ASTPass

} // namespace AST

#endif // AUC_ASTPASS_HPP
