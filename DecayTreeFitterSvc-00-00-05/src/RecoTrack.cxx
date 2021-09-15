#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/RecoTrack.h"


namespace DecayTreeFitter {


		RecoTrack::RecoTrack(const int number, const TString name, const RecMdcKalTrack *trk):
				ParticleBase(number,  name),
				m_dim(5),
				m_trktype(kMdcTrack),
				m_measurementPar(5),
				m_measurementParRef(5)
		{
				resetMeasurementPar();
				resetMCovariance();
				m_Jacobian = Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7>::Zero(5, 6);
				initialParticle(trk);
		}

		RecoTrack::RecoTrack(const int number, const TString name, const WTrackParameter trk):
				ParticleBase(number,  name),
				m_dim(7),
				m_trktype(kWTrackParameter),
				m_measurementPar(7),
				m_measurementParRef(7)
		{
				resetMeasurementPar();
				resetMCovariance();
				m_Jacobian = Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7>::Zero(7, 7);
				initialParticle(trk);
		}



		void RecoTrack::resetMeasurementPar(){
				m_measurementPar = Eigen::Matrix<double,1, Dynamic,  1, 1, 7>::Zero(1, m_dim);
				m_measurementParRef = Eigen::Matrix<double,1, Dynamic,  1, 1, 7>::Zero(1, m_dim);
				m_WtrkPar = Eigen::Matrix<double, 1, 7>::Zero();
				m_WtrkParRef = Eigen::Matrix<double, 1, 7>::Zero();
		}
		void RecoTrack::resetMCovariance(){
				m_mCovariance = Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7>::Zero(m_dim, m_dim);
		}


		ErrCode RecoTrack::initialParticle(const RecMdcKalTrack *trk){
				if(fabs(getpdgId()) == 2212 || fabs(getpdgId()) == 11 ||  fabs(getpdgId()) == 321 || fabs(getpdgId()) == 211 || fabs(getpdgId()) == 13){
						m_ptype = kChargeTrack;
						m_bfield = 1.0;
						if(fabs(getpdgId()) == 2212){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::proton);
						}
						else if(fabs(getpdgId()) == 11){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::electron);
						}
						else if(fabs(getpdgId()) == 321){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::kaon);
						}
						else if(fabs(getpdgId()) == 211){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::pion);
						}
						else if(fabs(getpdgId()) == 13){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::muon);
						}
						else {
								cout << "DecayTreeFitterSvc: Wrong Charge track pid!" << endl;
								exit(1);
						}
						m_debug = 5;
						if(m_debug < 3) {
								printParticleName(getpdgId());
						}
						m_debug = 5;
						/* get helix and covariance error matrix */
						//	double d0 = trk.helix(0);
						//	double phi0 = trk.helix(1);
						//	double omega = trk.helix(2);
						//	double z0 = trk.helix(3);
						//	double tanlam = trk.helix(4);
						const CLHEP::HepVector trkHelix = trk->getZHelix();
						for(int i  = 0; i < m_dim; i++){
								m_measurementPar(i) = trkHelix[i]; //  No reference parameters
						}
						/* error matrix */
						const CLHEP::HepSymMatrix trkHelixErr = trk->getZError();


						for( int irow = 0; irow < m_dim; irow++ )
								for( int icol = 0; icol < m_dim; icol++ ){
										m_mCovariance(irow, icol) = trkHelixErr(irow + 1, icol + 1);
								}
						/* get x y z position */
						/* keep in mind.  Don't have vertex infomation  */
						/* maybe this point could be a set of initial values in vertex fit */
						const HepPoint3D  trkpoca = trk->poca();
						/* four momenta and tree momenta */
						//const Hep3Vector trkp3mom = trk->p3();
						const HepLorentzVector trkp4mom = trk->p4(getpdgMass());

						m_WtrkPar(0) = trkp4mom.px();
						m_WtrkPar(1) = trkp4mom.py();
						m_WtrkPar(2) = trkp4mom.pz();
						m_WtrkPar(3) = trkp4mom.e();
						m_WtrkPar(4) = trkpoca.x();
						m_WtrkPar(5) = trkpoca.y();
						m_WtrkPar(6) = trkpoca.z();

						cout << getName() << endl;
						cout << getpdgId() << endl;
						m_commonStateVector(0) = trkp4mom.px();
						m_commonStateVector(1) = trkp4mom.py();
						m_commonStateVector(2) = trkp4mom.pz();
						m_commonStateVector(3) = trkp4mom.e();
						m_commonStateVector(4) = trkpoca.x();
						m_commonStateVector(5) = trkpoca.y();
						m_commonStateVector(6) = trkpoca.z();
						m_commonStateVector(7) = 0;  //  final state don't need tau.
						//		projectRecoConstraint(trk);
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
		}

		ErrCode RecoTrack::initialParticle(const WTrackParameter trk){
				if(fabs(getpdgId()) == 2212 || fabs(getpdgId()) == 11 ||  fabs(getpdgId()) == 321 || fabs(getpdgId()) == 211 || fabs(getpdgId()) == 13){
						m_ptype = kChargeTrack;
						m_bfield = 1.0;
						if(fabs(getpdgId()) == 2212){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::proton);
						}
						else if(fabs(getpdgId()) == 11){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::electron);
						}
						else if(fabs(getpdgId()) == 321){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::kaon);
						}
						else if(fabs(getpdgId()) == 211){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::pion);
						}
						else if(fabs(getpdgId()) == 13){
								RecMdcKalTrack::setPidType  (RecMdcKalTrack::muon);
						}
						else {
								cout << "DecayTreeFitterSvc: Wrong Charge track pid!" << endl;
								exit(1);
						}
						m_debug = 5;
						if(m_debug < 3) {
								printParticleName(getpdgId());
						}
						m_debug = 5;
						/* get helix and covariance error matrix */
						//	double d0 = trk.helix(0);
						//	double phi0 = trk.helix(1);
						//	double omega = trk.helix(2);
						//	double z0 = trk.helix(3);
						//	double tanlam = trk.helix(4);
						//	const CLHEP::HepVector trkHelix = trk->getZHelix();
						/* error matrix */
						const CLHEP::HepSymMatrix trkHelixErr = trk.Ew();

						for( int irow = 0; irow < m_dim; irow++ )
								for( int icol = 0; icol < m_dim; icol++ ){
										m_mCovariance(irow, icol) = trkHelixErr(irow + 1, icol + 1);
								}
						/* get x y z position */
						/* keep in mind.  Don't have vertex infomation  */
						/* maybe this point could be a set of initial values in vertex fit */
						const HepPoint3D  trkpoca = trk.x();
						/* four momenta and tree momenta */
						//const Hep3Vector trkp3mom = trk->p3();
						const HepLorentzVector trkp4mom = trk.p();

						m_WtrkPar(0) = trkp4mom.px();
						m_WtrkPar(1) = trkp4mom.py();
						m_WtrkPar(2) = trkp4mom.pz();
						m_WtrkPar(3) = trkp4mom.e();
						m_WtrkPar(4) = trkpoca.x();
						m_WtrkPar(5) = trkpoca.y();
						m_WtrkPar(6) = trkpoca.z();


						m_measurementPar(0) = trkp4mom.px();
						m_measurementPar(1) = trkp4mom.py();
						m_measurementPar(2) = trkp4mom.pz();
						m_measurementPar(3) = trkp4mom.e();
						m_measurementPar(4) = trkpoca.x();
						m_measurementPar(5) = trkpoca.y();
						m_measurementPar(6) = trkpoca.z();

						m_commonStateVector(0) = trkp4mom.px();
						m_commonStateVector(1) = trkp4mom.py();
						m_commonStateVector(2) = trkp4mom.pz();
						m_commonStateVector(3) = trkp4mom.e();
						m_commonStateVector(4) = trkpoca.x();
						m_commonStateVector(5) = trkpoca.y();
						m_commonStateVector(6) = trkpoca.z();
						m_commonStateVector(7) = 0;  //  final state don't need tau.

						//		projectRecoConstraint(trk);
						/* print the covariance matrix and parameters */
						m_debug = 0;
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
		}


				
		ErrCode RecoTrack::initCovariance(FitParams& fitparams) const {
				const int posindexmother = getMother()->posIndex();
				const int momindex = momIndex();

				Eigen::Matrix<double, 1, 6> positionAndMom = Eigen::Matrix<double, 1, 6>::Zero(1, 6);
				positionAndMom.segment(0, 3) = fitparams.getStateVector().segment(posindexmother, 3);
				positionAndMom.segment(3, 3) = fitparams.getStateVector().segment(momindex, 3);
				
				HelixUtils helix(positionAndMom(0),
								positionAndMom(1),
								positionAndMom(2),
								positionAndMom(3),
								positionAndMom(4),
								positionAndMom(5),
								m_bfield,
								getcharge());

				Eigen::Matrix<double, 8, 8>  errMatrix = helix.getJacobian().transpose() * m_mCovariance *helix.getJacobian();
				for (int row = 0; row < 3; ++row) {
						fitparams.getCovariance()(momindex + row, momindex + row) = 1000 * errMatrix(row, row);
				}
				return ErrCode(ErrCode::Status::success);
		}


		

		ErrCode RecoTrack::projectConstraint(const FitParams& fitparams, Constraint& cons) const{
				ErrCode status;
				switch(cons.getConsType()){
						case Constraint::kTrack: 
								status |= projectRecoConstraint(fitparams, cons); break;
						default:
								status |= ParticleBase::projectConstraint(fitparams, cons);
				}
				return status;
		} 

		ErrCode RecoTrack::projectRecoConstraint(const FitParams& fitparams, Constraint& cons) const {
				const int posindexmother = getMother()->posIndex();
				const int momindex = momIndex();

				Eigen::Matrix<double, 1, 6> positionAndMom = Eigen::Matrix<double, 1, 6>::Zero(1, 6);
				positionAndMom.segment(0, 3) = fitparams.getStateVector().segment(posindexmother, 3);
				positionAndMom.segment(3, 3) = fitparams.getStateVector().segment(momindex, 3);
				HelixUtils helix(positionAndMom(0),
								positionAndMom(1),
								positionAndMom(2),
								positionAndMom(3),
								positionAndMom(4),
								positionAndMom(5),
								m_bfield,
								getcharge());

				cons.getJacobian().block<5, 3>(0, momindex) = -1.0 * helix.getJacobian().block<5, 3>(0, MOM_IDX);
				cons.getJacobian().block<5, 3>(0, posindexmother) = -1.0* helix.getJacobian().block<5, 3>(0, POSI_IDX);
				for(int i = 0; i < 5; i++){
			/*			if(i == 1){   // account for periodic boundary in phi residual
								if(helix.getMeasurement()(i) < 0){
										helix.getMeasurement()(i) += 2. * TMath::Pi();
								}
								helix.getMeasurement()(i) -=  TMath::Pi()/2.;
								if(helix.getMeasurement()(i) < 0){
										helix.getMeasurement()(i) += 2. * TMath::Pi();
								}
								double phiResidual = m_measurementPar(i) - helix.getMeasurement()(i);
								cons.getResidualM()(i) = phiResidual;
						}
						else {
								cons.getResidualM()(i) = m_measurementPar(i) - helix.getMeasurement()(i);
						}*/
						cons.getResidualM()(i) = m_measurementPar(i) - helix.getMeasurement()(i);
				}
				cons.getV().block<5, 5>(0, 0) = getmCovariance().block<5, 5>(0, 0);
				return ErrCode(ErrCode::Status::success);
		}
} // end namespace TreeFitter
