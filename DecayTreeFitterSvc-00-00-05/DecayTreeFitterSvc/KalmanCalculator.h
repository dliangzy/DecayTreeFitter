/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/


#ifndef KALMAN_CALCULATOR_H
#define KALMAN_CALCULATOR_H

#include "DecayTreeFitterSvc/ParticleBase.h"
#include "DecayTreeFitterSvc/RecoTrack.h"
#include "DecayTreeFitterSvc/RecoPhoton.h"
#include "DecayTreeFitterSvc/InternalParticle.h"
#include "DecayTreeFitterSvc/RootParticle.h"
#include "DecayTreeFitterSvc/Constraint.h"
#include "Eigen/Core"
#include <stdarg.h>
#include <vector>
#include <Eigen/Dense>
namespace DecayTreeFitter {

		class KalmanCalculator {
				public:

						/** constructor  */
						KalmanCalculator(
										int sizeRes,
										int sizeState
										);

						/** init the kalman machienery */
						ErrCode calculateGainMatrix(
										const FitParams &fitparams,
										const Constraint &cons,
										double weight = 1);




						/** update statevector */


						void updateState(FitParams &fitparams);

						/** update statevector */
				//		void updateState(FitParams &fitparams, FitParams &oldfitparams);

						/** update the statevectors covariance */
						void updateCovariance(FitParams &fitparams);

						/** get chi2 of this iteration */
						double getChiSquare() { return m_chisq;}
						/**  get chi2 */
						double chisq() const { return m_chisq ; }

						/** get dimension of the constraint */
						double getConstraintDim() { return m_constrDim; }


#define SKIP007
#ifndef SKIP007

						void updateState(DecayTree *decayTree);

						/** update statevector */
						void updateState(DecayTree *decayTree, DecayTree *oldDecayTree);

						/** update the statevectors covariance */
						void updateCovariance(DecayTree *decayTree);

						/** get chi2 of this iteration */
						double getChiSquare() { return m_chisq;}
						/**  get chi2 */
						double chisq() const { return m_chisq ; }

						/** get dimension of the constraint */
						double getConstraintDim() { return m_constrDim; }
#endif


				private:
						/** dimension of the constraint  */
						int m_constrDim;
						int m_stateDim;

						/**  chi2 */
						double m_chisq;

						/** we know the max sizes of the matrices
						 *  we assume the tree is smaller than MAX_MATRIX_SIZE parameters
						 *  and the largest constraint is the track constraint with 5
						 *
						 *  -> Eigen puts this on the stack
						 *
						 *  Eigen::Matrix < double, col, row, ColMajor, maxCol, maxRow>
						 *  -1 = Eigen::Dynamic
						 *   0 = Eigen::ColMajor (don't touch)
						 * */

						/** vector holding the residuals */
						Eigen::Matrix < double, 1, -1, 1, 1, MAX_MATRIX_SIZE> m_res;

						/** G former H, transforms covraince of {residuals}<->{x,p,E} */
						Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE > m_G;
						Eigen::Matrix < double, -1, -1, 0, 7, 7 > m_V;
						Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE > m_C;

						/** R residual covariance */
						Eigen::Matrix < double, -1, -1, 0, 7, 7 > m_R;

						/** R inverse */
						Eigen::Matrix < double, -1, -1, 0, 7, 7 > m_Rinverse;

						/** K kalman gain matrix */
						Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE > m_K;

						/** C times G^t  */
						Eigen::Matrix < double, -1, -1, 0, MAX_MATRIX_SIZE, MAX_MATRIX_SIZE > m_CGt;
						Eigen::Matrix < double, -1, -1, 0, 7, 7> Rtemp;
						Eigen::Matrix < double, -1, -1, 0, 7, 7> RInvtemp;

		};


} // end namespace TreeFitter
#endif

