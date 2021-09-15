/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef RECO_PHOTON_H
#define RECO_PHOTON_H
#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/Constraint.h"
#include "DecayTreeFitterSvc/FitParams.h"

namespace DecayTreeFitter {
		class Constraint;
		class FitParams;
		class RecoPhoton : public ParticleBase {
				public:
						RecoPhoton(const int number, const TString name, const RecEmcShower *trk);
						virtual ~RecoPhoton() {};

						ErrCode resetMeasurementPar();
						ErrCode resetMCovariance();

						virtual ErrCode initialParticle(const RecEmcShower *trk);  //  override

						virtual const bool hasFinalPosition() const {return true;}
						virtual const bool hasDecayVertex() const {return false;}

						virtual ErrCode projectConstraint(const FitParams& fitparams, Constraint& cons) const;
						virtual ErrCode projectRecoConstraint(const FitParams& fitparams, Constraint& cons) const;

						virtual Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> & getMeasurement() {return m_measurementPar; }
						virtual const Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> & getMeasurement() const {return m_measurementPar;}
						virtual Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getmCovariance() { return m_mCovariance; }
						virtual const Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getmCovariance() const { return m_mCovariance;}

						virtual ErrCode initCovariance(FitParams& fitparams) const;



				private:

						const int m_dim;
						int m_i1, m_i2, m_i3;
						Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> m_measurementPar;
						Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> m_measurementParRef;
						Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> m_mCovariance;
		};
} // end namespace TreeFitter
#endif

