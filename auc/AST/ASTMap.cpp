/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ASTMap.hpp"
#include "Declarations.hpp"
#include "Statements.hpp"
#include "Type.hpp"

using namespace AST;

template<class T>
void ASTMap<T>::clear() {
    internalMap.clear();
}

template<class T>
bool ASTMap<T>::insert(T t) {
    return internalMap.insert(std::make_pair(t->getName(), t)).second;
}

template<class T>
bool ASTMap<T>::insert(T t, std::string name) {
    return internalMap.insert(std::make_pair(name, t)).second;
}

template<class T>
T ASTMap<T>::find(std::string name) {
    auto element = internalMap.find(name);
    if (element != internalMap.end()) {
        return element->second;
    }
    return nullptr;
}

template<class T>
typename InternalMapType<T>::iterator ASTMap<T>::begin() {
    return internalMap.begin();
}

template<class T>
typename InternalMapType<T>::iterator ASTMap<T>::end() {
    return internalMap.end();
}

template
class AST::ASTMap<FunctionDefPtr>;
template
class AST::ASTMap<MethodDefPtr>;
template
class AST::ASTMap<VariableDefStmtPtr>;
template
class AST::ASTMap<TypePtr>;
