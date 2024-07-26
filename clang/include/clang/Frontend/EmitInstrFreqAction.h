#ifndef LLVM_CLANG_FRONTEND_EMITINSTRFREQACTION_H
#define LLVM_CLANG_FRONTEND_EMITINSTRFREQACTION_H

#include "clang/Frontend/FrontendAction.h"

class EmitInstrFreqConsumer : public clang::ASTConsumer {
    clang::CompilerInstance &CI;

public:
    EmitInstrFreqConsumer(clang::CompilerInstance &CI);

    void HandleTranslationUnit(clang::ASTContext &Context) override;
};

class EmitInstrFreqAction : public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile) override;
};

#endif // LLVM_CLANG_FRONTEND_EMITINSTRFREQACTION_H
