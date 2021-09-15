/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef PARTICLE_BASE_H
#define PARTICLE_BASE_H

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/IHistogramSvc.h"

#include "Eigen/Core"

#include "VertexFit/IVertexDbSvc.h"
#include "DecayTreeFitterSvc/HelixUtils.h"

#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/ErrCode.h"
#include "DecayTreeFitterSvc/EigenStackConfig.h"
//#include "DecayTreeFitterSvc/FitParams.h"
//#include "DecayTreeFitterSvc/Constraint.h"
#include "VertexFit/WTrackParameter.h"
#include "VertexFit/GammaShape.h"
#include "TString.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Geometry/Point3D.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "MdcRecEvent/RecMdcTrack.h"
#include "MdcRecEvent/RecMdcKalTrack.h"
#include "EmcRecEventModel/RecEmcShower.h"
#include <vector>
#include <iomanip>
using namespace std;
using namespace Eigen;
using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;

typedef HepGeom::Point3D<double> HepPoint3D;


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MOM_IDX 0
#define POSI_IDX 4

namespace DecayTreeFitter {
		class FitParams;
		class Constraint;

		static std::vector<int> daughterList(int a, ...){
				std::vector<int> dauglist;
				va_list argptr;
				va_start(argptr,a); 
				for(; a > 0; a--){
						int args=va_arg(argptr,int);
						dauglist.push_back(args);
				}
				va_end(argptr);
				return dauglist;
		}






		class ParticleBase {

				public:
						/* particle type */
						enum ParticleType {
								kNull,
								kHead,
								kInternalParticle,
								kResonance,
								kComposite,
								/*final state*/
								kChargeTrack,
								kPhoton,
								kMissNeutral,
								kMassiveNeutral,
								kMissParticle,
								kNeutrino
						};
						/* default constructor */
						ParticleBase();
						ParticleBase(const int number, const TString name);
						virtual ~ParticleBase();

						virtual ParticleBase *getParticle(){return this;}

						virtual ErrCode initialParticle(const int number,  const TString name);
						virtual ErrCode initialParticle(const RecMdcKalTrack *trk) {};
						virtual ErrCode initialParticle(const WTrackParameter trk) {};
						virtual ErrCode initialParticle(const RecEmcShower *trk) {};
						virtual ErrCode initialParticle(const HepLorentzVector trk) {};
						/*  index  */
						virtual const int getIndex() {return m_index;}
						virtual const int setIndex(const int i ) {m_index = i;}
						/* pdg value */
						virtual const double getpdgMass() const {return m_pdgMass;}
						virtual const int getpdgId() const {return m_pdgId;}
						virtual const int getcharge() const { return m_charge;}
						virtual const TString getName() const {return m_name;}
						virtual const double getpdgLifeTime() const { return m_pdgLifeTime;}
						virtual const double getpdgCTau() const { return m_pdgCTau;}
						virtual double getpdgWidth() {return m_pdgWidth;} 
						/* particle type */ 
						virtual const int getParticleType() const {return m_ptype;}
						/* final state don't have decay vertex */
						/* kNull return false */
						virtual const bool hasDecayVertex() const{ 
								if(m_ptype == kNull) return false;
								return m_ptype >= kChargeTrack ? false : true;
						}
						virtual const  bool isFinalState() const {
								if(m_ptype == kNull) return false;
								return m_ptype >= kChargeTrack ? true : false;
						}
						/* charge track and neutrino and MissParticle don't have end point  *
						 * Head particle and resonance have a zero decay length */
						/* kNull return false */
						virtual const bool hasFinalPosition() const {
								if(m_ptype == kNull) return false;
								return (m_ptype == kChargeTrack || m_ptype == kMissParticle || m_ptype ==  kNeutrino) ? false: true;
						}

						virtual void setDaughter(ParticleBase *particle) {
								m_daughterList.push_back(particle);
								int size  = m_daughterList.size();
							//	cout << "set daughters " << m_daughterList[size-1]->getpdgId() << endl;
						}
						virtual void setDaughterLeft(ParticleBase *particle){
								m_daughterLeft = particle;
						}
						virtual void setDaughterRight(ParticleBase *particle){
								m_daughterRight = particle;
						}

						virtual ParticleBase* getDaughterLeft(){
								return m_daughterLeft;
						}
						virtual ParticleBase* getDaughterRight(){
								return m_daughterRight;
						}

						virtual const ParticleBase* getDaughter(int index) const {return m_daughterList[index];}
						virtual ParticleBase* getDaughter(int index) {return m_daughterList[index];}
						virtual const int daughterCount() const {return m_daughterList.size();}

						virtual void setMother(ParticleBase *particle) {m_mother = particle;}
						virtual const ParticleBase* getMother() const {return m_mother;}
						virtual ParticleBase* getMother() {return m_mother;}
					//	virtual ErrCode  preformParticle() = 0;
					//	virtual ErrCode  preformMomentum();  //  LRD order traverse
					//	virtual ErrCode  preformPosition();

						virtual Eigen::Matrix<double, 1, 8> & getStateVector() {return m_commonStateVector;}
						virtual const Eigen::Matrix<double, 1, 8> & getStateVector() const {return m_commonStateVector;}
						virtual Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> & getMeasurement() {}
						virtual const Eigen::Matrix<double, 1, Dynamic, 1, 1, 7> & getMeasurement() const {}
						virtual Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getmCovariance() {}
						virtual const Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getmCovariance() const {}
						virtual Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getJacobian() {}
						virtual const Eigen::Matrix<double, Dynamic, Dynamic, 0, 7, 7> & getJacobian() const {}
						virtual void updateParticle() {}

						virtual void addChargedDaughter(const int num){ m_chargeddaughterCount+=num;}
						virtual void addPhotonDaughter(const int num){ m_photondaughterCount+=num;}

						virtual const int ChargedDaughterCount() const {return m_chargeddaughterCount;}
						virtual const int PhotonDaughterCount() const {return m_photondaughterCount;}

						/**  get vertex index (in statevector!) */
						virtual const int posIndex() const { return m_posi_index ; }
						virtual void setposIndex(const int index) { m_posi_index  = index;}
						/**  get momentum index */
						virtual const int momIndex() const { return m_mom_index ; }
						virtual void setmomIndex(const int index) { m_mom_index  = index;}
						// does the particle have a 3-momentum or a 4-momentum ?
						/** get momentum dimension  */
						virtual bool hasEnergy() const { return false ; }
						virtual void setMassConstraint() { /* for InternalParticle and Resonance, m_hasEnergy = false */  ;} 
						virtual bool hasPosition() const { return false ; }

						virtual ErrCode projectConstraint(const FitParams& fitparams, Constraint& cons) const;
	//					virtual ErrCode projectMassConstraintDaughtor(const FitParams&, Constraint& cons) const;
						virtual ErrCode projectMassConstraint(const FitParams&, Constraint& cons) const;
						/**  project geometrical constraint */
						virtual ErrCode projectGeoConstraint(const FitParams&, Constraint& ) const ;
						/**  project kinematic constraint */
						virtual ErrCode projectKineConstraint(const FitParams&, Constraint& ) const ;
						/**  interaction point of e+ e-; read from VertexDBS  **/
						virtual Eigen::Matrix<double, 1, 3> & getRootVertex() { cerr << "It's not a cms particle!" << endl; exit(1); };
						virtual const Eigen::Matrix<double, 1, 3> & getRootVertex() const {cerr << "It's not a cms particle!" << endl; exit(1); };
						virtual Eigen::Matrix<double, 3, 3> & getRootVertexV() {cerr << "It's not a cms particle!" << endl; exit(1); };
						virtual const Eigen::Matrix<double, 3, 3> & getRootVertexV() const {cerr << "It's not a cms particle!" << endl; exit(1);};
						/**  cms momentum of e+ e-  **/
						virtual Eigen::Matrix<double, 1, 4> & getRootMomentum() {cerr << "It's not a cms particle!" << endl; exit(1);};
						virtual const Eigen::Matrix<double, 1, 4> & getRootMomentum() const {cerr << "It's not a cms particle!" << endl; exit(1);};
						/**  if cms is J/psi or psi(2S), it will have error matrix, E_spread **/
						virtual Eigen::Matrix<double, 4, 4> & getRootMomentumV() {cerr << "It's not a cms particle!" << endl; exit(1);};
						virtual const Eigen::Matrix<double, 4, 4> & getRootMomentumV() const {cerr << "It's not a cms particle!" << endl; exit(1);};

						virtual ErrCode initCovariance(FitParams& fitparams) const;

						virtual void setConstraintType(const int c){ m_constraintlist.push_back(c);}
						virtual int ConstraintType(const int i) const { return m_constraintlist[i];}
						virtual int ConstraintSize() const { return m_constraintlist.size();}
						virtual void initLen();







						
#define SKIP002
#ifndef SKIP002

						/*  measurement parameters */
						virtual Eigen::Matrix<double, 1, 8> getPar() const = 0;							// current parameter vector
						virtual Eigen::Matrix<double, 1, 8> getParRef() const = 0;							// current parameter vector
						/*  particle state vector */
						virtual Eigen::Matrix<double, 1, 8> getStateVector() const = 0;					// current state vector
						virtual Eigen::Matrix<double, 1, 8> getStateVectorRef() const = 0;		// reference state vector
						/*  covariance matrix C; error matrix of observable */
						virtual Eigen::Matrix<double, 8, 8>  getC() const = 0;
						/*  covariance matrix V; error matrix of measurement*/
						virtual Eigen::Matrix<double, Dynamic, Dynamic, 0, 8, 8>  getV() const = 0;
						/*  Jacobian matrix */
			

						/*  measurement parameters */
						virtual void updatePar() = 0;							// current parameter vector
						virtual void updateParRef() = 0;					// reference parameter vector
						/*  particle state vector */
						virtual void updateStateVector() = 0;					// current state vector
						virtual void updateStateVectorRef() = 0;		// reference state vector
						/*  covariance matrix C */
						virtual void updateC() = 0;
						/*  covariance matrix V */
						virtual void updateV() = 0;
						/*  Jacobian matrix */
						virtual void updateH() = 0;

						virtual ErrCode projectRecoConstraint(const RecMdcKalTrack *trk) = 0;
						virtual ErrCode projectRecoConstraint(const RecEmcShower *trk) = 0;
						virtual ErrCode projectRecoConstraint(const HepLorentzVector trk) = 0;
						virtual ErrCode projectRecoConstraint(const WTrackParameter trk) = 0;
#endif
						virtual void setName(const TString name) {m_name.Clear(); m_name.Append(name);}
						virtual void setcharge(const double charge){m_charge = charge;}
						virtual void setpdgMass(const double pdgMass){m_pdgMass = pdgMass;}
						virtual void setpdgLifeTime(const double pdgLifeTime){m_pdgLifeTime = pdgLifeTime;}
						virtual void setpdgWidth(const double pdgWidth){m_pdgWidth = pdgWidth;}
	
						virtual void setPdgValue(const TString name);

						void printParticleName(int pid){
								switch(pid){
										case 2212: cout << "Particle name: proton+" << endl; break;
										case -2212: cout << "Particle name: proton-" << endl; break;
										case 11: cout << "Particle name: electron-" << endl; break;
										case -11: cout << "Particle name: electron+" << endl; break;
										case 321: cout << "Particle name: kaon+" << endl; break;
										case -321: cout << "Particle name: kaon-" << endl; break;
										case 211: cout << "Particle name: pion+" << endl; break;
										case -211: cout << "Particle name: pion-" << endl; break;
										case 13: cout << "Particle name: mu+" << endl; break;
										case -13: cout << "Particle name: mu-" << endl; break;
										default:;

								}
						}

						void Clear();

				protected:
						/* debug, 0, 1, 2, 3, 4, 5  */
						int m_debug;
						/* index */
						int m_index;
						/* pdg value */
						int m_pdgId;

						int m_charge;

						double m_pdgMass;

						double m_pdgWidth;

						double m_pdgLifeTime;

						double m_pdgCTau;

						TString m_name;
						/* measurement parameters*/
						/* defined in subclass */
						//Eigen::Matrix<double, 1, Dynamic, 0, 1, 8> m_measurementPar;
						//Eigen::Matrix<double, 1, Dynamic, 0, 1, 8> m_measurementParRef;
						/* common state vector Px Py Pz E x y z tau  */
						Eigen::Matrix<double, 1, 8> m_commonStateVector;
						Eigen::Matrix<double, 1, 8> m_commonStateVectorRef;
						/* final position x y z */
						Eigen::Matrix<double, 1, 3> m_finalPosition;
						Eigen::Matrix<double, 1, 3> m_finalPositionRef;
						/* measurement error matrix */
						Eigen::Matrix<double, -1, -1, 0, 8, 8> m_V;
						/* measurement vertex*/
						Eigen::Matrix<double, 1, -1, 1, 1, 8> m_measurementVector;
						/*  residual_m */
						Eigen::Matrix<double, 1, -1, 1, 1, 8> m_residualM;
						/* index in global state vector */
						int m_mom_index;  // momentum index
						int m_posi_index; // position index

						typedef vector<ParticleBase*> VParticleBase;
						/* piont to mother and daughters*/
						ParticleBase *m_mother;
						VParticleBase m_daughterList;
						ParticleBase *m_daughterLeft;
						ParticleBase *m_daughterRight;

	//					int m_ptype;
						/* Particle Type  */
						enum ParticleType m_ptype;

						TString m_PdtTable;

						double m_bfield;


						/* tree preform*/

						int m_chargeddaughterCount;
						int m_photondaughterCount;

						std::vector<int> m_constraintlist;   // a vector used to store constraint type
 

#define SKIP001
#ifndef SKIP001

						Eigen::Matrix<double, 1, 7> m_public_StateVector;
						Eigen::Matrix<double, 1, 3> m_finalPosition;
						
						/*  Charged Track */

						bool m_isfinalCharge;

						/*  measurement parameters */
						Eigen::Matrix<double, 1, 5> m_par;							// current parameter vector
						Eigen::Matrix<double, 1, 5> m_referencepar;					// reference parameter vector
						/*  particle state vector */
						Eigen::Matrix<double, 1, 6> m_state;					// current state vector
						Eigen::Matrix<double, 1, 6> m_referencestate;		// reference state vector
						/*  covariance matrix C */
						Eigen::Matrix<double, 6, 6>  m_covC;
						/*  covariance matrix H */
						Eigen::Matrix<double, 5, 5>  m_covV;
						/*  Jacobian matrix */
						Eigen::Matrix<double, 5, 6> m_Jacobian;

						/*  Photon  */

						bool m_isPhoton;

						/*  measurement parameters */
						Eigen::Matrix<double, 1, 4> m_parPho;
						Eigen::Matrix<double, 1, 4> m_referenceparPho;
						/*  particle state vector */
						Eigen::Matrix<double, 1, 6> m_statePho;					// current state vector
						Eigen::Matrix<double, 1, 6> m_referencestatePho;		// reference state vector
						/*  covariance matrix C */
						Eigen::Matrix<double, 6, 6>  m_covCPho;
						/*  covariance matrix H */
						Eigen::Matrix<double, 4, 4>  m_covVPho;
						/*  Jacobian matrix */
						Eigen::Matrix<double, 5, 6> m_JacobianPho;


						/*  initial parameters. e.g. J/psi at Sqrt(s) = 3.097 GeV  */

						bool m_isInitialParticle;


						Eigen::Matrix<double, 1, 7> m_initPar;
						Eigen::Matrix<double, 1, 7> m_initParRef;

						Eigen::Matrix<double, 1, 7> m_initstate;
						Eigen::Matrix<double, 1, 7> m_initstateRef;
						
						Eigen::Matrix<double, 7, 7>  m_initcovC;
						Eigen::Matrix<double, 7, 7>  m_initcovV;
						Eigen::Matrix<double, 7, 7>  m_initJacobian;
						
						/*  Internal Particle   */

						bool m_isInternalParticle;

						Eigen::Matrix<double, 1, 7> m_internalPar;
						Eigen::Matrix<double, 1, 7> m_internalParRef;

						Eigen::Matrix<double, 1, 7> m_internalstate;
						Eigen::Matrix<double, 1, 7> m_internalstateRef;
						
						Eigen::Matrix<double, 7, 7>  m_internalcovC;
						Eigen::Matrix<double, 7, 7>  m_internalcovV;
						Eigen::Matrix<double, 7, 7>  m_internalJacobian;

						/* Resonance   */

						bool m_isResonance;

#endif


				//		double m_Mass;
				//		double m_Width;
				//		double m_LifeTime;
				//		double m_decayLength;
				//		double m_Life;

		}; // end class ParticleBase
} // end namespace TreeFitter
#endif
