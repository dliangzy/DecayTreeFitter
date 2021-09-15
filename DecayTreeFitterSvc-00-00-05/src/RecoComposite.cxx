#include "DecayTreeFitterSvc/RecoComposite.h"

namespace DecayTreeFitter {
		RecoComposite::RecoComposite(const int number, const TString name)
		{
				ParticleBase::Clear();
				m_ptype = kComposite;
				m_index = number;
				m_name = name;
		}
}// end namespace TreeFitter
