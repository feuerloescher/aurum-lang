/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ASTMap.hpp"
#include "Declarations.hpp"

using namespace AST;

template <class T>
void ASTMap<T>::clear() {
    internalMap.clear();
}

template <class T>
bool ASTMap<T>::insert(T& t) {
    return internalMap.insert(std::make_pair(t.getName(),
        std::reference_wrapper<T>(t))).second;
}

template class AST::ASTMap<FunctionDecl>;
