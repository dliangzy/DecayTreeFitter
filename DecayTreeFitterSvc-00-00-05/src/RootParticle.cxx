#include "DecayTreeFitterSvc/RootParticle.h"

namespace DecayTreeFitter {
		RootParticle::RootParticle(int number,  const TString name, const HepLorentzVector trk):
				ParticleBase(number, name), 
				m_dim(3)
		{
				resetMCovariance();
				resetMeasurementPar();
				initialParticle(trk);
		}

		RootParticle::~RootParticle(){

				for(auto daughter: m_daughterList){   /// ??? c++11
						delete daughter;
				}


		}

		ErrCode RootParticle::resetMeasurementPar(){
				m_beamSpot = Eigen::Matrix<double, 1, 3>::Zero();
				m_beamSpotRef = Eigen::Matrix<double, 1, 3>::Zero();
		}
		ErrCode RootParticle::resetMCovariance(){
				m_mCovariance = Eigen::Matrix<double, 3, 3>::Zero();
				m_MomCovariance = Eigen::Matrix<double, 4, 4>::Zero();
		}

		ErrCode RootParticle::initialParticle(const HepLorentzVector trk){
				m_ptype = kHead;
				m_espread = 0.0009;
				m_collideangle = 11e-3;

				double px = trk.px();
				double py = trk.py();
				double pz = trk.pz();
				double energy = trk.e();

				IVertexDbSvc* vtxsvc;
				Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
				if(!vtxsvc->isVertexValid()){
						cout << "DecayTreeFitterSvc:: Could not load opne VertexDbSvc" << endl;
						exit(1);
				}
				double* vv = vtxsvc->PrimaryVertex();
				double*  dbv = vtxsvc->SigmaPrimaryVertex();
				double x = vv[0];
				double y = vv[1];
				double z = vv[2];
				m_beamSpot(0) = x;
				m_beamSpot(1) = y;
				m_beamSpot(2) = z;

				m_beamMom(0) = px;
				m_beamMom(1) = py;
				m_beamMom(2) = pz;
				m_beamMom(3) = energy;

				m_mCovariance(0, 0) = dbv[0] * dbv[0];
				m_mCovariance(1, 1) = dbv[1] * dbv[1];
				m_mCovariance(2, 2) = dbv[2] * dbv[2];

				m_commonStateVector(0) = px;
				m_commonStateVector(1) = py;
				m_commonStateVector(2) = pz;
				m_commonStateVector(3) = energy;
				m_commonStateVector(4) = x;
				m_commonStateVector(5) = y;
				m_commonStateVector(6) = z;
				m_commonStateVector(7) = 0;  	// tau = 0;

				if(getpdgId() == 443 || getpdgId() == 100443){
						m_MomCovariance(0, 0) = 2*m_espread*m_espread*sin(m_collideangle)*sin(m_collideangle);
						m_MomCovariance(0, 3) = 2*m_espread*m_espread*sin(m_collideangle);
						m_MomCovariance(3, 0) = 2*m_espread*m_espread*sin(m_collideangle);
						m_MomCovariance(3, 3) = 2*m_espread*m_espread;
						m_MomCovariance(1, 1) = 0.001*m_espread*m_espread;
						m_MomCovariance(2, 2) = 0.001*m_espread*m_espread;
				}
		}

		ErrCode RootParticle::projectConstraint(const FitParams& fitparams, Constraint& cons) const{
				ErrCode status;
				switch(cons.getConsType()){
						case Constraint::kBeamSpot: 
								status |= projectBeamSpotConstraint(fitparams, cons); break;
						case Constraint::kCMS:
								status |= projectCMSConstraint(fitparams, cons); break;
						default:
								status |= ParticleBase::projectConstraint(fitparams, cons);
				}
				return status;
		} 

		ErrCode RootParticle::projectCMSConstraint(const FitParams& fitparams, Constraint& cons) const {
				const int momindex = momIndex();
				const Eigen::Matrix<double, 1, 4> p4_vec = fitparams.getStateVector().segment(momindex, 4);
				for(int imom = 0; imom < 4; imom++){
						cons.getResidualM()(imom) = getRootMomentum()(imom) - p4_vec(imom);
						cons.getJacobian()(imom, momindex + imom) = -1;
				}
				cons.getV().block<4, 4>(0, 0) = getRootMomentumV().block<4, 4>(0, 0);
				return ErrCode(ErrCode::Status::success);
		}
		ErrCode RootParticle::projectBeamSpotConstraint(const FitParams& fitparams, Constraint& cons) const {
				const int posindex = posIndex();
				const Eigen::Matrix<double, 1, 3> pos_vec = fitparams.getStateVector().segment(posindex, 3);
				for(int ipos = 0; ipos < 3; ipos++){
						cons.getResidualM()(ipos) = getRootVertex()(ipos) - pos_vec(ipos);
						cons.getJacobian()(ipos, posindex + ipos) = -1;
				}
				cons.getV().block<3, 3>(0, 0) = getRootVertexV().block<3, 3>(0, 0);
				return ErrCode(ErrCode::Status::success);
		}
}


