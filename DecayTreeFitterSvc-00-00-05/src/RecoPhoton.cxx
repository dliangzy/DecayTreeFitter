#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/RecoPhoton.h"


namespace DecayTreeFitter {
		
		RecoPhoton::RecoPhoton(const int number, const TString name, const RecEmcShower *trk):
				ParticleBase(number,  name),
				m_dim(4)
		{
				resetMeasurementPar();
				resetMCovariance();
				initialParticle(trk);
		}


		ErrCode RecoPhoton::resetMeasurementPar(){
				m_measurementPar = Eigen::Matrix<double, 1, Dynamic, 1, 1, 7>::Zero(1, m_dim);
				m_measurementParRef = Eigen::Matrix<double, 1, Dynamic, 1, 1, 7>::Zero(1, m_dim);
		}
		ErrCode RecoPhoton::resetMCovariance(){
				m_mCovariance = Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7>::Zero(m_dim, m_dim);
		}

		ErrCode RecoPhoton::initialParticle(const RecEmcShower *trk){
				if(fabs(getpdgId()) == 22){
						m_ptype = kPhoton;
						double x = trk->x();
						double y = trk->y();
						double z = trk->z();
						double dx = trk->dx();
						double dy = trk->dy();
						double dz = trk->dz();
						double theta = trk->theta();
						double phi = trk->phi();
						double energy = trk->energy();
						double dE = trk->dE();
						m_measurementPar(0) = x;
						m_measurementPar(1) = y;
						m_measurementPar(2) = z;
						m_measurementPar(3) = energy;
						const HepLorentzVector p4(energy*sin(theta) * cos(phi), energy*sin(theta)*sin(phi),
										energy*cos(theta), energy);
						const HepPoint3D posi(x, y, z);
						m_commonStateVector(0) = p4.px();
						m_commonStateVector(1) = p4.py();
						m_commonStateVector(2) = p4.pz();
						m_commonStateVector(3) = p4.e();
						m_commonStateVector(4) = x;
						m_commonStateVector(5) = y;
						m_commonStateVector(6) = z;
						m_commonStateVector(7) = 0;   // eliminated
						CLHEP::HepSymMatrix xyz_err = trk->errorMatrix();
						for( int irow = 0; irow < m_dim-1; irow++ )
								for( int icol = 0; icol < m_dim-1; icol++ ){
										m_mCovariance(irow, icol) = xyz_err(irow + 1, icol + 1);
								}
						m_mCovariance(3, 3) = dE*dE;

						Eigen::Matrix<double, 1, 3> p_vec = Eigen::Matrix<double, 1, 3>::Zero();
						p_vec(0) = p4.px();
						p_vec(1) = p4.py();
						p_vec(2) = p4.pz();

						if ((std::abs(p_vec(0)) >= std::abs(p_vec(1))) && (std::abs(p_vec(0)) >= std::abs(p_vec(2)))) {
								m_i1 = 0; m_i2 = 1; m_i3 = 2;
						} else if ((std::abs(p_vec(1)) >= std::abs(p_vec(0))) && (std::abs(p_vec(1)) >= std::abs(p_vec(2)))) {
								m_i1 = 1; m_i2 = 0; m_i3 = 2;
						} else if ((std::abs(p_vec(2)) >= std::abs(p_vec(1))) && (std::abs(p_vec(2)) >= std::abs(p_vec(0)))) {
								m_i1 = 2; m_i2 = 1; m_i3 = 0;
						} else {
								cout << "Could not estimate highest momentum for photon constraint. Aborting this fit.\n px: "
												<< p_vec(0) << " py: " << p_vec(1) << " pz: " << p_vec(2) << " calculated from Ec: " << m_measurementPar << endl;
								return ErrCode(ErrCode::Status::photondimerror);
						}

						/* print the covariance matrix and parameters */
						m_debug = 5;
						if(m_debug < 3) {
								cout << "m_par : " << endl;
								cout << m_measurementPar  << endl;
								cout << "m_state : " << endl;
								cout << m_commonStateVector  << endl;
								//	cout << "m_covC : " << endl;
								//	cout << m_covC  << endl;
								cout << "m_mCovariance : " << endl;
								cout << m_mCovariance  << endl;
								//	cout << "m_Jacobian : " << endl;
								//	cout << m_Jacobian  << endl;
						}
						m_debug =5;
				}
				return ErrCode(ErrCode::Status::success);
		}

		ErrCode RecoPhoton::initCovariance(FitParams& fitparams) const {
				const int momindex  = momIndex();
				const int posindexmother  = getMother()->posIndex();

				const double factorE = 1000 * m_mCovariance(3, 3);
				const double factorX = 1000;

				fitparams.getCovariance().block<4, 4>(momindex, momindex) =
						Eigen::Matrix<double, 4, 4>::Identity(4, 4) * factorE;
				fitparams.getCovariance().block<3, 3>(posindexmother, posindexmother) =
						Eigen::Matrix<double, 3, 3>::Identity(3, 3) * factorX;
				return ErrCode(ErrCode::Status::success);
		}

		ErrCode RecoPhoton::projectConstraint(const FitParams& fitparams, Constraint& cons) const{
				ErrCode status;
				switch(cons.getConsType()){
						case Constraint::kPhoton: 
								status |= projectRecoConstraint(fitparams, cons); break;
						default:
								status |= ParticleBase::projectConstraint(fitparams, cons);
				}
				return status;
		} 

		ErrCode RecoPhoton::projectRecoConstraint(const FitParams& fitparams, Constraint& cons) const {
				const int momindex  = momIndex() ;
				const int posindexmother  = getMother()->posIndex();
				const int posindex  = posIndex();
				/**
				 * m : decay vertex mother
				 * p : momentum photon
				 * c : position cluster
				 * so:
				 * m + p = c
				 * thus (tau converts p to the correct units):
				 * 0 = c - m - tau * p
				 * we have 3 geometric equations and eliminate tau using the dimension with the highest momentum
				 * (because we have to divide by that momentum)
				 * only downside is we have to figure out which dimension this is
				 * the 4th equation is the energy which we keep as:
				 * 0 = E - |p|
				 * just to be sure, essentially this is always zero because p is build from E
				 * */

				const Eigen::Matrix<double, 1, 3> x_vertex = fitparams.getStateVector().segment(posindexmother, 3);
				const Eigen::Matrix<double, 1, 3> p_vec = fitparams.getStateVector().segment(momindex, 3);

    			/* p_vec[m_i1] must not be 0 */
				if (0 == p_vec[m_i1]) { return ErrCode(ErrCode::photondimerror); }

				//  m_measurementPar(0) 
				//
				const double elim = (m_measurementPar[m_i1] - x_vertex[m_i1]) / p_vec[m_i1];
				const double mom = p_vec.norm();

				cons.getResidualM()(0) = m_measurementPar[m_i2] - x_vertex[m_i2] - p_vec[m_i2] * elim;
				cons.getResidualM()(1) = m_measurementPar[m_i3] - x_vertex[m_i3] - p_vec[m_i3] * elim;
				cons.getResidualM()(2) = m_measurementPar[3] - mom;
				// dr'/dm | m:={xc,yc,zc,Ec} the measured quantities
				Eigen::Matrix<double, 3, 4> P = Eigen::Matrix<double, 3, 4>::Zero(3, 4);
				// deriving by the cluster pars
				P(0, m_i2) = 1;
				P(0, m_i1) = - p_vec[m_i2] / p_vec[m_i1];

				P(1, m_i3) = 1;
				P(1, m_i1) = - p_vec[m_i3] / p_vec[m_i1];
				P(2, 3) = 1; // dE/dEc
				cons.getV().block<3, 3>(0, 0) = (P * m_mCovariance.selfadjointView<Eigen::Lower>() * P.transpose()).block<3, 3>(0, 0);


				// dr'/dm  | m:={x,y,z,px,py,pz,E}
				// x := x_vertex (decay vertex of mother)
				cons.getJacobian()(0, posindexmother + m_i1) =  p_vec[m_i2] / p_vec[m_i1];
				cons.getJacobian()(0, posindexmother + m_i2) = -1.0;
				cons.getJacobian()(0, posindexmother + m_i3) = 0;
				cons.getJacobian()(0, posindex + m_i1) = -p_vec[m_i2] / p_vec[m_i1];
				cons.getJacobian()(0, posindex + m_i2) = 1;
				cons.getJacobian()(0, posindex + m_i3) = 0;

				cons.getJacobian()(1, posindexmother + m_i1) =  p_vec[m_i3] / p_vec[m_i1];
				cons.getJacobian()(1, posindexmother + m_i2) = 0;
				cons.getJacobian()(1, posindexmother + m_i3) = -1.0;
				cons.getJacobian()(1, posindex + m_i1) = -p_vec[m_i3] / p_vec[m_i1];
				cons.getJacobian()(1, posindex + m_i2) = 0;
				cons.getJacobian()(1, posindex + m_i3) = 1;

				// elim already devided by p_vec[m_i1]
				cons.getJacobian()(0, momindex + m_i1) = p_vec[m_i2] * elim / p_vec[m_i1];
				cons.getJacobian()(0, momindex + m_i2) = -1. * elim;
				cons.getJacobian()(0, momindex + m_i3) = 0;

				cons.getJacobian()(1, momindex + m_i1) = p_vec[m_i3] * elim / p_vec[m_i1];
				cons.getJacobian()(1, momindex + m_i2) = 0;
				cons.getJacobian()(1, momindex + m_i3) = -1. * elim;

				cons.getJacobian()(2, momindex + m_i1) = -1. * p_vec[m_i1] / mom;
				cons.getJacobian()(2, momindex + m_i2) = -1. * p_vec[m_i2] / mom;
				cons.getJacobian()(2, momindex + m_i3) = -1. * p_vec[m_i3] / mom;
	//			cons.getJacobian()(2, momindex + 3) =  1;
				// the photon does not store an energy in the state vector
				// so no p.getH()(2, momindex + 3) here
				return ErrCode(ErrCode::Status::success);

		}
} // end namespace TreeFitter
