/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "StdLibPass.hpp"
#include "AST/ScalarTypes.hpp"
#include "AST/TypeStmt.hpp"

using namespace AST;
using namespace Passes;

StdLibPass::StdLibPass(AST::AbstractSyntaxTree& ast)
    : ast(ast), types(ast.getTypes()) {
}

void StdLibPass::run() {
    addScalarTypes();
    /// more to come...
}

void StdLibPass::addScalarTypes() {
    for (bool isSigned : {false, true}) {
        for (unsigned int width : {8, 16, 32, 64}) {
            std::string intTypeName =
                (isSigned ? "int" : "uint") + std::to_string(width);
            std::shared_ptr<IntType> intType = std::make_shared<IntType>(
                intTypeName, width, isSigned);
            types.insert(intType);

            std::shared_ptr<TypeStmt> intTypeStmt = std::make_shared<TypeStmt>(
                intTypeName, CodeLocation::none);
            intTypeStmt->setType(intType);

            for (std::string op : {"+", "-", "*", "/", "="}) {
                std::shared_ptr<MethodDef> intMethod =
                    std::make_shared<MethodDef>(intTypeStmt, op, intTypeStmt,
                    CodeLocation::none);
                intMethod->getParameters().push_back(
                    std::make_shared<VariableDefStmt>(intTypeStmt, "param",
                    CodeLocation::none));
                ast.getStdLibMethodDefs().insert(intMethod);
                intType->getMethodDefs().insert(intMethod.get());
            }
            for (std::string op : {"++", "--"}) {
                std::shared_ptr<MethodDef> intMethod =
                    std::make_shared<MethodDef>(intTypeStmt, op, intTypeStmt,
                    CodeLocation::none);
                ast.getStdLibMethodDefs().insert(intMethod);
                intType->getMethodDefs().insert(intMethod.get());
            }
        }
    }
    types.insert(types.find("int8"), "byte");
    types.insert(types.find("uint8"), "char");
    types.insert(types.find("int16"), "short");
    types.insert(types.find("uint16"), "ushort");
    types.insert(types.find("int32"), "int");
    types.insert(types.find("uint32"), "uint");
    types.insert(types.find("int64"), "long");
    types.insert(types.find("uint64"), "ulong");
}
