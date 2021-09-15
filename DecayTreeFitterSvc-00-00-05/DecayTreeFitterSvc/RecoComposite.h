/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef RECO_COMPOSITE_H
#define RECO_COMPOSITE_H

#include "DecayTreeFitterSvc/ParticleBase.h"

namespace DecayTreeFitter {

		class RecoComposite : public ParticleBase {

				public:
						RecoComposite(const int number, const TString name);
						virtual ~RecoComposite(){};

				private:

		};
} // end namespace TreeFitter
#endif

