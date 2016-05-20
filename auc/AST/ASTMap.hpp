/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ASTMAP_HPP
#define AUC_ASTMAP_HPP

#include "common.hpp"

#include <functional>
#include <map>
#include <string>

namespace AST {

template <class T>
class ASTMap {

protected:
    std::map<std::string, ASTRef<T>> internalMap;

public:
    void clear();
    bool insert(T& t);
    T* find(std::string name);

}; // class Type

} // namespace AST

#endif // AUC_ASTMAP_HPP
