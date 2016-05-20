/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_COMMON_HPP
#define AUC_COMMON_HPP

#include <memory>
#include <vector>

namespace AST {

template <class T>
using ASTPtr = std::shared_ptr<T>;

template <class T>
using ASTList = std::vector<ASTPtr<T>>;

} // namespace AST

#endif // AUC_COMMON_HPP
