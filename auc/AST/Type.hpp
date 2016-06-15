/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#ifndef AUC_TYPE_HPP
#define AUC_TYPE_HPP

#include "common.hpp"

#include <llvm/IR/Type.h>
#include <string>

namespace AST {

class Type {

protected:
    std::string name;
    llvm::Type* llvmType;

public:
    Type(std::string name);

    std::string getName();
    llvm::Type* getLLVMType();
    virtual void createLLVMType(llvm::LLVMContext& llvmContext) = 0;

}; // class Type

} // namespace AST

#endif // AUC_TYPE_HPP
