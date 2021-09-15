/*****************************************************************************\
 *  BOSS (BES Offline Software System)                                       *
 *       Filename:  Resonance.h												 *
 *                                                                           *
 *    Description:  Define a resonance particle with 0 decay length          *
 *                                                                           *
 *        Version:  1.0                                                      *
 *        Created:  08/21/2021 03:21:30 PM                                   *
 *       Revision:  none                                                     *
 *       Compiler:  gcc                                                      *
 *                                                                           *
 *         Author:  Liang Liu (USTC), <liangzy@mail.ustc.edu.cn>             *
 *   Organization:  BESIII Collaboration                                     *
 *        License:  GNU Lesser General Public License 3.0, see LICENSE.md.   *
\*****************************************************************************/


#ifndef  RESONANCE_H
#define  RESONANCE_H

#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/Constraint.h"
#include "DecayTreeFitterSvc/FitParams.h"

namespace DecayTreeFitter {
		class Constraint;
		class FitParams;
		/*
		 * =====================================================================================
		 *        Class:  Resonance
		 *  Description:  
		 * =====================================================================================
		 */
		class Resonance : public ParticleBase
		{
				public:
						/* ====================  LIFECYCLE     ======================================= */
						/* constructor */
						Resonance (const int number, const TString name);


						virtual ~Resonance();

						virtual ErrCode projectConstraint(const FitParams& fitparams, Constraint& cons) const;
						virtual const int posIndex() const;

						virtual const  bool isFinalState() const {return false;};
						virtual const  bool hasDecayVertex() const {return true;};
						virtual bool hasEnergy() const {return m_hasEnergy;};
						virtual void setMassConstraint() { m_hasEnergy = false;}
						virtual ErrCode initCovariance(FitParams& fitparams) const;
						virtual void setConstraintType(const int c){ 
								m_constraintlist.push_back(c);
								if(Constraint::ConstraintType(c) == Constraint::kMass){
										setMassConstraint();
								}
						}


				protected:
						/* ====================  METHODS       ======================================= */

						/* ====================  DATA MEMBERS  ======================================= */

				private:
						/* ====================  METHODS       ======================================= */

						/* ====================  DATA MEMBERS  ======================================= */
						bool m_hasEnergy;

		}; /* -----  end of class Resonance  ----- */
}		/* -----  end of namespace DecayTreeFitter  ----- */

#endif   /* ----- #ifndef Resonance_INC  ----- */
