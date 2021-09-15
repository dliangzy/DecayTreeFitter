/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef RECO_TRACK_H
#define RECO_TRACK_H
#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/Constraint.h"
#include "DecayTreeFitterSvc/FitParams.h"
#include "DecayTreeFitterSvc/BField.h"
#include "TMath.h"

namespace DecayTreeFitter {
		 /** representation of all charged final states FIXME rename since this name is taken in tracking */
				class Constraint;
				class FitParams;
		class RecoTrack : public ParticleBase {
				public:
						enum TrackType {
								kNull,
								kMdcTrack,
								kWTrackParameter
						};
						RecoTrack(const int number, const TString name, const RecMdcKalTrack *trk);
						RecoTrack(const int number, const TString name, const WTrackParameter trk);

						virtual ~RecoTrack() {};

						void resetMeasurementPar();
						void resetMCovariance();

						virtual ErrCode initialParticle(const RecMdcKalTrack *trk);  //  override
						virtual ErrCode initialParticle( const  WTrackParameter trk); // override

						virtual const bool hasFinalPosition() const {return false;}
						virtual const bool hasDecayVertex() const {return false;}


						virtual Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> & getMeasurement() {return m_measurementPar; }
						virtual const Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> & getMeasurement() const {return m_measurementPar;}
						virtual Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getmCovariance() { return m_mCovariance; }
						virtual const Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getmCovariance() const { return m_mCovariance;}
						virtual Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getJacobian() { return m_Jacobian; }
						virtual const Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getJacobian() const { return m_Jacobian; }
					//	virtual void updateParticle();
						virtual ErrCode projectConstraint(const FitParams& fitparams, Constraint& cons) const;
						virtual ErrCode projectRecoConstraint(const FitParams& fitparams, Constraint& cons) const;

						virtual ErrCode initCovariance(FitParams& fitparams) const;


				private:

						const int m_dim;
						enum TrackType m_trktype;

						Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> m_measurementPar;
						Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> m_measurementParRef;

						Eigen::Matrix<double, 1, 7> m_WtrkPar;   // unique for charged track
						Eigen::Matrix<double, 1, 7> m_WtrkParRef;


						Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> m_mCovariance;
						Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> m_Jacobian;
		};

} // end namespace TreeFitter
#endif

