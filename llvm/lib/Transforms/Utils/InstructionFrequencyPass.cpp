#include "llvm/Transforms/Utils/InstructionFrequencyPass.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/Module.h"
#include <fstream>

using namespace llvm;

PreservedAnalyses InstructionFrequencyPass::run(Function &F, FunctionAnalysisManager &) {
    std::map<InstructionCategory, unsigned> &FreqMap = FrequencyTable[F.getName().str()];
    for (auto &BB : F) {
        for (auto &I : BB) {
            InstructionCategory Cat = classifyInstruction(I);
            FreqMap[Cat]++;
        }
    }

    // Do finalization in the last pass run
    if (&F == &F.getParent()->getFunctionList().back()) {
        std::string Filename = F.getParent()->getModuleIdentifier() + ".ic";
        std::ofstream OutFile(Filename);
        for (const auto &FuncEntry : FrequencyTable) {
            OutFile << "Function: " << FuncEntry.first << "\n";
            for (const auto &CatEntry : FuncEntry.second) {
                OutFile << "  " << categoryToString(CatEntry.first) << ": " << CatEntry.second << "\n";
            }
        }
        OutFile.close();
    }

    return PreservedAnalyses::all();
}

InstructionCategory InstructionFrequencyPass::classifyInstruction(Instruction &I) {
    switch (I.getOpcode()) {
        case Instruction::Add:
        case Instruction::Sub:
        case Instruction::Mul:
        case Instruction::UDiv:
        case Instruction::SDiv:
        case Instruction::URem:
        case Instruction::SRem:
            return IC_Arithmetic;

        case Instruction::And:
        case Instruction::Or:
        case Instruction::Xor:
        case Instruction::Shl:
        case Instruction::LShr:
        case Instruction::AShr:
            return IC_Logical;

        case Instruction::ICmp:
        case Instruction::FCmp:
            return IC_Comparison;

        case Instruction::Load:
        case Instruction::Store:
        case Instruction::Alloca:
        case Instruction::GetElementPtr:
            return IC_Memory;

        case Instruction::Br:
        case Instruction::Switch:
        case Instruction::PHI:
            return IC_ControlFlow;

        case Instruction::Call:
        case Instruction::Invoke:
        case Instruction::Ret:
            return IC_FunctionCall;

        default:
            return IC_Other;
    }
}

std::string InstructionFrequencyPass::categoryToString(InstructionCategory Cat) {
    switch (Cat) {
        case IC_Arithmetic: return "Arithmetic";
        case IC_Logical: return "Logical";
        case IC_Comparison: return "Comparison";
        case IC_Memory: return "Memory";
        case IC_ControlFlow: return "Control Flow";
        case IC_FunctionCall: return "Function Call";
        default: return "Other";
    }
}

// extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeInstructionFrequencyPass() {
//     PassBuilder PB;
//     PB.registerFunctionAnalyses();
//     PB.registerFunctionPass([]() -> std::unique_ptr<FunctionPass> {
//         return std::make_unique<InstructionFrequencyPass>();
//     });
// }