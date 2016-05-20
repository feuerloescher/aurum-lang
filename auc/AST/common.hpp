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

/// Reference
template <class T>
using ASTRef = std::reference_wrapper<T>;

/// Managed list
template <class T>
using ASTList = std::vector<ASTPtr<T>>;

} // namespace AST

#endif // AUC_COMMON_HPP
