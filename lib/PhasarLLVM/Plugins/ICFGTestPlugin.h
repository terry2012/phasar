/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

#ifndef ICFGTESTPLUGIN_H_
#define ICFGTESTPLUGIN_H_

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <json.hpp>

#include <phasar/PhasarLLVM/Plugins/Interfaces/ControlFlow/ICFGPlugin.h>

namespace llvm {
class Instruction;
class Function;
} // namespace llvm

namespace psr {

using json = nlohmann::json;

class ICFGTestPlugin : public ICFGPlugin {
public:
  typedef const llvm::Instruction *n_t;
  typedef const llvm::Function *m_t;

  ICFGTestPlugin(ProjectIRDB &IRDB, const std::vector<std::string> EntryPoints);

  ~ICFGTestPlugin() override = default;

  // CFG parts

  m_t getFunctionOf(n_t stmt) const override;

  std::vector<n_t> getPredsOf(n_t stmt) const override;

  std::vector<n_t> getSuccsOf(n_t stmt) const override;

  std::vector<std::pair<n_t, n_t>>
  getAllControlFlowEdges(m_t fun) const override;

  std::vector<n_t> getAllInstructionsOf(m_t fun) const override;

  bool isExitStmt(n_t stmt) const override;

  bool isStartPoint(n_t stmt) const override;

  bool isFieldLoad(n_t stmt) const override;

  bool isFieldStore(n_t stmt) const override;

  bool isFallThroughSuccessor(n_t stmt, n_t succ) const override;

  bool isBranchTarget(n_t stmt, n_t succ) const override;

  std::string getStatementId(n_t stmt) const override;

  std::string getFunctionName(m_t fun) const override;

  void print(m_t F, std::ostream &OS = std::cout) const override;

  nlohmann::json getAsJson(m_t F) const override;

  // ICFG parts

  std::set<m_t> getAllFunctions() const override;

  m_t getFunction(const std::string &fun) const override;

  bool isCallStmt(n_t stmt) const override;

  bool isIndirectFunctionCall(n_t stmt) const override;

  bool isVirtualFunctionCall(n_t stmt) const override;

  std::set<n_t> allNonCallStartNodes() const override;

  std::set<m_t> getCalleesOfCallAt(n_t stmt) const override;

  std::set<n_t> getCallersOf(m_t fun) const override;

  std::set<n_t> getCallsFromWithin(m_t fun) const override;

  std::set<n_t> getStartPointsOf(m_t fun) const override;

  std::set<n_t> getExitPointsOf(m_t fun) const override;

  std::set<n_t> getReturnSitesOfCallAt(n_t stmt) const override;

  void print(std::ostream &OS = std::cout) const override;

  nlohmann::json getAsJson() const override;
};

extern "C" std::unique_ptr<ICFGPlugin>
makeICFGTestPlugin(ProjectIRDB &IRDB,
                   const std::vector<std::string> EntryPoints);
} // namespace psr

#endif
