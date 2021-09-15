/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "DecayTreeFitterSvc/ParticleBase.h"
#include "Eigen/Core"

namespace DecayTreeFitter {
//#define SKIP005
#ifndef SKIP005
		class Constraint {

				public:

				enum ConstraintType {
						unknown = 0,
						kCMS,
						kBeamSpot,
						kTrack,
						kPhoton,
						kMassNeutral,
						kKinematic,
						kFourMomentum, 					// 1
						kVertex, // for charged tracks	// 2
						kGeometric,						// 3
						kMass
				};

				Constraint(enum ConstraintType ctype, const int dimState):
						m_ctype(ctype),
						m_dimX(dimState)
				{};
				Constraint( enum ConstraintType ctype, ParticleBase *particle, const int dimState);
				virtual ~Constraint();

	//			virtual bool projectFourMomConstraint(ParticleBase* particle);
	//			virtual void projectConstraint(enum ConstraintType ctype, ParticleBase* particle);

	//			virtual	Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE> & getCovariance(){}
	//			virtual const Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE> & getCovariance() const {} //

				virtual	Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE> & getJacobian(){return m_H;}
				virtual const Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE> & getJacobian() const {return m_H;}

				virtual	Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE> & getV(){return m_V;}
				virtual const Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE> & getV() const {return m_V;}
		//		virtual	Eigen::Matrix < double, 1, Dynamic, 1, 1, MAX_MATRIX_SIZE> & getStateVector(){}
		//		virtual const Eigen::Matrix < double, 1, Dynamic, 1, 1, MAX_MATRIX_SIZE> & getStateVector() const {}

				virtual	Eigen::Matrix < double, 1, Dynamic, 1, 1, MAX_MATRIX_SIZE> & getResidualM(){return m_ResidualM;}
				virtual const Eigen::Matrix < double, 1, Dynamic, 1, 1, MAX_MATRIX_SIZE> & getResidualM() const {return m_ResidualM;}

				virtual const TString Name() const{
						TString name;
						switch(m_ctype){
								case unknown : name  = "unknown"; break;
								case kTrack : name  = "kTrack"; break;
								case kPhoton : name  = "kPhoton"; break;
								case kMassNeutral : name  = "kMassNeutral"; break;
								case kKinematic : name  = "kKinematic"; break;
								case kVertex : name  = "kVertex"; break;
								case kFourMomentum : name  = "kFourMomentum"; break;
								case kGeometric : name  = "kGeometric"; break;
								case kMass : name  = "kMass"; break;
								case kCMS : name  = "kCMS"; break;
								case kBeamSpot : name  = "kBeamSpot"; break;
								default: name = "wrong!";
						}
						return name;
				}

	//			virtual void updateConstraint();
	//			virtual void updateConstraint();
		
				friend ostream& operator<<(ostream & os, const Constraint & cons);
				enum ConstraintType getConsType(){return m_ctype;}
				void initConstraint();
				void resetConstraint();

				const int dimState(){return m_dimX;}
				const int dimRes(){return m_dimM;}

				bool operator<( const Constraint& rhs) const;
				bool operator>( const Constraint& rhs) const;
				bool operator==( const Constraint& rhs ) const { return m_ctype == rhs.m_ctype; }
				bool operator>( const Constraint* rhs) const;
				bool operator<( const Constraint* rhs) const;
				bool operator==( const Constraint* rhs ) const { return m_ctype == rhs->m_ctype; }

				void setDepth(const int depth) {m_depth = depth;}
				int Depth(const int depth) {return m_depth;}

				void setParticle(ParticleBase *p) {particle = p;}
				ParticleBase* Particle() {return particle;}


				private:

						const enum ConstraintType m_ctype;

						const int m_dimX;
						int m_dimM;

						int m_depth;

						ParticleBase* particle;

						std::vector<int> m_dimVector;
						static constexpr double m_espread = 0.0009;
						static constexpr double m_collideangle = 11e-3;
						/*  Matirx  */
						Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE> m_V;
						Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE> m_H;
						Eigen::Matrix < double, 1, Dynamic, 1, 1, MAX_MATRIX_SIZE> m_ResidualM;
		}; //end Constraint
#endif
} // end namespace TreeFitter
#endif

