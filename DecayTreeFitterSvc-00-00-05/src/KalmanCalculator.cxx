#include "DecayTreeFitterSvc/KalmanCalculator.h"
#include <Eigen/Dense>
#include "TMatrixDSym.h"
#include <iostream>

namespace DecayTreeFitter {

		KalmanCalculator::KalmanCalculator(
						int sizeRes,
						int sizeState
						) :
				m_constrDim(sizeRes),
				m_stateDim(sizeState),
				m_chisq(1e10),
				m_res(sizeRes),
				m_G(sizeRes, sizeState),
				m_R(sizeRes, sizeRes),
				m_Rinverse(sizeRes, sizeRes),
				Rtemp(sizeRes, sizeRes),
				RInvtemp(sizeRes, sizeRes),
				m_K(sizeState, sizeRes),
				m_CGt(sizeState, sizeRes)
		{
				m_R = Eigen::Matrix < double, -1, -1, 0, 7, 7 >::Zero(m_constrDim, m_constrDim);
				m_G = Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE >::Zero(m_constrDim, m_stateDim);
				m_K = Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE >::Zero(m_stateDim, m_constrDim);
				m_V = Eigen::Matrix < double, -1, -1, 0, 7, 7 >::Zero(m_constrDim, m_constrDim);
				m_C = Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE >::Zero(m_stateDim, m_stateDim);
				m_res = Eigen::Matrix < double, 1, -1, 1, 1, MAX_MATRIX_SIZE>::Zero(m_constrDim);
				m_CGt = Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE >::Zero(m_stateDim, m_constrDim);
				Rtemp = Eigen::Matrix < double, -1, -1, 0, 7, 7 >::Zero(m_constrDim, m_constrDim);
				RInvtemp = Eigen::Matrix < double, -1, -1, 0, 7, 7 >::Zero(m_constrDim, m_constrDim);
				m_Rinverse = Eigen::Matrix < double, -1, -1, 0, 7, 7 >::Zero(m_constrDim, m_constrDim);
		}


//#define SKIP009
#ifndef SKIP009
		
		ErrCode KalmanCalculator::calculateGainMatrix(
						const FitParams& fitparams,
						const Constraint& cons,
						double weight)
		{
				const int sizeState = cons.getJacobian().rows();
				const int sizeRes = cons.getJacobian().cols();
				m_G = cons.getJacobian();
				m_V =	cons.getV();
				m_C = fitparams.getCovariance().triangularView<Eigen::Lower>();
				m_res = cons.getResidualM();
				
				m_CGt = m_C.selfadjointView<Eigen::Lower>() * m_G.transpose();
				Rtemp = m_G * m_CGt;
				if ((weight) && ((m_V).diagonal().array() != 0).all()) {

			//			cout << "+++++++++++++++++++++++++++++++++++++++++"  << cons.Name() << endl;
						const Eigen::Matrix < double, -1, -1, 0, 7, 7 > weightedV  =
								weight * (m_V).selfadjointView<Eigen::Lower>();
			//			cout << m_V << endl;
						m_R = Rtemp + weightedV;

				} else {
						m_R = Rtemp.triangularView<Eigen::Lower>();
				}


				RInvtemp = m_R.selfadjointView<Eigen::Lower>();
				m_Rinverse = RInvtemp.inverse();
				if (!m_Rinverse.allFinite()) { return ErrCode(ErrCode::Status::inversionerror); }
				m_K = m_CGt * m_Rinverse.selfadjointView<Eigen::Lower>();
				return ErrCode(ErrCode::Status::success);
		}

#endif

		void KalmanCalculator::updateState(FitParams &fitparams)
		{
				fitparams.getStateVector() -= (m_K * m_res.transpose()).transpose();
		//		m_res = (m_G*(m_K * m_res.transpose())).transpose();
				m_chisq = m_res * m_Rinverse.selfadjointView<Eigen::Lower>() * m_res.transpose();
				int m_debug = 0;
				if(m_debug == 5){
				cout << "residual x " << endl;
				cout << m_res.transpose() << endl;
				cout << "R : " << endl;
				cout << RInvtemp << endl;
				cout << "Rinverse " << endl;
				cout << m_Rinverse << endl;
				cout << "R*R^-1" << endl;
				cout << RInvtemp * m_Rinverse << endl;
		//		for(int i = 0; i < m_stateDim; i++){
		//				cout << (m_K * m_res.transpose())(i) << "			" << fitparams.getStateVector()(i) << endl; 
		//		}
				cin.get();
				cout << "chisq : " << m_chisq << endl;
				cin.get();
				}
			//	m_chisq = m_res * m_Rinverse.selfadjointView<Eigen::Lower>() * m_res.transpose();
		}



				void KalmanCalculator::updateCovariance(FitParams &fitparams)
				{
						Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE > fitCov  =
								fitparams.getCovariance().triangularView<Eigen::Lower>();

						Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE > GRinvGt =
								m_G.transpose() * m_Rinverse.selfadjointView<Eigen::Lower>() * m_G;

						//fitcov is sym so no transpose needed (not that it would have runtime cost)
						Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE > deltaCov  =
								fitCov.selfadjointView<Eigen::Lower>() * GRinvGt * fitCov.selfadjointView<Eigen::Lower>();

						Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE > delta =
								fitCov - deltaCov;

						fitparams.getCovariance().triangularView<Eigen::Lower>() = delta.triangularView<Eigen::Lower>();

				}//end function




#define SKIP008
#ifndef SKIP008
		void KalmanCalculator::updateState(FitParams& fitparams, FitParams& oldfitparams)
		{
				Eigen::Matrix < double, -1, 1, 0, 7, 1 > res_prime =
						m_res + m_G * (fitparams.getStateVector() - oldfitparams.getStateVector());
				fitparams.getStateVector() = oldfitparams.getStateVector() -  m_K * res_prime;
				m_chisq = res_prime.transpose() * m_Rinverse.selfadjointView<Eigen::Lower>() * res_prime;
		}

	//	TREEFITTER_NO_STACK_WARNING
#endif


}
