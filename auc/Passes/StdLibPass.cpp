/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "StdLibPass.hpp"
#include "AST/ScalarTypes.hpp"

using namespace AST;
using namespace Passes;

StdLibPass::StdLibPass(AST::AbstractSyntaxTree& ast) : ast(ast) {
}

void StdLibPass::run() {
    addStdLibTypes();
    /// more to come...
}

void StdLibPass::addStdLibTypes() {
    ast.getTypes().insert(std::make_shared<IntType>("uint32", 32, false));
}



//~ void LLVMPass::runOn(UnaryOpExpr& stmt) {
    //~ stmt.getOperand()->runPass(*this);
    //~ /// \todo Add standard operators in StdLibPass
    //~ if (stmt.getName() == "-") {
        //~ stmt.setLLVMValue(
            //~ irBuilder.CreateNeg(stmt.getOperand()->getLLVMValue(),
            //~ "negtmp"));
    //~ }
//~ }

//~ void LLVMPass::runOn(BinaryOpExpr& stmt) {
    //~ stmt.getOperand1()->runPass(*this);
    //~ stmt.getOperand2()->runPass(*this);
    //~ /// \todo Add standard operators in StdLibPass
    //~ if (stmt.getName() == "+") {
        //~ stmt.setLLVMValue(
            //~ irBuilder.CreateAdd(stmt.getOperand1()->getLLVMValue(),
            //~ stmt.getOperand2()->getLLVMValue(), "addtmp"));
    //~ }
//~ }

//~ void LLVMPass::runOn(UnaryAssignOpExpr& stmt) {
    //~ stmt.getVariable()->runPass(*this);
    //~ /// \todo Add standard operators in StdLibPass
    //~ if (stmt.getName() == "++") {
        //~ /// \todo Store LLVM value for '1' as a class member
        //~ llvm::Value* llvmValue = irBuilder.CreateAdd(
            //~ llvm::ConstantInt::get(llvmContext,
            //~ llvm::APInt(32u, (uint64_t) 1, false)),
            //~ stmt.getVariable()->getLLVMValue(),
            //~ "inctmp");
        //~ stmt.setLLVMValue(llvmValue);
        //~ stmt.setLLVMValue(irBuilder.CreateStore(
            //~ stmt.getVariable()->getVariableDefStmt()->getAllocaInst(),
            //~ llvmValue));
    //~ }
//~ }

//~ void LLVMPass::runOn(BinaryAssignOpExpr& stmt) {
    //~ stmt.getVariable()->runPass(*this);
    //~ stmt.getOperand()->runPass(*this);
    //~ /// \todo Add standard operators in StdLibPass
    //~ if (stmt.getName() == "=") {
        //~ stmt.setLLVMValue(irBuilder.CreateStore(
            //~ stmt.getVariable()->getVariableDefStmt()->getAllocaInst(),
            //~ stmt.getOperand()->getLLVMValue()));
    //~ }
//~ }
