#include "GaudiKernel/DeclareFactoryEntries.h"

#include "DecayTreeFitterSvc/DecayTreeFitterSvc.h"

DECLARE_SERVICE_FACTORY( DecayTreeFitterSvc )

DECLARE_FACTORY_ENTRIES( DecayTreeFitterSvc ) { 
  DECLARE_SERVICE( DecayTreeFitterSvc );
}
