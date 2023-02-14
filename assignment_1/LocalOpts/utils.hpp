#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/ValueMap.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/ConstantFolding.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

#pragma once

// Helper function to check if the instruction is an Add Inst
bool isAddInst(unsigned int opcode)
{
    bool ret;
    switch (opcode)
    {
    case Instruction::Add:
        ret = true;
        break;
    default:
        ret = false;
        break;
    }

    return ret;
}

// Helper function to check if the instruction is a Sub Inst
bool isSubInst(unsigned int opcode)
{
    bool ret;
    switch (opcode)
    {
    case Instruction::Sub:
        ret = true;
        break;
    default:
        ret = false;
        break;
    }

    return ret;
}

// Helper function to check if the instruction is a Mul Inst
bool isMulInst(unsigned int opcode)
{
    bool ret;
    switch (opcode)
    {
    case Instruction::Mul:
        ret = true;
        break;
    default:
        ret = false;
        break;
    }

    return ret;
}

// Helper function to check if the instruction is a Division Inst
bool isDivInst(unsigned int opcode)
{
    bool ret;
    switch (opcode)
    {
    case Instruction::SDiv:
        ret = true;
        break;
    case Instruction::UDiv:
        ret = true;
        break;
    default:
        ret = false;
        break;
    }

    return ret;
}

// This is a helper function to get the result of a constant expression
Constant *getConstExprResult(ConstantInt *firstOperand, ConstantInt *secondOperand, unsigned int opcode, Type *type)
{
    switch (opcode)
    {
    case Instruction::Add:
        return ConstantInt::get(type, firstOperand->getValue() + secondOperand->getValue());
        break;

    case Instruction::Sub:
        return ConstantInt::get(type, firstOperand->getValue() - secondOperand->getValue());
        break;

    case Instruction::Mul:
        return ConstantInt::get(type, firstOperand->getValue() * secondOperand->getValue());
        break;
    case Instruction::SDiv:
        return ConstantInt::get(type, firstOperand->getValue().sdiv(secondOperand->getValue()));
        break;
    case Instruction::UDiv:
        return ConstantInt::get(type, firstOperand->getValue().udiv(secondOperand->getValue()));
        break;

    default:
        break;
    }
    return nullptr;
}

// Helper function to check if a number is a power of two
bool isPowerOfTwo(unsigned int num)
{
    return (num & (num - 1)) == 0 ? true : false;
}