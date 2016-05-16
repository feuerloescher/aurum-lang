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

class DeclarativeExpr;
class FunctionDeclExpr;

class ImperativeExpr;
class ReturnExpr;
class VariableDefExpr;
class VariableDefAssignExpr;

class BlockExpr;
class IfExpr;
class WhileLoopExpr;

class TypeExpr;

class ValueExpr;
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

    void runOn(DeclarativeExpr& expr);
    virtual void runOn(FunctionDeclExpr& expr) = 0;

    void runOn(ImperativeExpr& expr);
    virtual void runOn(ReturnExpr& expr) = 0;
    virtual void runOn(VariableDefExpr& expr) = 0;
    virtual void runOn(VariableDefAssignExpr& expr) = 0;

    void runOn(BlockExpr& expr);
    virtual void runOn(IfExpr& expr) = 0;
    virtual void runOn(WhileLoopExpr& expr) = 0;

    virtual void runOn(TypeExpr& expr) = 0;

    void runOn(ValueExpr& expr);
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
