#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/DecayTree.h"

namespace DecayTreeFitter {
		DecayTree::DecayTree(){
				particlelist.clear();
				headparticle = new ParticleBase();
		}
		DecayTree::~DecayTree(){
				for(int i = 0; i < particlelist.size(); i++){
						delete particlelist[i]; // ??
						particlelist[i] = NULL; // ??
						particlelist.clear();
				}
				for(int i = 0; i < compositelist.size(); i++){
						delete compositelist[i]; // ??
						compositelist[i] = NULL; // ??
						compositelist.clear();
				}
		}
		ErrCode DecayTree::initialize(){
				for(int i = 0; i < particlelist.size(); i++){
						delete particlelist[i]; // ??
						particlelist[i] = NULL; // ??
						particlelist.clear();
				}
				for(int i = 0; i < compositelist.size(); i++){
						delete compositelist[i]; // ??
						compositelist[i] = NULL; // ??
						compositelist.clear();
				}
				headparticle->setIndex(-1);
				return ErrCode(ErrCode::Status::success);
		}

		ErrCode DecayTree::AddFinalState(const int number, const TString name, const RecMdcKalTrack *trk){
				ParticleBase *p = new  RecoTrack(number, name, trk);
				p->setDaughterLeft(headparticle);
				p->setDaughterRight(headparticle);
				int type = int(Constraint::kTrack);
				p->setConstraintType(type);
				particlelist.push_back(p);
				return ErrCode(ErrCode::Status::success);
		}
/*

		ErrCode DecayTree::AddFinalState(const int number, const TString name, const WTrackParameter trk){
				ParticleBase *p = new  RecoTrack(number, name, trk);
				p->setDaughterLeft(headparticle);
				p->setDaughterRight(headparticle);
				particlelist.push_back(p);
				return ErrCode(ErrCode::Status::success);
		}
*/

		ErrCode DecayTree::AddFinalState(const int number, const TString name, const RecEmcShower *trk){
				ParticleBase *p = new RecoPhoton(number, name, trk);
				p->setDaughterLeft(headparticle);
				p->setDaughterRight(headparticle);
				int type = int(Constraint::kPhoton);
				p->setConstraintType(type);
				particlelist.push_back(p);
				return ErrCode(ErrCode::Status::success);
		}

		ErrCode DecayTree::AddInternalParticle(const int number, const TString name, Vint dauglist){
				ParticleBase *p = new InternalParticle(number, name);
				if(dauglist.size() == 2){
						p->setDaughterLeft(particlelist[dauglist[0]]);
						p->setDaughterRight(particlelist[dauglist[1]]);
						for(int i  = 0; i < dauglist.size(); i++){
								p->setDaughter(particlelist[dauglist[i]]);
								p->getDaughter(i)->setMother(p);
						}
				}
				else if(dauglist.size() > 2){
						for(int i  = 0; i < dauglist.size() - 1; i++){
								if(i == (dauglist.size() - 2)){
										compositelist[compositelist.size() - 1]->setDaughterLeft(particlelist[dauglist[i]]);
										compositelist[compositelist.size() - 1]->setDaughterRight(particlelist[dauglist[i+1]]);
										p->setDaughter(particlelist[dauglist[i]]);
										p->setDaughter(particlelist[dauglist[i+1]]);
										p->getDaughter(i)->setMother(p);
										p->getDaughter(i+1)->setMother(p);
								}
								else{
										ParticleBase *pcomposite = new RecoComposite(-2, "Composite");
										p->setDaughterLeft(particlelist[dauglist[i]]);
										p->setDaughterRight(pcomposite);
										p->setDaughter(particlelist[dauglist[i]]);
										p->getDaughter(i)->setMother(p);
										compositelist.push_back(pcomposite);
								}
						}
				}
				int type = int(Constraint::kKinematic);
				p->setConstraintType(type);
				type = int(Constraint::kGeometric);
				p->setConstraintType(type);
				particlelist.push_back(p);
				return ErrCode(ErrCode::Status::success);
		}

		ErrCode DecayTree::AddResonance(const int number, const TString name, Vint dauglist){
				ParticleBase *p = new Resonance(number, name);

				if(dauglist.size() == 2){
						p->setDaughterLeft(particlelist[dauglist[0]]);
						p->setDaughterRight(particlelist[dauglist[1]]);
						for(int i  = 0; i < dauglist.size(); i++){
								p->setDaughter(particlelist[dauglist[i]]);
								p->getDaughter(i)->setMother(p);
						}
				}
				else if(dauglist.size() > 2){
						for(int i  = 0; i < dauglist.size() - 1; i++){
								if(i == (dauglist.size() - 2)){
										compositelist[compositelist.size() - 1]->setDaughterLeft(particlelist[dauglist[i]]);
										compositelist[compositelist.size() - 1]->setDaughterRight(particlelist[dauglist[i+1]]);
										p->setDaughter(particlelist[dauglist[i]]);
										p->setDaughter(particlelist[dauglist[i+1]]);
										p->getDaughter(i)->setMother(p);
										p->getDaughter(i+1)->setMother(p);
								}
								else{
										ParticleBase *pcomposite = new RecoComposite(-2, "Composite");
										p->setDaughterLeft(particlelist[dauglist[i]]);
										p->setDaughterRight(pcomposite);
										p->setDaughter(particlelist[dauglist[i]]);
										p->getDaughter(i)->setMother(p);
										compositelist.push_back(pcomposite);
								}
						}
				}

				int type = int(Constraint::kKinematic);
				p->setConstraintType(type);
				type = int(Constraint::kMass);
				p->setConstraintType(type);
				particlelist.push_back(p);
				return ErrCode(ErrCode::Status::success);
		}



		ErrCode DecayTree::AddCMS(const int number, const TString name, const HepLorentzVector trk, Vint dauglist){
				//001cout << dauglist.size() << endl;
				ParticleBase *p = new RootParticle(number, name, trk);
			//	ParticleBase *particle = &p;
				//001cout << dauglist.size() << endl;
				if(dauglist.size() == 2){
						p->setDaughterLeft(particlelist[dauglist[0]]);
						p->setDaughterRight(particlelist[dauglist[1]]);
						for(int i  = 0; i < dauglist.size(); i++){
								p->setDaughter(particlelist[dauglist[i]]);
								p->getDaughter(i)->setMother(p);
						}
				}
				else if(dauglist.size() > 2){
						for(int i  = 0; i < dauglist.size() - 1; i++){
								if(i == (dauglist.size() - 2)){
										compositelist[compositelist.size() - 1]->setDaughterLeft(particlelist[dauglist[i]]);
										compositelist[compositelist.size() - 1]->setDaughterRight(particlelist[dauglist[i+1]]);
										p->setDaughter(particlelist[dauglist[i]]);
										p->setDaughter(particlelist[dauglist[i+1]]);
										p->getDaughter(i)->setMother(p);
										p->getDaughter(i+1)->setMother(p);
								}
								else{
										ParticleBase *pcomposite = new RecoComposite(-2, "Composite");
										p->setDaughterLeft(particlelist[dauglist[i]]);
										p->setDaughterRight(pcomposite);
										p->setDaughter(particlelist[dauglist[i]]);
										p->getDaughter(i)->setMother(p);
										compositelist.push_back(pcomposite);
								}
						}
				}

				int type = int(Constraint::kKinematic);
				p->setConstraintType(type);
				type = int(Constraint::kBeamSpot);
				p->setConstraintType(type);
				type = int(Constraint::kCMS);
				p->setConstraintType(type);

				particlelist.push_back(p);
				//	particlelist[number] = particle;
				return ErrCode(ErrCode::Status::success);
		}

		void DecayTree::preformDecayTree(ParticleBase *particle){
				preformMomentum(particle);
				preformPosition(particle);
				printDecayTree(particle);
		}
		/* main fit function that uses the kalman filter  */
		bool DecayTree::Fit(){

				ParticleBase *phead = Head(particlelist[0]);

				preformDecayTree(phead);

				m_dimState = 8 * particlelist.size(); 

				m_fitparams = new FitParams(m_dimState);

				m_treeCount.clear();
				initialParams(phead);

		//		cout << "m_fitparams.getStateVector()" << endl;
	//			cout << *m_fitparams << endl;
				m_treeCount.clear();
				initialCovariance(phead);
				constraintlist.clear();
				initialConstraint();
			//	cout << m_fitparams->getStateVector() << endl;
			//	cout << m_fitparams->getCovariance() << endl;
				
				std::sort(constraintlist.begin(), constraintlist.end(), pointer_less());

				double tmpChi = -1;
				bool Finished = false;
				NiterMax = 10;
				for(m_niter = 0; m_niter < NiterMax && !Finished; m_niter++){
						ErrCode status;
						if( m_niter   == 0){
								m_fitparams->resetCovariance();
								initialCovariance(phead);
								m_fitparams->resetChiSquare();
								for(auto constraint : constraintlist){
										KalmanCalculator kalman(constraint->dimRes(), constraint->dimState());
										double chisq = 0;
										int iter = 0;
										bool finished = false;
										double accumulated_chi2 = 0;
										int m_maxNIter = 10;

										while( !finished && !status.failure() ){
												constraint->resetConstraint();
												status |= constraint->Particle()->projectConstraint(*m_fitparams, *constraint);
												if(!status.failure()){
												status |= kalman.calculateGainMatrix(*m_fitparams, *constraint);
												if(!status.failure()){
														kalman.updateState(*m_fitparams);
														double newchisq = kalman.getChiSquare();
														double dchisqconverged = 0.001;
														double dchisq = newchisq - chisq;
														bool diverging = iter > 0 && dchisq > 0;
														bool converged = std::abs(dchisq) < dchisqconverged;
														finished  = ++iter >= m_maxNIter || diverging || converged;
														chisq = newchisq;
														accumulated_chi2 += newchisq;
												}
										}
								}
										m_chisq = accumulated_chi2;
								//		cout << "accumulated_chi2 : " << accumulated_chi2 << endl;
								kalman.updateCovariance(*m_fitparams);
								}
								cout << *m_fitparams << endl;
							//	cout << "end of niter == 1" << endl;
							//	cout << *m_fitparams << endl;
						}
						else if (m_niter > 0){
								auto* oldfitparams = new FitParams(*m_fitparams);
								m_fitparams->resetCovariance();
								initialCovariance(phead);
								m_fitparams->resetChiSquare();
								double tmpChisq = 0;
								for(auto constraint : constraintlist){
								//		cin.get();
										KalmanCalculator kalman(constraint->dimRes(), constraint->dimState());
										constraint->resetConstraint();
										status |= constraint->Particle()->projectConstraint(*m_fitparams, *constraint);
										constraint->getResidualM() = 0.5*constraint->getResidualM() +  0.5* (constraint->getJacobian() * (m_fitparams->getStateVector() - oldfitparams->getStateVector()).transpose()).transpose(); 
	//									constraint->getResidualM() += (constraint->getJacobian() * (m_fitparams->getStateVector() - oldfitparams->getStateVector()).transpose()).transpose(); 
								//		cout << constraint->getResidualM() << endl;
										if(!status.failure()){
												status |= kalman.calculateGainMatrix(*m_fitparams, *constraint);
												if(!status.failure()){
														kalman.updateState(*m_fitparams);
												}
										}
										kalman.updateCovariance(*m_fitparams);
										tmpChisq += kalman.chisq();
								}
								delete oldfitparams;
								double deltachisq  = tmpChisq - tmpChi;
							//	cout << "chisq : " << fabs(deltachisq)/ tmpChi  << endl;
								if(m_niter > 1){
								if(fabs(deltachisq)/tmpChisq  < 0.01 )
										Finished = true;
								}

								tmpChi = tmpChisq;
							//	cout << "tmpchisq : " << tmpChisq  << endl;
							//	cout << *m_fitparams << endl;
						}
				//		cout << *m_fitparams << endl;

				}


			//	cout << *m_fitparams << endl;


				for(int i = 0; i < constraintlist.size(); i++){
						delete constraintlist[i];
				}
				constraintlist.clear();

				CopyParams(phead);
				printDecayTree(phead);

				delete m_fitparams;

				return true;
		}


		double DecayTree::decayLength(TString name){
				for(auto part : particlelist){
						if(part->getName() == name){
								return part->getStateVector()(7);
						}
				}
		}

		const Eigen::Matrix<double, 1, 8> DecayTree::getStateVector(const int index){
				if(index < 0) {cout << "error index!" << endl; exit(1); }
				for(auto part : particlelist){
						if(part->getIndex() == index){
								if(part->hasEnergy()){
										return part->getStateVector();
								}
								else{
										double px = part->getStateVector()(0);
										double py = part->getStateVector()(1);
										double pz = part->getStateVector()(2);
										part->getStateVector()(3) = sqrt(px*px + py*py + pz*pz + part->getpdgMass()*part->getpdgMass());
										return part->getStateVector();
								}
						}
				}
		}



		//#define SKIP003
#ifndef SKIP003

		void DecayTree::initialConstraint(){
				for(int i = 0; i < particlelist.size(); i++){
						int ctypeSize = particlelist[i]->ConstraintSize();
						for(int ic = 0; ic < ctypeSize; ic++){
								Constraint::ConstraintType ctype = Constraint::ConstraintType(particlelist[i]->ConstraintType(ic));
								Constraint *cons = new Constraint(ctype, particlelist[i], m_dimState);
								particlelist[i]->projectConstraint(*m_fitparams, *cons);
								cons->setDepth(Depth( particlelist[i] ));
								cons->setParticle(particlelist[i]);
								constraintlist.push_back(cons);
						}
				}
		}



		bool DecayTree::CopyParams(ParticleBase *particle){
				if(particle->getIndex() != -1){
						if(CopyParams(particle->getDaughterLeft()))
								if(CopyParams(particle->getDaughterRight())){
										if(particle->getParticleType() != ParticleBase::kComposite){
												for(int i = 0; i < 8; i ++){
														particle->getStateVector()(i) = m_fitparams->getStateVector()(particle->momIndex() + i);
												}
										}
										return true;
								}
						return false;
				}
				else {
						return true;
				}
		}






		bool DecayTree::initialParams(ParticleBase *particle){
				if(particle->getIndex() != -1){
						if(initialParams(particle->getDaughterLeft()))
								if(initialParams(particle->getDaughterRight())){
										if(particle->getParticleType() != ParticleBase::kComposite){
												int particle_index = m_treeCount.size();
												particle->setmomIndex(8*particle_index + 0);
												particle->setposIndex(8*particle_index + 4);
												if(particle->ChargedDaughterCount() != 0){
														particle->getStateVector()(POSI_IDX + 0) /= particle->ChargedDaughterCount();
														particle->getStateVector()(POSI_IDX + 1) /= particle->ChargedDaughterCount();
														particle->getStateVector()(POSI_IDX + 2) /= particle->ChargedDaughterCount();
												}
												if(particle->getParticleType() == ParticleBase::kInternalParticle){
														particle->initLen();
												}
												for(int i = 0; i < 8; i ++){
														m_fitparams->getStateVector()(8*particle_index + i) = particle->getStateVector()(i);
												}
												m_treeCount.push_back(1);
										}
										return true;
								}
						return false;
				}
				else {
						return true;
				}
		}


		bool DecayTree::initialCovariance(ParticleBase *particle){
				if(particle->getIndex() != -1){
						if(initialCovariance(particle->getDaughterLeft()))
								if(initialCovariance(particle->getDaughterRight())){
										if(particle->getParticleType() != ParticleBase::kComposite){
												particle->initCovariance(*m_fitparams);
										}
										return true;
								}
						return false;
				}
				else {
						return true;
				}
		}


		bool DecayTree::preformMomentum(ParticleBase *particle){
				if(particle->getIndex() != -1){
						if(preformMomentum(particle->getDaughterLeft()))
								if(preformMomentum(particle->getDaughterRight())){

										if(particle->getParticleType() != ParticleBase::kComposite){
												if(particle->getParticleType() != ParticleBase::kHead){
														if(particle->getMother()->getParticleType() != ParticleBase::kHead){
																for(int i = 0; i < 4; i++){
																		particle->getMother()->getStateVector()(MOM_IDX + i) += particle->getStateVector()(MOM_IDX + i);
																}
														}
												}
										}
										return true;
								}
						return false;
				}
				else {
						return true;
				}
		}

		bool DecayTree::preformPosition(ParticleBase *particle){
				if(particle->getIndex() != -1){
						if(preformPosition(particle->getDaughterLeft()))
								if(preformPosition(particle->getDaughterRight())){
										if(particle->getParticleType() != ParticleBase::kComposite){
												if(particle->getParticleType() == ParticleBase::kChargeTrack){
														ParticleBase *internalMother;
														internalMother = particle->getMother();
														while(internalMother->getParticleType() == ParticleBase::kResonance){
																internalMother = internalMother->getMother();
														}
														internalMother->addChargedDaughter(1);
														for(int i = 0; i < 3; i++){
																internalMother->getStateVector()(POSI_IDX + i) += particle->getStateVector()(POSI_IDX + i);
														}
												}
										}
										return true;
								}
						return false;
				}
				else {
						return true;
				}
		}

		ParticleBase* DecayTree::Head(ParticleBase* particle){
				ParticleBase *p;
				p = particle;
				while(p->getParticleType() != ParticleBase::kHead){
						p = p->getMother();
				}
				return p;
		}

		bool DecayTree::printDecayTree(ParticleBase* particle, const int flag){
				if(particle->getIndex() == -1){
						return true;
				}
				else {
						if(particle->getParticleType() != ParticleBase::kComposite){
								int depth = Depth(particle);
								for(int i = 0; i < depth; i++){

										if(i == depth -1){
												if(flag == -1 || flag == 0){
														cout <<" |-----> ";
												}
												else if(flag == 1){
														cout <<" `-----> ";
												}
										}
										else {
												cout << "        ";
										}
								}
								cout << particle->getName() << "    " ;
								for(int i = 0; i < 8; i++){
										cout << particle->getStateVector()(i) << "    " ;
								}
								cout << endl;
						}
						if(printDecayTree(particle->getDaughterLeft(), -1))
								if(printDecayTree(particle->getDaughterRight(), 1))
										return true;
						return false;
				}
		}

		int DecayTree::Depth(ParticleBase* particle){
				int depth_i = 0;
				while(particle->getParticleType() != ParticleBase::kHead){
						depth_i ++;
						particle = particle->getMother();
				}
				return depth_i;
		}
#endif
}// end namespace TreeFitter

