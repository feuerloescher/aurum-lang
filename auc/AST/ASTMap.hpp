/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ASTMAP_HPP
#define AUC_ASTMAP_HPP

#include "common.hpp"
#include "CodeLocation.hpp"

#include <functional>
#include <map>
#include <string>

namespace AST {

#warning Use unordered_map instead of map?
template<class T>
using InternalMapType = std::map<std::string, T>;

template<class T>
class ASTMap {

protected:
    InternalMapType<T> internalMap;

public:
    void clear();
    void insert(T t, CodeLocation codeLocation);
    void insert(T t, std::string name, CodeLocation codeLocation);
    T find(std::string name);
    typename InternalMapType<T>::iterator begin();
    typename InternalMapType<T>::iterator end();

}; // class ASTMap

} // namespace AST

#endif // AUC_ASTMAP_HPP
