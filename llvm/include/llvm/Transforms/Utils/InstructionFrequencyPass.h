#ifndef LLVM_TRANSFORMS_UTILS_INSTRUCTIONFREQUENCYPASS_H
#define LLVM_TRANSFORMS_UTILS_INSTRUCTIONFREQUENCYPASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"

#include <map>
#include <string>

namespace llvm {

enum InstructionCategory {
    IC_Arithmetic,
    IC_Logical,
    IC_Comparison,
    IC_Memory,
    IC_ControlFlow,
    IC_FunctionCall,
    IC_Other
};

class InstructionFrequencyPass : public PassInfoMixin<InstructionFrequencyPass> {
public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

    // Add the name method
    std::string getPassName() const {
        return "Instruction Frequency Pass";
    }

private:
    InstructionCategory classifyInstruction(Instruction &I);
    std::string categoryToString(InstructionCategory Cat);

    // Frequency table to track instruction frequencies
    std::map<std::string, std::map<InstructionCategory, unsigned>> FrequencyTable;
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_INSTRUCTIONFREQUENCYPASS_H
