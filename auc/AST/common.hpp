/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_COMMON_HPP
#define AUC_COMMON_HPP

#include <functional>
#include <memory>
#include <vector>

namespace AST {

/// Managed pointer
template<class T>
using ASTPtr = std::shared_ptr<T>;

/// Managed list
template<class T>
using ASTList = std::vector<ASTPtr<T>>;

/// Forward declarations:
class AbstractSyntaxTree;

class ASTElement;
typedef ASTPtr<ASTElement> ASTElementPtr;

class ASTPass;


class Declaration;
typedef ASTPtr<Declaration> DeclarationPtr;
typedef ASTList<Declaration> DeclarationList;

class FunctionDecl;
typedef ASTPtr<FunctionDecl> FunctionDeclPtr;

class FunctionDef;
typedef ASTPtr<FunctionDef> FunctionDefPtr;


class Statement;
typedef ASTList<Statement> StatementList;
typedef ASTPtr<Statement> StatementPtr;

class ReturnStmt;
typedef ASTPtr<ReturnStmt> ReturnStmtPtr;

class VariableDefStmt;
typedef ASTList<VariableDefStmt> VariableDefStmtList;
typedef ASTPtr<VariableDefStmt> VariableDefStmtPtr;

class VariableDefAssignStmt;
typedef ASTPtr<VariableDefAssignStmt> VariableDefAssignStmtPtr;


class TypeStmt;
typedef ASTPtr<TypeStmt> TypeStmtPtr;
class BasicTypeStmt;
typedef ASTPtr<BasicTypeStmt> BasicTypeStmtPtr;


class Block;
typedef ASTPtr<Block> BlockPtr;

class IfStmt;
typedef ASTPtr<IfStmt> IfStmtPtr;

class WhileLoop;
typedef ASTPtr<WhileLoop> WhileLoopPtr;


class Expression;
typedef ASTList<Expression> ExpressionList;
typedef ASTPtr<Expression> ExpressionPtr;

class FunctionCallExpr;
typedef ASTPtr<FunctionCallExpr> FunctionCallExprPtr;

class ConstIntExpr;
typedef ASTPtr<ConstIntExpr> ConstIntExprPtr;

class VariableExpr;
typedef ASTPtr<VariableExpr> VariableExprPtr;

} // namespace AST

#endif // AUC_COMMON_HPP
