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

public:
    virtual void runOn(AbstractSyntaxTree& ast) = 0;

    void runOn(Declaration& expr);
    virtual void runOn(FunctionDecl& expr) = 0;

    void runOn(Statement& expr);
    virtual void runOn(ReturnStmt& expr) = 0;
    virtual void runOn(VariableDefStmt& expr) = 0;
    virtual void runOn(VariableDefAssignStmt& expr) = 0;

    void runOn(Block& expr);
    virtual void runOn(IfStmt& expr) = 0;
    virtual void runOn(WhileLoop& expr) = 0;

    virtual void runOn(Type& expr) = 0;

    void runOn(Expression& expr);
    virtual void runOn(FunctionCallExpr& expr) = 0;
    virtual void runOn(ConstIntExpr& expr) = 0;
    virtual void runOn(VariableExpr& expr) = 0;
    virtual void runOn(UnaryOpExpr& expr) = 0;
    virtual void runOn(BinaryOpExpr& expr) = 0;
    virtual void runOn(UnaryAssignOpExpr& expr) = 0;
    virtual void runOn(BinaryAssignOpExpr& expr) = 0;

}; // class ASTPass

} // namespace AST

#endif // AUC_ASTPASS_HPP
