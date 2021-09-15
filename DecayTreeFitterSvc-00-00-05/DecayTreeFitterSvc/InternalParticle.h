/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef INTERNAL_PARTICLE_H
#define INTERNAL_PARTICLE_H

#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/Constraint.h"
#include "DecayTreeFitterSvc/FitParams.h"

namespace DecayTreeFitter {
		class Constraint;
		class FitParams;
		class InternalParticle : public ParticleBase {
				public:
						InternalParticle(const int number, const TString name);
						virtual ~InternalParticle();

				//		virtual void preformParticle(const std::vector<int> daugList);

						virtual ErrCode projectConstraint(const FitParams& fitparams, Constraint& cons) const ;  
						virtual ErrCode initCovariance(FitParams& fitparams) const;


						virtual const  bool isFinalState() const {return false;};
						virtual const  bool hasDecayVertex() const {return true;};
						virtual bool hasEnergy() const {return m_hasEnergy;};
						virtual void setMassConstraint() { m_hasEnergy = false;}
						virtual void setConstraintType(const int c){ 
								m_constraintlist.push_back(c);
								if(Constraint::ConstraintType(c) == Constraint::kMass){
										setMassConstraint();
								}
						}






						private:

						bool m_hasEnergy;

						/* internal particle don't have measurable parameters*
						 * Only observable*/


		};
} // end namespace TreeFitter
#endif

