

#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/InternalParticle.h"


namespace DecayTreeFitter {

		

		InternalParticle::InternalParticle(const int number, const TString name):
		ParticleBase(number, name){
				m_ptype = kInternalParticle;
				m_hasEnergy = true;
		}

		InternalParticle::~InternalParticle(){
				for(auto daughter: m_daughterList){   /// ??? c++11
						delete daughter;
				}
		}

		ErrCode InternalParticle::projectConstraint(const FitParams& fitparams, Constraint& cons) const {
				ErrCode status;
				switch(cons.getConsType()){
						case Constraint::kMass:
								status |= ParticleBase::projectMassConstraint(fitparams, cons); break;
						case Constraint::kGeometric:
								status |= ParticleBase::projectGeoConstraint(fitparams, cons); break;
						case Constraint::kKinematic:
								status |= ParticleBase::projectKineConstraint(fitparams, cons); break;
						default: status |= ParticleBase::projectConstraint(fitparams, cons);
				}
				return status;
		}

		ErrCode InternalParticle::initCovariance(FitParams& fitparams) const {
				/* this is very sensitive and can heavily affect the efficiency of the fit */
				const int posindex = posIndex();
				if(posindex >= 0){
						for ( int i = 0; i < 4; i++ ) {
								fitparams.getCovariance()(posindex + i, posindex + i) = 1;
						}
				}


				const int momindex = momIndex();
				if ( momindex >= 0 ) {
						for(int i = 0; i < 4; i++){
								fitparams.getCovariance()(momindex + i, momindex + i) = 10;
						}
				} 
				return ErrCode(ErrCode::Status::success);

		}




		/*
		   void InternalParticle::initialParticle(const std:vector<int> daugList){


		   }

*/

} // end namespace TreeFitter
