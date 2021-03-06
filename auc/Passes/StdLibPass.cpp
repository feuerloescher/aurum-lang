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
using namespace type;

StdLibPass::StdLibPass(AST::AbstractSyntaxTree& ast)
    : ast(ast), types(ast.getTypes()) {
}

void StdLibPass::run() {
    addScalarTypes();
    /// more to come...
}

void StdLibPass::addScalarTypes() {
    std::shared_ptr<VoidType> voidType = std::make_shared<VoidType>();
    types.insert(voidType, CodeLocation::none);

    std::shared_ptr<IntType> boolType = std::make_shared<IntType>(
        "bool", 8, false);
    types.insert(boolType, CodeLocation::none);
    std::shared_ptr<TypeStmt> boolTypeStmt = std::make_shared<BasicTypeStmt>(
        "bool", CodeLocation::none);
    boolTypeStmt->setType(boolType);

    for (bool isSigned : {false, true}) {
        for (unsigned int width : {8, 16, 32, 64}) {
            std::string intTypeName =
                (isSigned ? "int" : "uint") + std::to_string(width);
            std::shared_ptr<IntType> intType = std::make_shared<IntType>(
                intTypeName, width, isSigned);
            types.insert(intType, CodeLocation::none);

            std::shared_ptr<BasicTypeStmt> intTypeStmt = std::make_shared<BasicTypeStmt>(
                    intTypeName, CodeLocation::none);
            // intTypeStmt type is set to intType in IdentifierPass
            std::shared_ptr<BasicTypeStmt> intRefTypeStmt = std::make_shared<BasicTypeStmt>(
                    intTypeName, CodeLocation::none);
            intRefTypeStmt->setIsReference(true);
            // intRefTypeStmt type is set to intType in IdentifierPass

            for (std::string op : {"+", "-", "*", "/"}) {
                std::shared_ptr<FunctionDecl> intFunc =
                        std::make_shared<FunctionDecl>(intTypeStmt, op, true,
                                CodeLocation::none);
                intFunc->getParameters().push_back(
                        std::make_shared<VariableDefStmt>(intTypeStmt, "self", CodeLocation::none));
                intFunc->getParameters().push_back(
                        std::make_shared<VariableDefStmt>(intTypeStmt, "param", CodeLocation::none));
                ast.getStdLibFunctionDecls().push_back(intFunc);
                // function is added to intType in IdentifierPass
            }
            for (std::string op : {"+=", "-=", "*=", "/=", "="}) {
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
                        std::make_shared<VariableDefStmt>(intTypeStmt, "self", CodeLocation::none));
                intFunc->getParameters().push_back(
                    std::make_shared<VariableDefStmt>(intTypeStmt, "param", CodeLocation::none));
                ast.getStdLibFunctionDecls().push_back(intFunc);
                // function is added to intType in IdentifierPass
            }
        }
    }
    types.insert(types.find("int8"), "byte", CodeLocation::none);
    types.insert(types.find("uint8"), "char", CodeLocation::none);
    types.insert(types.find("int16"), "short", CodeLocation::none);
    types.insert(types.find("uint16"), "ushort", CodeLocation::none);
    types.insert(types.find("int32"), "int", CodeLocation::none);
    types.insert(types.find("uint32"), "uint", CodeLocation::none);
    types.insert(types.find("int64"), "long", CodeLocation::none);
    types.insert(types.find("uint64"), "ulong", CodeLocation::none);
}
