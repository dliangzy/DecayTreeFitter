#ifndef DECAY_TREE_FITTER_SVC_H
#define DECAY_TREE_FITTER_SVC_H

#include "GaudiKernel/Service.h"
#include "DecayTreeFitterSvc/IDecayTreeFitterSvc.h"
#include "DecayTreeFitterSvc/ParticleBase.h"
#include "MdcRecEvent/RecMdcTrack.h"
#include "MdcRecEvent/RecMdcKalTrack.h"
#include "EmcRecEventModel/RecEmcShower.h"
#include "DecayTreeFitterSvc/DecayTree.h"


using namespace DecayTreeFitter;
class DecayTreeFitterSvc : public Service, virtual public IDecayTreeFitterSvc {


		public:
				typedef std::vector<int> Vint;
				DecayTreeFitterSvc(const std::string& name, ISvcLocator* svcLoc);
				virtual ~DecayTreeFitterSvc();
				virtual StatusCode initialize();
				virtual StatusCode finalize();
				virtual StatusCode queryInterface(const InterfaceID& riid, void** ppvIF);
				void init();
				void AddFinalState(const int number, const TString name, const RecMdcKalTrack *trk);
				void AddFinalState(const int number, const TString name, const RecEmcShower *trk);
				void AddFinalState(const int number, const TString name, const HepLorentzVector trk);
				void AddInternalParticle(const int number, const TString name, Vint dauglist);
				void AddResonance(const int number, const TString name, Vint dauglist);
				void AddCMS(const int number, const TString name, const HepLorentzVector trk, Vint dauglist);
				bool Fit();
				double chisq();
				double decayLength(TString name);
				HepLorentzVector p4(const int index);

		private:
				ParticleBase *pbtest;
				DecayTree *decayTree;
				double m_debug;
};


#endif
