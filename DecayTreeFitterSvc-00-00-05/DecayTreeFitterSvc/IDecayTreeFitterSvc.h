#ifndef IDECAY_TREE_FITTER_SVC_H
#define IDECAY_TREE_FITTER_SVC_H

#include <iostream>
#include "GaudiKernel/IService.h"
#include "DecayTreeFitterSvc/ParticleBase.h"
#include <string>

using namespace DecayTreeFitter;

static const InterfaceID IID_IDecayTreeFitterSvc("IDecayTreeFitterSvc", 1, 0);

class IDecayTreeFitterSvc : virtual public IService {
		public:
				virtual ~IDecayTreeFitterSvc() {}
				static const InterfaceID& interfaceID() { return IID_IDecayTreeFitterSvc; }
};
#endif
