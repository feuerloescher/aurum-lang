/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ASTMap.hpp"
#include "Declarations.hpp"
#include "Statements.hpp"
#include "Types/Type.hpp"
#include "Errors.hpp"

using namespace AST;
using namespace type;

template<class T>
void ASTMap<T>::clear() {
    internalMap.clear();
}

template<class T>
void ASTMap<T>::insert(T t, CodeLocation codeLocation) {
    insert(t, t->getName(), codeLocation);
}

template<class T>
void ASTMap<T>::insert(T t, std::string name, CodeLocation codeLocation) {
    if (!internalMap.insert(std::make_pair(name, t)).second) {
        throw ExistingIdentifierError(codeLocation, name);
    }
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
class AST::ASTMap<FunctionDef*>;
template
class AST::ASTMap<FunctionDecl*>;
template
class AST::ASTMap<FunctionDeclPtr>;
template
class AST::ASTMap<VariableDefStmt*>;
template
class AST::ASTMap<TypePtr>;
