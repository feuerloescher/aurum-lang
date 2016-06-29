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
using InternalMapType = std::map<std::string, T>;

template <class T>
class ASTMap {

protected:
    InternalMapType<T> internalMap;

public:
    void clear();
    bool insert(T t);
    bool insert(T t, std::string name);
    T find(std::string name);
    typename InternalMapType<T>::iterator begin();
    typename InternalMapType<T>::iterator end();

}; // class ASTMap

} // namespace AST

#endif // AUC_ASTMAP_HPP
