/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "StdLibPass.hpp"
#include "Types/ScalarTypes.hpp"
#include "AST/TypeStmt.hpp"
#include "AST/Statements.hpp"

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
    std::shared_ptr<IntType> boolType = std::make_shared<IntType>(
        "bool", 1, false);
    types.insert(boolType);
    std::shared_ptr<TypeStmt> boolTypeStmt = std::make_shared<TypeStmt>(
        "bool", CodeLocation::none);
    boolTypeStmt->setType(boolType);

    for (bool isSigned : {false, true}) {
        for (unsigned int width : {8, 16, 32, 64}) {
            std::string intTypeName =
                (isSigned ? "int" : "uint") + std::to_string(width);
            std::shared_ptr<IntType> intType = std::make_shared<IntType>(
                intTypeName, width, isSigned);
            types.insert(intType);

            std::shared_ptr<TypeStmt> intTypeStmt = std::make_shared<TypeStmt>(
                    intTypeName, CodeLocation::none);
            // intTypeStmt type is set to intType in IdentifierPass
            #warning intRefTypeStmt has to declare a reference-to-int type
            std::shared_ptr<TypeStmt> intRefTypeStmt = std::make_shared<TypeStmt>(
                    intTypeName, CodeLocation::none);
            // intRefTypeStmt type is set to intType in IdentifierPass

            for (std::string op : {"+", "-", "*", "/", "="}) {
                std::shared_ptr<FunctionDecl> intFunc =
                    std::make_shared<FunctionDecl>(intTypeStmt, op, true,
                    CodeLocation::none);
                intFunc->getParameters().push_back(
                        std::make_shared<VariableDefStmt>(intRefTypeStmt, "self", CodeLocation::none));
                intFunc->getParameters().push_back(
                        std::make_shared<VariableDefStmt>(intTypeStmt, "param", CodeLocation::none));
                ast.getStdLibFunctionDecls().push_back(intFunc);
                // function is added to intType in IdentifierPass
            }
            for (std::string op : {"++", "--"}) {
                std::shared_ptr<FunctionDecl> intFunc =
                    std::make_shared<FunctionDecl>(intTypeStmt, op, true, CodeLocation::none);
                intFunc->getParameters().push_back(
                        std::make_shared<VariableDefStmt>(intRefTypeStmt, "self", CodeLocation::none));
                ast.getStdLibFunctionDecls().push_back(intFunc);
                // function is added to intType in IdentifierPass
            }
            for (std::string op : {"==", "!=", ">", "<", ">=", "<="}) {
                std::shared_ptr<FunctionDecl> intFunc =
                    std::make_shared<FunctionDecl>(boolTypeStmt, op, true,
                    CodeLocation::none);
                intFunc->getParameters().push_back(
                        std::make_shared<VariableDefStmt>(intRefTypeStmt, "self", CodeLocation::none));
                intFunc->getParameters().push_back(
                    std::make_shared<VariableDefStmt>(intTypeStmt, "param", CodeLocation::none));
                ast.getStdLibFunctionDecls().push_back(intFunc);
                // function is added to intType in IdentifierPass
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
