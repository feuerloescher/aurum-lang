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
template <class T>
using ASTPtr = std::shared_ptr<T>;

/// Managed list
template <class T>
using ASTList = std::vector<ASTPtr<T>>;

/// Forward declarations:
class AbstractSyntaxTree;

class Declaration;
class FunctionDef;
class MethodDef;

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
class MethodCallExpr;
class ConstIntExpr;
class VariableExpr;

class Type;
class ASTPass;

} // namespace AST

#endif // AUC_COMMON_HPP
