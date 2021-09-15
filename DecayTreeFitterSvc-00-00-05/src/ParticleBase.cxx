
#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/HelixUtils.h"
#include "DecayTreeFitterSvc/ErrCode.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Geometry/Point3D.h"
#include "DecayTreeFitterSvc/FitParams.h"
#include "DecayTreeFitterSvc/Constraint.h"
#include <fstream> 
#include <iostream>
#include <cstring>
#include <stdarg.h>
#include <string>
namespace DecayTreeFitter {

		ParticleBase::ParticleBase(){ Clear();}
		ParticleBase::ParticleBase(const int number,  const TString name){
				initialParticle(number,  name);
		}

		ParticleBase::~ParticleBase(){
				for(auto daughter: m_daughterList){   /// ??? c++11
						delete daughter;
				}
		}

		ErrCode ParticleBase::initialParticle(const int number,  const TString name){
				Clear();
				setPdgValue(name);
				m_index = number;
				return ErrCode(ErrCode::Status::success);
		}

		
		ErrCode ParticleBase::initCovariance(FitParams& fitparams) const {
				/* this is very sensitive and can heavily affect the efficiency of the fit */
				const int posindex = posIndex();
				if(posindex >= 0){
						for ( int i = 0; i < 4; i++ ) {
								fitparams.getCovariance()(posindex + i, posindex + i) = 1000;
						}
				}
				const int momindex = momIndex();
				if ( momindex >= 0 ) {
						for(int i = 0; i < 4; i++){
								fitparams.getCovariance()(momindex + i, momindex + i) = 1000;
						}
				} 
				return ErrCode(ErrCode::Status::success);
		}

		ErrCode ParticleBase::projectConstraint(const FitParams& fitparams, Constraint& cons) const {
				switch(cons.getConsType()){
						case Constraint::kMass: 		projectMassConstraint(fitparams, cons); break;
						case Constraint::kGeometric: 	projectGeoConstraint(fitparams, cons); break;
						case Constraint::kVertex: 		cout << "1" << endl; break;
						case Constraint::kFourMomentum: cout << "1" << endl; break;
						case Constraint::kKinematic: 	projectKineConstraint(fitparams, cons); break;
						case Constraint::kMassNeutral: 	cout << "1" << endl; break;
						case Constraint::kPhoton: 		cout << "1" << endl; break;
						case Constraint::kTrack: 		cout << "1" << endl; break;
						default: break;
				}
		}


		ErrCode ParticleBase::projectMassConstraint(const FitParams& fitparams, Constraint& cons) const{
				if(isFinalState()){
						const double mass = getpdgMass();
						const double mass2 = mass*mass;
						const int  momindex = momIndex();
						const double px = fitparams.getStateVector()(momindex +0);
						const double py = fitparams.getStateVector()(momindex +1);
						const double pz = fitparams.getStateVector()(momindex +2);
						const double E  = fitparams.getStateVector()(momindex +3);
						/** be aware that the signs here are important
						 * E-|p|-m extracts a negative mass and messes with the momentum !
						 * */
						cons.getResidualM()(0) = mass2 - E * E + px * px + py * py + pz * pz;
						cons.getJacobian()(0, momindex + 0) = 2.0 * px;
						cons.getJacobian()(0, momindex + 1) = 2.0 * py;
						cons.getJacobian()(0, momindex + 2) = 2.0 * pz;
						cons.getJacobian()(0, momindex + 3) = -2.0 * E;
				}
				else{
						const double mass = getpdgMass();
						const double mass2  = mass*mass;
						double px = 0;
						double py = 0;
						double pz = 0;
						double E  = 0;

						for(int i = 0; i < daughterCount(); i ++){
								const int momindex = getDaughter(i)->momIndex();
								const double px_daughter = fitparams.getStateVector()(momindex);
								const double py_daughter = fitparams.getStateVector()(momindex+1);
								const double pz_daughter = fitparams.getStateVector()(momindex+2);
								px += px_daughter;
								py += py_daughter;
								pz += pz_daughter;
								if(getDaughter(i)->hasEnergy()){
										const double m = getDaughter(i)->getpdgMass();
										E += std::sqrt(m * m + px_daughter * px_daughter + py_daughter * py_daughter + pz_daughter * pz_daughter);
								}
						}
						/** be aware that the signs here are important
						 * * E-|p|-m extracts a negative mass and messes with the momentum !
						 * */
						cons.getResidualM()(0) = mass2 - E * E + px * px + py * py + pz * pz;
						for(int i = 0; i < daughterCount(); i++){
								//dr/dx = d/dx m2-{E1+E2+...}^2+{p1+p2+...}^2 = 2*x (x= E or p)
								const int momindex = getDaughter(i)->momIndex();
								cons.getJacobian()(0, momindex)     = 2.0 * px;
								cons.getJacobian()(0, momindex + 1) = 2.0 * py;
								cons.getJacobian()(0, momindex + 2) = 2.0 * pz;

								if(getDaughter(i)->hasEnergy()){
										cons.getJacobian()(0, momindex + 3) = -2.0 * E;
								}
								else {
										const double px_daughter = fitparams.getStateVector()(momindex);
										const double py_daughter = fitparams.getStateVector()(momindex + 1);
										const double pz_daughter = fitparams.getStateVector()(momindex + 2);
										const double m = getDaughter(i)->getpdgMass();
										const double E_daughter = std::sqrt(m * m + px_daughter * px_daughter + py_daughter*py_daughter +  pz_daughter * pz_daughter);
										const double E_by_E_daughter = E / E_daughter;
										cons.getJacobian()(0, momindex)     -= 2.0 * E_by_E_daughter * px_daughter;
										cons.getJacobian()(0, momindex + 1) -= 2.0 * E_by_E_daughter * py_daughter;
										cons.getJacobian()(0, momindex + 2) -= 2.0 * E_by_E_daughter * pz_daughter;
								}
						}
				}
				return ErrCode(ErrCode::Status::success);
		}

		ErrCode ParticleBase::projectGeoConstraint(const FitParams& fitparams, Constraint& cons) const {
				if(!hasFinalPosition()){
						cerr << "This particle --- " << getName() << " --- don't have decay vertex, can not perform a GeoConstraint on it!" << endl;
						cerr << "Please cheack it!" << endl;
						exit(1);
				}
	/*			if(getMother()->getParticleType() == kHead){
						const int posindexmother = getMother()->posIndex();
						const int posindex = posIndex();
						const int momindex = momIndex();
						double len = fitparams.getStateVector()(posindex + 3);  // decay lenght of the long life internal particle
						Eigen::Matrix < double, 1, -1, 1, 1, 3 > u_vec = fitparams.getStateVector().segment(posindex, 3);
						Eigen::Matrix < double, 1, -1, 1, 1, 3 > uparent_vec = fitparams.getStateVector().segment(posindexmother, 3);
						Eigen::Matrix < double, 1, -1, 1, 1, 3 > mom_vec = fitparams.getStateVector().segment(momindex, 3);

						const double mom  = mom_vec.norm();
						const double mom3  = mom * mom * mom;

						cons.getJacobian()(0, momindex) 	= len *  (mom_vec(1)*mom_vec(1) + mom_vec(2) * mom_vec(2)) /mom3;
						cons.getJacobian()(1, momindex)   = - len * mom_vec(1) * mom_vec(0) / mom3 ;
						cons.getJacobian()(2, momindex)   = - len * mom_vec(2) * mom_vec(0) / mom3 ;

						cons.getJacobian()(0, momindex + 1) = - len * mom_vec(0) * mom_vec(1) / mom3 ;
						cons.getJacobian()(1, momindex + 1) = len * (mom_vec(0) * mom_vec(0) + mom_vec(2) * mom_vec(2)) / mom3 ;
						cons.getJacobian()(2, momindex + 1) = - len * mom_vec(2) * mom_vec(1) / mom3 ;

						cons.getJacobian()(0, momindex + 2) = - len * mom_vec(0) * mom_vec(2) / mom3 ;
						cons.getJacobian()(1, momindex + 2) = - len * mom_vec(1) * mom_vec(2) / mom3 ;
						cons.getJacobian()(2, momindex + 2) = len * (mom_vec(0) * mom_vec(0) + mom_vec(1) * mom_vec(1)) / mom3 ;

						for (int row = 0; row < 3; row++) {
								double momx = mom_vec(row);
								double posx = u_vec(row);
								cons.getJacobian()(row, posindexmother +  row) = 1;
								cons.getJacobian()(row, posindex +  row) = -1;
								cons.getJacobian()(row, posindex+3) = momx / mom;
								double posxmother = getMother()->getRootVertex()(row);
								cons.getResidualM()(row) = posxmother + len * momx / mom - posx;
						}
						cout << "length : " << len << "  " <<  << endl;
						cons.getV().block<3, 3>(0, 0) = getMother()->getRootVertexV().block<3, 3>(0, 0);
				}
				else {
*/


						const int posindexmother = getMother()->posIndex();
						const int posindex = posIndex();
						const int momindex = momIndex();
						double len = fitparams.getStateVector()(posindex + 3);  // decay lenght of the long life internal particle
						Eigen::Matrix < double, 1, -1, 1, 1, 3 > u_vec = fitparams.getStateVector().segment(posindex, 3);
						Eigen::Matrix < double, 1, -1, 1, 1, 3 > uparent_vec = fitparams.getStateVector().segment(posindexmother, 3);
						Eigen::Matrix < double, 1, -1, 1, 1, 3 > mom_vec = fitparams.getStateVector().segment(momindex, 3);

						const double mom  = mom_vec.norm();
						const double mom3  = mom * mom * mom;

						cons.getJacobian()(0, momindex) 	= len *  (mom_vec(1)*mom_vec(1) + mom_vec(2) * mom_vec(2)) /mom3;
						cons.getJacobian()(1, momindex)   = - len * mom_vec(1) * mom_vec(0) / mom3 ;
						cons.getJacobian()(2, momindex)   = - len * mom_vec(2) * mom_vec(0) / mom3 ;

						cons.getJacobian()(0, momindex + 1) = - len * mom_vec(0) * mom_vec(1) / mom3 ;
						cons.getJacobian()(1, momindex + 1) = len * (mom_vec(0) * mom_vec(0) + mom_vec(2) * mom_vec(2)) / mom3 ;
						cons.getJacobian()(2, momindex + 1) = - len * mom_vec(2) * mom_vec(1) / mom3 ;

						cons.getJacobian()(0, momindex + 2) = - len * mom_vec(0) * mom_vec(2) / mom3 ;
						cons.getJacobian()(1, momindex + 2) = - len * mom_vec(1) * mom_vec(2) / mom3 ;
						cons.getJacobian()(2, momindex + 2) = len * (mom_vec(0) * mom_vec(0) + mom_vec(1) * mom_vec(1)) / mom3 ;

						for (int row = 0; row < 3; row++) {
								double momx = mom_vec(row);
								double posx = u_vec(row);
								double posxmother = uparent_vec(row);
								cons.getJacobian()(row, posindexmother +  row) = 1;
								cons.getJacobian()(row, posindex +  row) = -1;
								cons.getJacobian()(row, posindex+3) = momx / mom;
								cons.getResidualM()(row) = posxmother + len * momx / mom - posx;
						}
	//			}
				return ErrCode(ErrCode::Status::success);
		}

		ErrCode ParticleBase::projectKineConstraint(const FitParams& fitparams, Constraint& cons) const {
	/*			if(getParticleType() == kHead){
						const int momindex = momIndex();
						//  set the cms momentum  
						for(int imom = 0; imom < 4; imom++){
		//						cons.getResidualM()(imom) = getRootMomentum()(imom) - fitparams.getStateVector()(momindex + imom);
								cons.getResidualM()(imom) = getRootMomentum()(imom);
								cons.getJacobian()(imom, momindex+imom) = 1;
						}

						for(const auto daughter : m_daughterList) {
								const int daumomindex = daughter->momIndex();
								const Eigen::Matrix<double, 1, 3> p3_vec = fitparams.getStateVector().segment(daumomindex, 3);

								// three momentum is easy just substract the vectors
								for(int imom = 0; imom < 3; imom++){
										cons.getResidualM()(imom) -= p3_vec(imom);
										cons.getJacobian()(imom, daumomindex+imom) = -1;
								}

								if(daughter->hasEnergy()){
										cons.getJacobian()(3, daumomindex+3) = -1;
										cons.getResidualM()(3) -= fitparams.getStateVector()(daumomindex + 3);
								}
								else{
										const double mass = daughter->getpdgMass();
										const double mom = p3_vec.norm();
										const double energy = std::sqrt(mass*mass + mom*mom);
										for(int imom = 0; imom < 3; imom++){
												cons.getJacobian()(3, daumomindex+imom) = -1 * p3_vec(imom) / energy;
										}
								}
						}
				} */
				if(hasDecayVertex()){
						const int momindex = momIndex();
						/*  set the cms momentum  */
						for(int imom = 0; imom < 4; imom++){
								cons.getResidualM()(imom) = fitparams.getStateVector()(momindex + imom);
								cons.getJacobian()(imom, momindex+imom) = 1;
						}

						for(const auto daughter : m_daughterList) {
								const int daumomindex = daughter->momIndex();
								const Eigen::Matrix<double, 1, 3> p3_vec = fitparams.getStateVector().segment(daumomindex, 3);

								// three momentum is easy just substract the vectors
								for(int imom = 0; imom < 3; imom++){
										cons.getResidualM()(imom) -= p3_vec(imom);
										cons.getJacobian()(imom, daumomindex+imom) = -1;
								}

								if(daughter->hasEnergy()){
										cons.getResidualM()(3) -= fitparams.getStateVector()(daumomindex + 3);
										cons.getJacobian()(3, daumomindex+3) = -1;
								}
								else{
										const double mass = daughter->getpdgMass();
										const double mom = p3_vec.norm();
										const double energy = std::sqrt(mass*mass + mom*mom);
										cons.getResidualM()(3) -= energy;
										for(int imom = 0; imom < 3; imom++){
												cons.getJacobian()(3, daumomindex+imom) = -1 * p3_vec(imom) / energy;
										}
								}
						}
				}

				return ErrCode(ErrCode::Status::success);
		}




		void ParticleBase::setPdgValue(const TString name){
				m_PdtTable.Clear();
				m_name = name;
				m_PdtTable =getenv("BESEVTGENROOT");
				m_PdtTable +="/share/pdt.table";
				if(m_debug < 3){
						cout << m_PdtTable << endl;
				}
				fstream  pdtfile;
				pdtfile.open(m_PdtTable, ios::in);
				std::string s;
				bool pdt_name_flag = false;
				int title_count = 0;
				bool pdt_particle_flag = false;
				int particle_property_count = 0;
				std::string particle_property[9];
				m_debug = 5;
				while(pdtfile >> s){
						if(m_debug < 3){
								if(s == "name")
										pdt_name_flag = true;
								if(pdt_name_flag){
										cout << s << "		" ;
										title_count++;
								}
								if(title_count == 9){
										pdt_name_flag = false;
										title_count = 0;
										cout << endl;
								}

						}

						if(s == name && particle_property_count == 0)
								pdt_particle_flag = true;
						if(pdt_particle_flag){
								if(m_debug < 3) {
										cout << s << "		" ;
								}
								particle_property[particle_property_count] = s;
								particle_property_count++;
						}
						if(particle_property_count == 9){
								pdt_particle_flag = false;
								particle_property_count = -1;
								if(m_debug < 3)
										cout << endl;
						}
						if(pdt_particle_flag  && particle_property_count == -1) break;
				}
				m_pdgId = stoi(particle_property[1]);  	// pdt id
				m_pdgMass = stof(particle_property[2]);	// mass / GeV
				m_pdgWidth = stof(particle_property[3]);	// width / GeV
				//			m_pdgId = stoi(particle_property[4]);	// max_Dm / GeV
				m_charge = stoi(particle_property[5])/3;	// 3*charge / 3
				//			m_pdgId = stoi(particle_property[6]);	// 2*spin 
				m_pdgCTau = stof(particle_property[7]) / 10.;	// lifetime c/mm / 10
				//			m_pdgId = stoi(particle_property[8]);	// Lund-KC
				m_debug = 5;
		}


		void ParticleBase::initLen(){
				Eigen::Matrix < double, 1, -1, 1, 1, 3 > vec = getStateVector().segment(4, 3) - getMother()->getStateVector().segment(4, 3);
				cout << getStateVector().segment(4, 3) << endl;
				getStateVector()(7) = vec.norm();
		}

		/*  first preform Particle in decay tree */

		void ParticleBase::Clear(){
				m_debug = 5;
				m_index = -1;
				m_pdgId = 0;
				m_mother = nullptr;
				m_daughterList.clear();
				m_constraintlist.clear();
				m_daughterLeft = nullptr;
				m_daughterRight = nullptr;
				m_name.Clear();
				m_charge = 0;
				m_pdgMass = -1;
				m_pdgWidth = -1;
				m_pdgLifeTime = -1;
				m_pdgCTau = -1;
				m_ptype = kNull;
				m_PdtTable.Clear();
				m_bfield = 0;
				m_chargeddaughterCount = 0;
				m_photondaughterCount = 0;
				/*  measurement parameters */

				m_commonStateVector = Eigen::Matrix<double, 1, 8>::Zero();
				m_commonStateVectorRef = Eigen::Matrix<double, 1, 8>::Zero();
				m_finalPosition = Eigen::Matrix<double, 1, 3>::Zero();
				m_finalPositionRef = Eigen::Matrix<double, 1, 3>::Zero();

#ifndef SKIP001


				m_par = Eigen::Matrix<double, 1, 5>::Zero(1, 5);
				m_referencepar = Eigen::Matrix<double, 1, 5>::Zero(1, 5);
				m_state = Eigen::Matrix<double, 1, 6>::Zero(1, 6);
				m_referencestate = Eigen::Matrix<double, 1, 6>::Zero(1, 6);
				m_covV = Eigen::Matrix<double, 5, 5>::Zero(5, 5);
				m_covC = Eigen::Matrix<double, 6, 6>::Zero(6, 6);
				m_Jacobian = Eigen::Matrix<double, 5, 6>::Zero(5, 6);

				/*  Photon  */
				m_isPhoton = false;

				m_parPho = Eigen::Matrix<double, 1, 4>::Zero(1, 4);
				m_referenceparPho = Eigen::Matrix<double, 1, 4>::Zero(1, 4);
				m_statePho = Eigen::Matrix<double, 1, 6>::Zero(1, 6);
				m_referencestatePho = Eigen::Matrix<double, 1, 6>::Zero(1, 6);
				m_covCPho = Eigen::Matrix<double, 6, 6>::Zero(6, 6);
				m_covVPho = Eigen::Matrix<double, 4, 4>::Zero(4, 4);
				m_JacobianPho = Eigen::Matrix<double, 5, 6>::Zero(5, 6);

				/*  initial parameters. e.g. J/psi at Sqrt(s) = 3.097 GeV  */
				m_isInitialParticle = false;

				m_initPar = Eigen::Matrix<double, 1, 7>::Zero(1, 7);
				m_initParRef = Eigen::Matrix<double, 1, 7>::Zero(1, 7);

				m_initstate = Eigen::Matrix<double, 1, 7>::Zero(1, 7);
				m_initstateRef = Eigen::Matrix<double, 1, 7>::Zero(1, 7);

				m_initcovC = Eigen::Matrix<double, 7, 7>::Zero(7, 7);
				m_initcovV = Eigen::Matrix<double, 7, 7>::Zero(7, 7);
				m_initJacobian = Eigen::Matrix<double, 7, 7>::Zero(7, 7);

				/*  Internal Particle   */

				m_isInternalParticle = false;

#endif

		}
}  //end namespace DecayTreeFitter
