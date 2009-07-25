//===-- X86AsmPrinter.cpp - Convert X86 LLVM IR to X86 assembly -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file the shared super class printer that converts from our internal
// representation of machine-dependent LLVM code to Intel and AT&T format
// assembly language.
// This printer is the output mechanism used by `llc'.
//
//===----------------------------------------------------------------------===//

#include "X86.h"
#include "X86ATTAsmPrinter.h"
#include "X86IntelAsmPrinter.h"
#include "X86Subtarget.h"
#include "llvm/Target/TargetRegistry.h"
using namespace llvm;

/// createX86CodePrinterPass - Returns a pass that prints the X86 assembly code
/// for a MachineFunction to the given output stream, using the given target
/// machine description.
///
static FunctionPass *createX86CodePrinterPass(formatted_raw_ostream &o,
                                              TargetMachine &tm,
                                              bool verbose) {
  const X86Subtarget *Subtarget = &tm.getSubtarget<X86Subtarget>();

  if (Subtarget->isFlavorIntel())
    return new X86IntelAsmPrinter(o, tm, tm.getTargetAsmInfo(), verbose);
  return new X86ATTAsmPrinter(o, tm, tm.getTargetAsmInfo(), verbose);
}

// Force static initialization.
extern "C" void LLVMInitializeX86AsmPrinter() { 
  TargetRegistry::RegisterAsmPrinter(TheX86_32Target, createX86CodePrinterPass);
  TargetRegistry::RegisterAsmPrinter(TheX86_64Target, createX86CodePrinterPass);
}
