/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef ROOT_PARTICLE_H
#define ROOT_PARTICLE_H

#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/Constraint.h"
#include "DecayTreeFitterSvc/FitParams.h"

namespace DecayTreeFitter {

				class Constraint;
				class FitParams;
		class RootParticle : public ParticleBase {
				public:
						RootParticle(int number,  const TString name, const HepLorentzVector trk);
						virtual ~RootParticle();
						ErrCode resetMeasurementPar();
						ErrCode resetMCovariance();

						virtual ErrCode initialParticle(const HepLorentzVector trk);
						virtual const bool hasDecayVertex() const{
								return true;
						}
						/**  interaction point of e+ e-; read from VertexDBS  **/
						virtual Eigen::Matrix<double, 1, 3> & getRootVertex() { return m_beamSpot;};
						virtual const Eigen::Matrix<double, 1, 3> & getRootVertex() const { return m_beamSpot;};
						virtual Eigen::Matrix<double, 3, 3> & getRootVertexV() {return m_mCovariance;};
						virtual const Eigen::Matrix<double, 3, 3> & getRootVertexV() const { return m_mCovariance;};
						virtual Eigen::Matrix<double, 1, 4> & getRootMomentum(){return m_beamMom;};
						virtual const Eigen::Matrix<double, 1, 4> & getRootMomentum() const { return m_beamMom;};
						virtual Eigen::Matrix<double, 4, 4> & getRootMomentumV(){return m_MomCovariance;};
						virtual const Eigen::Matrix<double, 4, 4> & getRootMomentumV() const { return m_MomCovariance;};
						
						/* projection of beam spot and cms momentum */
						virtual ErrCode projectConstraint(const FitParams& fitparams, Constraint& cons) const;
						virtual ErrCode projectCMSConstraint(const FitParams& fitparams, Constraint& cons) const ;
						virtual ErrCode projectBeamSpotConstraint(const FitParams& fitparams, Constraint& cons) const ;

				private:

						const int m_dim;

						/*? uncertainty of the beam spot ?*/

						double m_espread;
						double m_collideangle;


						Eigen::Matrix<double, 1, 3> m_beamSpot;
						Eigen::Matrix<double, 1, 3> m_beamSpotRef;
						Eigen::Matrix<double, 1, 4> m_beamMom;
						Eigen::Matrix<double, 4, 4> m_MomCovariance;

						Eigen::Matrix<double, 3, 3> m_mCovariance;



		};
} // end namespace TreeFitter
#endif

