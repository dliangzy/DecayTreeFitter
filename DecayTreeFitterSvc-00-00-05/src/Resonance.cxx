/*****************************************************************************\
 *  BOSS (BES Offline Software System)                                       *
 *       Filename:  Resonance.cxx											 *
 *                                                                           *
 *    Description:  Define a resonance particle with 0 decay length			 *
 *                                                                           *
 *        Version:  1.0                                                      *
 *        Created:  08/21/2021 03:14:05 PM                                   *
 *       Revision:  none                                                     *
 *       Compiler:  gcc                                                      *
 *                                                                           *
 *         Author:  Liang Liu (USTC), <liangzy@mail.ustc.edu.cn>             *
 *   Organization:  BESIII Collaboration                                     *
 *        License:  GNU Lesser General Public License 3.0, see LICENSE.md.   *
\*****************************************************************************/



#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/Resonance.h"



namespace DecayTreeFitter {
		Resonance::Resonance(const int number, const TString name):
				ParticleBase(number, name){
						m_ptype = kResonance;
						m_hasEnergy = true;
				}
		Resonance::~Resonance(){
				for(auto daughter: m_daughterList){
						delete daughter;
				}
		}

		ErrCode Resonance::projectConstraint(const FitParams& fitparams, Constraint& cons) const {
				ErrCode status;
				switch(cons.getConsType()){
						case Constraint::kMass:
								status |= ParticleBase::projectMassConstraint(fitparams, cons); break;
						case Constraint::kKinematic:
								status |= ParticleBase::projectKineConstraint(fitparams, cons); break;
						default: status |= ParticleBase::projectConstraint(fitparams, cons);
				}
				return status;
		}
		const int Resonance::posIndex() const {
				if(m_ptype == kResonance){
						return getMother()->posIndex();
				}
		}
		
		ErrCode Resonance::initCovariance(FitParams& fitparams) const {
				const int momindex = momIndex();
				if ( momindex >= 0 ) {
						for(int i = 0; i < 4; i++){
								fitparams.getCovariance()(momindex + i, momindex + i) = 10;
						}
				}
				return ErrCode(ErrCode::Status::success);
		}
}		/* -----  end of namespace DecayTreeFitter  ----- */

