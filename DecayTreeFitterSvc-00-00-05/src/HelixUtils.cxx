
#include <TMath.h>

#include <TVector3.h>
#include <TVectorD.h>
#include "DecayTreeFitterSvc/HelixUtils.h"
const double Calpha = -0.00299792458;
namespace DecayTreeFitter {


		/* Eight state vector to helix parameters */
		HelixUtils::HelixUtils(		const double d0,
						const double phi0,
						const double omega,
						const double z0,
						const double tanlam,
						const double bfield,
						const double charge){

				m_jacobian = Eigen::Matrix<double, 5, 8>::Zero();
				m_m0 = Eigen::Matrix<double, 1, 5>::Zero();




		}

		/* Eight state vector to helix parameters */
		HelixUtils::HelixUtils( 	const double x,
									const double y,
									const double z __attribute__((unused)),
						const double px,
						const double py,
						const double pz,
						const double bfield,
						const double charge){
				m_jacobian = Eigen::Matrix<double, 5, 8>::Zero();
				m_m0 = Eigen::Matrix<double, 1, 5>::Zero();

				HepPoint3D xyz(x, y, z);
				double bField = VertexFitBField::instance()->getBFieldZ(xyz);
				

				const double alpha = 1.0 / (bfield * TMath::C()) * 1E11; //  using bes3 results
				const double aq = Calpha * bField * charge;

				const double pt = std::hypot(px, py);
				const double pt2 = pt * pt;
				const double pt3 = pt2 * pt;
				const double aq2 = aq * aq;

				const double x2 = x * x;
				const double y2 = y * y;
				const double r  = x2 + y2;

				const double px2 = px * px;
				const double py2 = py * py;

				const double px0 = px + aq * y;
				const double py0 = py - aq * x;


				const double pt02 = px0 * px0 + py0 * py0;
				const double pt0 = std::sqrt(pt02);
				const double sqrt13 = pt0 / pt;

/*
				const double omega = charge / pt;
				const double tanlam = pz / pt;

				const double phi = atan2(py, px);
				const double deltap =  -x*cos(phi) - y*sin(phi);  // delta parallel
				const double deltav =  -y*cos(phi) + x*sin(phi);
				const double A = 2*deltav + omega *(deltap*deltap +deltav*deltav);
				const double U = sqrt(1 + omega*A);
				const double d0 = A / (1 +U);
				const double l = atan2(omega*deltap, 1+omega*deltav);
				const double z0 = z + l * tanlam;

				const double phi0 = atan( - px0/py0);
*/
				const double d0 = - (pt0 - pt) / aq;
	//			const double phi0 = atan2(py0, px0);
				const double phi0 = fmod((4*TMath::Pi())+atan2(0-px-aq*y, py-aq*x), (2*TMath::Pi()));
				const double omega = charge / pt;
				const double J = aq * (x * px + y * py) / (pt0 * pt);
				const double z0 = z - pz * asin( J ) /aq;
				const double tanlam = pz/pt;
				

				m_m0(0) = d0;
				m_m0(1) = phi0; 	/* 0 -> 2Pi */
				m_m0(2) = omega;
				m_m0(3) = z0;
				m_m0(4) = tanlam;

				// D d0 / Dx_i
				//	std::cout << py0 / pt0 << std::endl;
				//	std::cout << -px0 / pt0 << std::endl;
				m_jacobian(0, 0) = (1/aq) * (px / pt - px0 / pt0);
				m_jacobian(0, 1) = (1/aq) * (py / pt - py0 / pt0);
				m_jacobian(0, 2) = 0;
				m_jacobian(0, 3) = 0;
				m_jacobian(0, 4) = py0 / pt0;
				m_jacobian(0, 5) = -px0 / pt0;
				m_jacobian(0, 6) = 0;
				m_jacobian(0, 7) = 0;

				// D phi0 / Dx_i;
				m_jacobian(1, 0) = -py0 / pt02;
				m_jacobian(1, 1) = px0 / pt02;
				m_jacobian(1, 2) = 0;
				m_jacobian(1, 3) = 0;
				m_jacobian(1, 4) = - aq * px0 / pt02;
				m_jacobian(1, 5) = - aq * py0 / pt02;
				m_jacobian(1, 6) = 0;
				m_jacobian(1, 7) = 0;

				// D omega / Dx_i
				m_jacobian(2, 0) = - charge * px / pt3;
				m_jacobian(2, 1) = - charge * py / pt3;
				m_jacobian(2, 2) = 0;
				m_jacobian(2, 3) = 0;
				m_jacobian(2, 4) = 0;
				m_jacobian(2, 5) = 0;
				m_jacobian(2, 6) = 0;
				m_jacobian(2, 7) = 0;

				// D z0 / Dx_i
				m_jacobian(3, 0) = (pz / aq) * (py/pt2 - py0/ pt02);
				m_jacobian(3, 1) = -(pz / aq) * (px/pt2 - px0/ pt02);
				m_jacobian(3, 2) = - (1/ aq) * asin( J ); //pt on num. and denom cancels.
				m_jacobian(3, 3) = 0;
				m_jacobian(3, 4) = -pz * px0 / pt02;
				m_jacobian(3, 5) = -pz * py0 / pt02;
				m_jacobian(3, 6) = 1;
				m_jacobian(3, 7) = 0;

				// D tan lambda / Dx_i
				m_jacobian(4, 0) = -pz * px / pt3;
				m_jacobian(4, 1) = -pz * py / pt3;
				m_jacobian(4, 2) = 1. / pt; 
				m_jacobian(4, 3) = 0;
				m_jacobian(4, 4) = 0;
				m_jacobian(4, 5) = 0;
				m_jacobian(4, 6) = 0;
				m_jacobian(4, 7) = 0;
		}





		Eigen::Matrix<double, 5, 6> HelixUtils::GetCvtMatrix(const double mass, const Eigen::Matrix<double, 1, 5> &helix)  //just suitable for charged tracks
		{
				Eigen::Matrix<double, 6, 5> m;
				double drho    = helix(0);
				double phi0    = helix(1);
				double kappa   = helix(2);
				double kappa2  = kappa * kappa;
				double kappa3  = kappa * kappa2;
				double dz      = helix(3);
				double lambda  = helix(4);
				double lambda2 = lambda * lambda;
				double e       = sqrt( (1+lambda2) / kappa2 + mass * mass );
				double sinphi0 = sin(phi0);
				double cosphi0 = cos(phi0);
				int    q       = (kappa>0) ? 1 : (-1);
				m(0 , 1) = -cosphi0 * q / kappa;
				m(0 , 2) = sinphi0 * q / kappa2;
				m(1 , 1) = -sinphi0 * q / kappa;
				m(1 , 2) = -cosphi0 * q / kappa2;
				m(2 , 2) = -lambda * q / kappa2;
				m(2 , 4) = q / kappa;
				//	m(3 , 2) = -(1+lambda2) / (kappa3 * e);
				//	m(3 , 4) = lambda / (kappa2 * e);
				m(3 , 0) = cosphi0;
				m(3 , 1) = -drho * sinphi0;
				m(4 , 0) = sinphi0;
				m(4 , 1) = drho * cosphi0;
				m(5 , 3) = 1;
				return m.transpose();
		}

		Eigen::Matrix<double, 1, 6> HelixUtils::CvtH2W(const double mass, const Eigen::Matrix<double, 1, 5> &helix)
		{
				double drho    = helix(0);
				double phi0    = helix(1);
				double kappa   = helix(2);
				double dz      = helix(3);
				double lambda  = helix(4);
				double sinphi0 = sin(phi0);
				double cosphi0 = cos(phi0);
				int    q       = (kappa>0) ? 1 : (-1);
				Eigen::Matrix<double, 1, 6> w;
				w(0) = -sinphi0 * q / kappa;
				w(1) = cosphi0 * q / kappa;
				w(2) = lambda * q / kappa;
				//	w(3) = sqrt( (1+lambda*lambda) / (kappa*kappa) + mass * mass );
				w(3) = drho * cosphi0;
				w(4) = drho * sinphi0;
				w(5) = dz;
				return w;
		}


}


