/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

/*
 * IFDSTabulationProblem.h
 *
 *  Created on: 04.08.2016
 *      Author: pdschbrt
 */

#ifndef PHASAR_PHASARLLVM_IFDSIDE_IFDSTABULATIONPROBLEM_H_
#define PHASAR_PHASARLLVM_IFDSIDE_IFDSTABULATIONPROBLEM_H_

#include <iostream>
#include <map>
#include <set>
#include <string>

#include <phasar/PhasarLLVM/ControlFlow/ICFG.h>
#include <phasar/PhasarLLVM/ControlFlow/LLVMBasedICFG.h>
#include <phasar/PhasarLLVM/DataFlowSolver/IfdsIde/FlowFunctions.h>
#include <phasar/PhasarLLVM/DataFlowSolver/IfdsIde/IFDSIDESolverConfig.h>
#include <phasar/PhasarLLVM/DataFlowSolver/IfdsIde/Solver/SolverResults.h>
#include <phasar/PhasarLLVM/Utils/Printer.h>

namespace psr {

struct HasNoConfigurationType;

class ProjectIRDB;
template <typename T, typename M> class TypeHierarchy;
template <typename V, typename N> class PointsToInfo;

template <typename N, typename D, typename M, typename T, typename V,
          typename I>
class IFDSTabulationProblem : public virtual FlowFunctions<N, D, M>,
                              public virtual NodePrinter<N>,
                              public virtual DataFlowFactPrinter<D>,
                              public virtual FunctionPrinter<M> {
  static_assert(std::is_base_of_v<ICFG<N, M>, I>,
                "I must implement the ICFG interface!");

protected:
  IFDSIDESolverConfig SolverConfig;
  const ProjectIRDB *IRDB;
  const TypeHierarchy<T, M> *TH;
  const I *ICF;
  const PointsToInfo<V, N> *PT;
  D ZeroValue;
  std::set<std::string> EntryPoints;

public:
  using ConfigurationTy = HasNoConfigurationType;

  IFDSTabulationProblem(const ProjectIRDB *IRDB, const TypeHierarchy<T, M> *TH,
                        const I *ICF, const PointsToInfo<V, N> *PT,
                        std::set<std::string> EntryPoints = {})
      : IRDB(IRDB), TH(TH), ICF(ICF), PT(PT), EntryPoints(EntryPoints) {}

  ~IFDSTabulationProblem() override = default;

  virtual D createZeroValue() const = 0;

  virtual bool isZeroValue(D d) const = 0;

  virtual std::map<N, std::set<D>> initialSeeds() = 0;

  D getZeroValue() const { return ZeroValue; }

  std::set<std::string> getEntryPoints() const { return EntryPoints; }

  const ProjectIRDB *getProjectIRDB() const { return IRDB; }

  const TypeHierarchy<T, M> *getTypeHierarchy() const { return TH; }

  const I *getICFG() const { return ICF; }

  const PointsToInfo<V, N> *getPointstoInfo() const { return PT; }

  void setIFDSIDESolverConfig(IFDSIDESolverConfig Config) {
    SolverConfig = Config;
  }

  IFDSIDESolverConfig getIFDSIDESolverConfig() const { return SolverConfig; }

  virtual void emitTextReport(const SolverResults<N, D, BinaryDomain> &SR,
                              std::ostream &OS = std::cout) {
    OS << "No text report available!\n";
  }

  virtual void emitGraphicalReport(const SolverResults<N, D, BinaryDomain> &SR,
                                   std::ostream &OS = std::cout) {
    OS << "No graphical report available!\n";
  }
};
} // namespace psr

#endif
