#include "DecayTreeFitterSvc/Constraint.h"


namespace DecayTreeFitter {

//#define SKIP004		
#ifndef SKIP004
		Constraint::~Constraint(){
				// do something
				initConstraint();
		}

		Constraint::Constraint(enum ConstraintType ctype, ParticleBase *particle, const int dimState):
				m_ctype(ctype),
				m_dimX(dimState)
		{
				switch(m_ctype){
						case kTrack: m_dimM = 5; break;
						case kPhoton: m_dimM = 3; break;
						case kMassNeutral: m_dimM = 0; break;
						case kKinematic: m_dimM = 4; break;
						case kFourMomentum: m_dimM = 4; break;
						case kVertex: m_dimM = 3; break;
						case kGeometric: m_dimM = 3; break;
						case kMass: m_dimM = 1; break;
						case kCMS: m_dimM = 4; break;
						case kBeamSpot: m_dimM = 3; break;
						default: m_dimM = 0;
				}
				if(m_dimM != 0){
				//		cout << "Constraint : Ok!" << endl;
						initConstraint();
				}
		}
		bool Constraint::operator > ( const Constraint& rhs) const {
				return m_ctype > rhs.m_ctype || ( m_ctype == rhs.m_ctype && m_depth > rhs.m_depth);
		}

		bool Constraint::operator > ( const Constraint* rhs) const {
				cout << "test !" << endl;
				return m_ctype > rhs->m_ctype || ( m_ctype == rhs->m_ctype && m_depth > rhs->m_depth);
		}

		bool Constraint::operator < ( const Constraint* rhs) const {
				cout << "test !" << endl;
				return m_ctype < rhs->m_ctype || ( m_ctype == rhs->m_ctype && m_depth > rhs->m_depth);
		}
		bool Constraint::operator < ( const Constraint& rhs) const {
				return m_ctype < rhs.m_ctype || ( m_ctype == rhs.m_ctype && m_depth > rhs.m_depth);
		}


#define SKIP006
#ifndef SKIP006
		/* project FourMomentum Constraint  */
#endif
#define SKIP007
#ifndef SKIP007
		/* project FourMomentum Constraint  */
#endif


		void Constraint::resetConstraint(){
				//			m_ctype = unknown;
				m_V = Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE>::Zero(m_dimM, m_dimM);
				m_H = Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE>::Zero(m_dimM, m_dimX);
				m_ResidualM = Eigen::Matrix < double, 1, Dynamic, 0, 1, MAX_MATRIX_SIZE>::Zero(1, m_dimM);
		}




		void Constraint::initConstraint(){
				//			m_ctype = unknown;
				m_dimVector.clear();
				m_depth = 0;
				particle = nullptr;
				m_V = Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE>::Zero(m_dimM, m_dimM);
				m_H = Eigen::Matrix < double, Dynamic, Dynamic, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE>::Zero(m_dimM, m_dimX);

				m_ResidualM = Eigen::Matrix < double, 1, Dynamic, 0, 1, MAX_MATRIX_SIZE>::Zero(1, m_dimM);
		}

		ostream& operator<<(ostream & os, const Constraint & cons){
				os << "----------------------------------------------------------------- Constraint Type :" ;
				switch(cons.m_ctype){
						case Constraint::kTrack: os << " Track" << endl;break;
						case Constraint::kPhoton: os << " Photon" << endl;break;
						case Constraint::kMassNeutral: os << " MassNeutral" << endl;break;
						case Constraint::kKinematic: os << " Kinematic" << endl;break;
						case Constraint::kFourMomentum: os << " FourMomentum" << endl;break;
						case Constraint::kVertex: os << " Vertex" << endl;break;
						case Constraint::kGeometric: os << " Geometric" << endl;break;
						case Constraint::kMass: os << " Mass" << endl;break;
						case Constraint::kBeamSpot: os << " BeamSpot" << endl;break;
						case Constraint::kCMS: os << " CMS" << endl;break;
						default:break;
				}
				os << "ResidualM : "<< endl ;
				os << cons.m_ResidualM.transpose()<< endl;
				os << "Jacobian Matrix : " << endl;
				os << cons.m_H.transpose()<< endl;
				os << "Covariance Matrix : " << endl;
				os << cons.m_V.transpose()<< endl;
		}
#endif
} // end namespace TreeFitter
