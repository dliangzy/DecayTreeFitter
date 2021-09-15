/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef DEACY_TREE_H
#define DEACY_TREE_H

#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/RecoTrack.h"
#include "DecayTreeFitterSvc/RecoPhoton.h"
#include "DecayTreeFitterSvc/InternalParticle.h"
#include "DecayTreeFitterSvc/Resonance.h"
#include "DecayTreeFitterSvc/RootParticle.h"
#include "DecayTreeFitterSvc/Constraint.h"
#include "DecayTreeFitterSvc/KalmanCalculator.h"
#include "DecayTreeFitterSvc/FitParams.h"
#include "DecayTreeFitterSvc/RecoComposite.h"
#include "Eigen/Core"
#include <stdarg.h>
#include <vector>


namespace DecayTreeFitter {



		class DecayTree {
				public:

						typedef std::vector<ParticleBase*> VParticleBase;
						typedef std::vector<Constraint*> VConstraint;
						typedef std::vector<int>  Vint;

						DecayTree();
						~DecayTree();

						ErrCode initialize();
						ErrCode AddFinalState(const int number, const TString name, const RecMdcKalTrack *trk);
				//		ErrCode AddFinalState(const int number, const TString name, const WTrackParameter trk);  // could not be used.
						ErrCode AddFinalState(const int number, const TString name, const RecEmcShower *trk);
						ErrCode AddFinalState(const int number, const TString name, const HepLorentzVector trk) {
								/*  keep  */
						}; // for miss particle
						ErrCode AddCMS(const int number, const TString name, const HepLorentzVector trk, Vint dauglist);
						ErrCode AddInternalParticle(const int number, const TString name, Vint dauglist);
						ErrCode AddResonance(const int number, const TString name, Vint dauglist);
					//	ParticleBase* particlelist[30];
						VParticleBase particlelist;
						VParticleBase compositelist;
						ParticleBase* headparticle;
						ParticleBase* Head(ParticleBase* particle);
						bool printDecayTree(ParticleBase* particle, const int flag = 0);
						int Depth(ParticleBase* particle);
						bool Fit();
						/******************* Method *************************************/
						/* initialize the FitParams globalStateVector and global Covariance  */
						bool initialParams(ParticleBase *particle);
						bool CopyParams(ParticleBase *particle);
						bool initialCovariance(ParticleBase *particle);
						void preformDecayTree(ParticleBase *particle);  // using PreOrderTraverse method
						bool preformMomentum(ParticleBase *particle);  //  LRD OrderTraverse method
						bool preformPosition(ParticleBase *particle);	// using DLR OrderTraverse method
						void initialConstraint();

						double chisq() {return m_chisq;}
						double decayLength(TString name);

						const Eigen::Matrix<double, 1, 8> getStateVector(const int index);


						struct pointer_less {
								template< typename T >
										bool operator()( T const *lhs, T const *rhs ) const
										{ return * lhs < * rhs; }
						};

				private:
						//					VParticleBase particlelist;
						int m_dimState;
						Vint daughterList(int a, ...);
						FitParams *m_fitparams;
						Vint m_treeCount;
						VConstraint constraintlist;
						/* iteration */
						int m_niter;
						int NiterMax;
						double m_chisq;

		}; //end DecayTree
} // end namespace TreeFitter
#endif

