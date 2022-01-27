#include "PodioOutput.h"
#include "k4FWCore/PodioDataSvc.h"
#include "TFile.h"
#include "rootUtils.h"

DECLARE_COMPONENT(PodioOutput)

PodioOutput::PodioOutput(const std::string& name, ISvcLocator* svcLoc)
    : GaudiAlgorithm(name, svcLoc) {}

StatusCode PodioOutput::initialize() {
  if (GaudiAlgorithm::initialize().isFailure()) return StatusCode::FAILURE;

  // check whether we have the PodioEvtSvc active
  m_podioDataSvc = dynamic_cast<PodioDataSvc*>(evtSvc().get());
  if (nullptr  == m_podioDataSvc) {
    error() << "Could not get DataSvc!" << endmsg;
    return StatusCode::FAILURE;
  }

  m_ROOTWriter = std::make_unique<podio::ROOTWriter>(m_filename.value(), &(m_podioDataSvc->getProvider()));
  return StatusCode::SUCCESS;  
}

StatusCode PodioOutput::execute() {

  m_ROOTWriter->writeEvent();

  return StatusCode::SUCCESS;
}

StatusCode PodioOutput::finalize() {

  m_ROOTWriter->finish();

  return StatusCode::SUCCESS;
}
