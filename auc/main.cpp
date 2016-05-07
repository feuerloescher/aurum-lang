/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "AST/AST.hpp"

#include <iostream>

int main() {
    AST::AST ast;
    std::cout << ast.toString() << std::endl;
    return 0;
}
