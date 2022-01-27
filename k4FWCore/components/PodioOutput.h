#ifndef FWCORE_PODIOOUTPUT_H
#define FWCORE_PODIOOUTPUT_H

#include "GaudiAlg/GaudiAlgorithm.h"
#include "podio/ROOTWriter.h"

#include <vector>

// forward declarations
class PodioDataSvc;

class PodioOutput : public GaudiAlgorithm {

public:
  /// Constructor.
  PodioOutput(const std::string& name, ISvcLocator* svcLoc);

  /// Initialization of PodioOutput. Acquires the data service, creates ROOTWriter from podio
  virtual StatusCode initialize();
  virtual StatusCode execute();
  virtual StatusCode finalize();

private:
  /// Root file name the output is written to
  Gaudi::Property<std::string> m_filename{this, "filename", "output.root", "Name of the file to create"};
  /// Needed for collection ID table
  PodioDataSvc* m_podioDataSvc;
  // ROOT writer to persist events into .root files
  std::unique_ptr<podio::ROOTWriter> m_ROOTWriter;
};

#endif
