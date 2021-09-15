#include "GaudiKernel/MsgStream.h"
#include "DecayTreeFitterSvc/DecayTreeFitterSvc.h"
#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/RecoTrack.h"
#include "DecayTreeFitterSvc/RecoPhoton.h"
#include "DecayTreeFitterSvc/InternalParticle.h"
#include "DecayTreeFitterSvc/RootParticle.h"
#include "DecayTreeFitterSvc/DecayTree.h"


using namespace DecayTreeFitter;


DecayTreeFitterSvc::DecayTreeFitterSvc(const std::string& name, ISvcLocator* svcLoc) 
:Service(name, svcLoc) 
{
		declareProperty("debug", m_debug = 5);
}

DecayTreeFitterSvc::~DecayTreeFitterSvc(){


}


StatusCode DecayTreeFitterSvc::queryInterface(const InterfaceID& riid, void** ppvIF)
{
		if (IDecayTreeFitterSvc::interfaceID().versionMatch(riid)) {
				*ppvIF = dynamic_cast<IDecayTreeFitterSvc*>(this);
		}
		else {
				return Service::queryInterface(riid, ppvIF);
		}
		addRef();
		return StatusCode::SUCCESS;
}




StatusCode DecayTreeFitterSvc::initialize(){
		MsgStream log(messageService(), name());
		log << MSG::INFO << "@initialize()" << endreq;

		StatusCode sc = Service::initialize();
		if (sc.isSuccess()) cout << "Hellow world from DecayTreeFitterSvc!" << endl;
		decayTree = new DecayTree();

	//	pbtest = new ParticleBase();

		return sc;
}

StatusCode DecayTreeFitterSvc::finalize(){

		MsgStream log(messageService(), name());
		log << MSG::INFO << "@finalize()" << endreq;
		StatusCode sc = Service::finalize();
		return sc;


}

void DecayTreeFitterSvc::init(){
		decayTree->initialize();
}

void DecayTreeFitterSvc::AddFinalState(const int number, const TString name, const RecMdcKalTrack *trk){
		if(m_debug < 3){
				cout << "DecayTreeFitterSvc : test !" << endl;
		}
		cout << "Ok" << endl;
		decayTree->AddFinalState(number, name, trk);
}

void DecayTreeFitterSvc::AddFinalState(const int number, const TString name, const RecEmcShower *trk){
		if(m_debug < 3){
				cout << "DecayTreeFitterSvc : test !" << endl;
		}
		decayTree->AddFinalState(number, name, trk);
}


void DecayTreeFitterSvc::AddFinalState(const int number, const TString name, const HepLorentzVector trk){
		if(m_debug < 3){
				cout << "DecayTreeFitterSvc : test !" << endl;
		}
		decayTree->AddFinalState(number, name, trk);
}


void DecayTreeFitterSvc::AddInternalParticle(const int number, const TString name, Vint dauglist){
		decayTree->AddInternalParticle(number, name, dauglist);
}

void DecayTreeFitterSvc::AddResonance(const int number, const TString name, Vint dauglist){
		decayTree->AddResonance(number, name, dauglist);
}

void DecayTreeFitterSvc::AddCMS(const int number, const TString name, const  HepLorentzVector trk, Vint dauglist){
		decayTree->AddCMS(number, name, trk, dauglist);
}

bool DecayTreeFitterSvc::Fit(){
		return decayTree->Fit();
}

double DecayTreeFitterSvc::chisq(){
		return decayTree->chisq();
}

double DecayTreeFitterSvc::decayLength(TString name){
		return decayTree->decayLength(name);
}

HepLorentzVector DecayTreeFitterSvc::p4(const int index){
		Eigen::Matrix<double, 1, 8> state_vec = decayTree->getStateVector(index);
		HepLorentzVector mom(state_vec(0), state_vec(1), state_vec(2), state_vec(3));
		return mom;
}


