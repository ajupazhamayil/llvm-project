//===--- ExtensionRAIIObject.h - Use RAII for __extension__ -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  This file defines and implements the ExtensionRAIIObject class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_PARSE_EXTENSION_RAII_OBJECT_H
#define LLVM_CLANG_PARSE_EXTENSION_RAII_OBJECT_H

#include "clang/Basic/DiagnosticParse.h"

namespace clang {

  /// ExtensionRAIIObject - This saves the state of extension warnings when
  /// constructed and disables them.  When destructed, it restores them back to
  /// the way they used to be.  This is used to handle __extension__ in the
  /// parser.
  class ExtensionRAIIObject {
    void operator=(const ExtensionRAIIObject &);     // DO NOT IMPLEMENT
    ExtensionRAIIObject(const ExtensionRAIIObject&); // DO NOT IMPLEMENT
    Diagnostic &Diags;
    bool OldState;
  public:
    ExtensionRAIIObject(Diagnostic &diags) : Diags(diags) {
      OldState = Diags.getWarnOnExtensions();
      Diags.setWarnOnExtensions(false);
    }
    
    ~ExtensionRAIIObject() {
      Diags.setWarnOnExtensions(OldState);
    }
  };
}

#endif
