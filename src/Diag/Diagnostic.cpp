
/**
  Copyright(c) 2016 - 2017 Denis Blank <denis.blank at outlook dot com>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
**/

#include "Diagnostic.hpp"

#include "llvm/Support/ErrorHandling.h"

Severity getDiagnosticSeverity(Diagnostic diag) {
  switch (diag) {
#define FOR_EACH_DIAG(SEVERITY, NAME, MESSAGE)                                 \
  case Diagnostic::DIAG_AS_ENUM(SEVERITY, NAME):                               \
    return Severity::SEVERITY;
#include "Diagnostic.inl"
  }
  llvm_unreachable("Unknown diagnostic!");
}

char const* getDiagnosticMessage(Diagnostic diag) {
  switch (diag) {
#define FOR_EACH_DIAG(SEVERITY, NAME, MESSAGE)                                 \
  case Diagnostic::DIAG_AS_ENUM(SEVERITY, NAME):                               \
    return MESSAGE;
#include "Diagnostic.inl"
  }
  llvm_unreachable("Unknown diagnostic!");
}
