#ifndef LLVM_TRANSFORMS_UTILS_INSTRUCTIONFREQUENCYPASSADAPTER_H
#define LLVM_TRANSFORMS_UTILS_INSTRUCTIONFREQUENCYPASSADAPTER_H

#include "llvm/Pass.h"
#include "llvm/Transforms/Utils/InstructionFrequencyPass.h"

namespace llvm {

class InstructionFrequencyPassAdapter : public ModulePass {
public:
    static char ID;

    InstructionFrequencyPassAdapter() : ModulePass(ID) {}

    bool runOnModule(Module &M) override;

    // Override the name method for legacy pass manager
    StringRef getPassName() const override {
        return "Instruction Frequency Pass Adapter";
    }

private:
    InstructionFrequencyPass NewPass;
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_INSTRUCTIONFREQUENCYPASSADAPTER_H
