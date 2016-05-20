/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_ERRORS_HPP
#define AUC_ERRORS_HPP

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

} // namespace AST

#endif // AUC_ERRORS_HPP
