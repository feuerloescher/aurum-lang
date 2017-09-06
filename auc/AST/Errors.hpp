/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ERRORS_HPP
#define AUC_ERRORS_HPP

#include "common.hpp"
#include "Types/Type.hpp"

#include <exception>

namespace AST {

class ExistingIdentifierError : public std::runtime_error {
public:
    ExistingIdentifierError(std::string identifier)
            : std::runtime_error("The identifier '" + identifier
            + "' already exists in this context.") {
    }
};

class UnknownIdentifierError : public std::runtime_error {
public:
    UnknownIdentifierError(std::string identifier)
            : std::runtime_error("The identifier '" + identifier
            + "' is unknown in this context.") {
    }
};

class ArgumentCountError : public std::runtime_error {
public:
    ArgumentCountError(std::string functionName,
            unsigned int expectedParameters, unsigned int providedParameters)
            : std::runtime_error("The function '" + functionName
            + "' expects " + std::to_string(expectedParameters)
            + " parameters, but is provided " + std::to_string(providedParameters)
            + ".") {
    }
};

class ArgumentTypeError : public std::runtime_error {
public:
    ArgumentTypeError(std::string functionName, unsigned int argumentIndex,
            TypePtr expectedType, TypePtr providedType)
            : std::runtime_error("The function '" + functionName
            + "' expects argument " + std::to_string(argumentIndex)
            + " to be of type " + expectedType->getName() + ", but is provided "
            + providedType->getName() + ".") {
    }
};

class ConditionTypeError : public std::runtime_error {
public:
    ConditionTypeError(TypePtr providedType)
            : std::runtime_error("The condition has to be of type bool, "
            "but is of type " + providedType->getName() + ".") {
    }
};

} // namespace AST

#endif // AUC_ERRORS_HPP
