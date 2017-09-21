/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ERRORS_HPP
#define AUC_ERRORS_HPP

#include "common.hpp"
#include "AST/CodeLocation.hpp"
#include "Types/Type.hpp"

#include <exception>

namespace AST {

class ASTError : public std::runtime_error {
public:
    ASTError(CodeLocation codeLocation, std::string message)
            : std::runtime_error(codeLocation.toString() + ": " + message) {
    }
};

class ExistingIdentifierError : public ASTError {
public:
    ExistingIdentifierError(CodeLocation codeLocation, std::string identifier)
            : ASTError(codeLocation, "The identifier '" + identifier
            + "' already exists in this context.") {
    }
};

class UnknownIdentifierError : public ASTError {
public:
    UnknownIdentifierError(CodeLocation codeLocation, std::string identifier)
            : ASTError(codeLocation, "The identifier '" + identifier
            + "' is unknown in this context.") {
    }
};

class ArgumentCountError : public ASTError {
public:
    ArgumentCountError(CodeLocation codeLocation, std::string functionName,
            unsigned int expectedParameters, unsigned int providedParameters)
            : ASTError(codeLocation, "The function '" + functionName
            + "' expects " + std::to_string(expectedParameters)
            + " parameters, but is provided " + std::to_string(providedParameters)
            + ".") {
    }
};

class ArgumentTypeError : public ASTError {
public:
    ArgumentTypeError(CodeLocation codeLocation, std::string functionName, unsigned int argumentIndex,
            type::TypePtr expectedType, type::TypePtr providedType)
            : ASTError(codeLocation, "The function '" + functionName
            + "' expects argument " + std::to_string(argumentIndex)
            + " to be of type " + expectedType->getName() + ", but is provided "
            + providedType->getName() + ".") {
    }
};

class ArgumentReferenceError : public ASTError {
public:
    ArgumentReferenceError(CodeLocation codeLocation, std::string functionName, unsigned int argumentIndex, std::string parameterName)
            : ASTError(codeLocation, "The function '" + functionName
            + "' expects argument " + std::to_string(argumentIndex) + " (parameter '" + parameterName
            + "') to be a referenceable type.") {
    }
};

class ConditionTypeError : public ASTError {
public:
    ConditionTypeError(CodeLocation codeLocation, type::TypePtr providedType)
            : ASTError(codeLocation, "The condition has to be of type bool, "
            "but is of type " + providedType->getName() + ".") {
    }
};

class ReferenceInitializationError : public ASTError {
public:
    ReferenceInitializationError(CodeLocation codeLocation)
            : ASTError(codeLocation, "A reference variable cannot be declared without being initialized.") {
    }
};

} // namespace AST

#endif // AUC_ERRORS_HPP
