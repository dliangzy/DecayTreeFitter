/****************************************************************************\
 *	BOSS (BES Offline Software System)										*
 *	Author: The BESIII Collaboration										*
 *	External Contributor: Liang Liu <liangzy@mail.ustc.edu.cn>				*
 *																			*
 *  This file is licensed under LGPL-3.0, see LICENSE.md.					*
\****************************************************************************/
// HelixUtils.cc

#ifndef HELIX_UTILS_H
#define HELIX_UTILS_H

#include "CLHEP/Matrix/Matrix.h"
#include "TMatrixD.h"
#include "Eigen/Core"
#include "DecayTreeFitterSvc/BField.h"

namespace DecayTreeFitter {

		class HelixUtils {
				public:
						/* Eight state vector to helix parameters */
						HelixUtils( 	const double x,
										const double y,
										const double z __attribute__((unused)),
										const double px,
										const double py,
										const double pz,
										const double bfield,
										const double charge);

						/* helix parameters to eight state vector  */
						HelixUtils(		const double d0,
										const double phi0,
										const double omega,
										const double z0,
										const double tanlam,
										const double bfield,
										const double charge);

						~HelixUtils(){}


						Eigen::Matrix<double, 5, 8> &  getJacobian() {return m_jacobian;}
						const Eigen::Matrix<double, 5, 8> &  getJacobian() const  {return m_jacobian;}
						Eigen::Matrix<double, 1, 5> & getMeasurement() {return m_m0;}
						const Eigen::Matrix<double, 1, 5> & getMeasurement() const  {return m_m0;}





						Eigen::Matrix<double, 5, 6> GetCvtMatrix(const double mass, const Eigen::Matrix<double, 1, 5> &helix);

						Eigen::Matrix<double, 1, 6> CvtH2W(const double mass, const Eigen::Matrix<double, 1, 5> &helix);
				private:
						/* Jacobian Matrix */
						Eigen::Matrix<double, 5, 8>  m_jacobian;
						/* Measurement parameters, helix */
						Eigen::Matrix<double, 1, 5>  m_m0;




		};





} // end namespace TreeFitter
#endif

