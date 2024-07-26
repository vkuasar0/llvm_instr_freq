// #include "clang/Frontend/EmitInstrFreqAction.h"
// #include "clang/Frontend/CompilerInstance.h"
// #include "clang/Frontend/FrontendAction.h"
// #include "llvm/IR/Function.h"
// #include "llvm/IR/PassManager.h"
// #include "llvm/Transforms/Utils/InstructionFrequencyPass.h"
// #include "llvm/IR/Module.h"
// #include "llvm/IR/LegacyPassManager.h"
// #include "llvm/IR/PassManager.h"
// #include "llvm/Passes/PassBuilder.h"
// #include "clang/CodeGen/CodeGenAction.h"

// using namespace clang;
// using namespace llvm;

// EmitInstrFreqConsumer::EmitInstrFreqConsumer(CompilerInstance &CI) : CI(CI) {}

// void EmitInstrFreqConsumer::HandleTranslationUnit(clang::ASTContext &Context) {
//     // Ensure LLVM IR emission is enabled
//     auto &CodeGenOpts = CI.getCodeGenOpts();

//     if (!CodeGenOpts.EmitLLVM) {
//         llvm::errs() << "LLVM IR emission is not enabled.\n";
//         return;
//     }

//     // Retrieve the LLVM Module using the CompilerInstance
//     auto *Action = static_cast<CodeGenAction*>(CI.getFrontendAction());
//     llvm::Module *Module = Action->takeModule().get();
    
//     if (!Module) {
//         llvm::errs() << "LLVM Module is not available.\n";
//         return;
//     }

//     // Create FunctionPassManager and register the pass
//     FunctionPassManager FPM;
//     FPM.addPass(InstructionFrequencyPass());

//     // Create AnalysisManager
//     FunctionAnalysisManager FAM;
//     PassBuilder PB;
//     PB.registerFunctionAnalyses(FAM);

//     // Register the pass with FunctionPassManager
//     FPM.addPass(InstructionFrequencyPass());

//     // Iterate over all functions in the module
//     for (auto &F : *Module) {
//         FPM.run(F, FAM);
//     }
// }

// std::unique_ptr<clang::ASTConsumer> EmitInstrFreqAction::CreateASTConsumer(
//     clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
//     return std::make_unique<EmitInstrFreqConsumer>(Compiler);
// }
