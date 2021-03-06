/**
 * @author Sebastian Roland <seroland86@gmail.com>
 */

#ifndef MEMSETINSTFLOWFUNCTION_H
#define MEMSETINSTFLOWFUNCTION_H

#include <phasar/PhasarLLVM/DataFlowSolver/IfdsIde/IFDSFieldSensTaintAnalysis/FlowFunctions/FlowFunctionBase.h>

namespace psr {

class MemSetInstFlowFunction : public FlowFunctionBase {
public:
  MemSetInstFlowFunction(const llvm::Instruction *_currentInst,
                         TraceStats &_traceStats, ExtendedValue _zeroValue)
      : FlowFunctionBase(_currentInst, _traceStats, _zeroValue) {}
  ~MemSetInstFlowFunction() override = default;

  std::set<ExtendedValue> computeTargetsExt(ExtendedValue &fact) override;
};

} // namespace psr

#endif // MEMSETINSTFLOWFUNCTION_H
