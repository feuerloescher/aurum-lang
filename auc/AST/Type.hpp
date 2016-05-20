/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPE_HPP
#define AUC_TYPE_HPP

#include "common.hpp"

#include <string>

namespace AST {

class Type {

public:
    virtual std::string getName() = 0;

}; // class Type

} // namespace AST

#endif // AUC_TYPE_HPP
