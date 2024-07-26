#include "llvm/Transforms/Utils/InstructionFrequencyPassAdapter.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Passes/PassBuilder.h"

using namespace llvm;

char InstructionFrequencyPassAdapter::ID = 0;

bool InstructionFrequencyPassAdapter::runOnModule(Module &M) {
    // Create a FunctionAnalysisManager for the new pass manager
    FunctionAnalysisManager FAM;
    PassBuilder PB;
    PB.registerFunctionAnalyses(FAM);

    // Run the new pass manager pass on each function
    for (Function &F : M) {
        NewPass.run(F, FAM);
    }

    return false; // No modifications to the module
}
