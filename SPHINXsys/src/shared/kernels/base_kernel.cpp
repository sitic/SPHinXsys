/**
 * @file 	base_kernel.cpp
 * @author	Luhui Han, Chi ZHang and Xiangyu Hu
 */

#include "base_kernel.h"

namespace SPH
{
	//=================================================================================================//
	Kernel::Kernel(std::string kernel_name)
		: kernel_name_(kernel_name), h_(1.0), inv_h_(1.0) {};
	//=================================================================================================//
	void Kernel::initialize(Real h)
	{
		h_ = h;
		inv_h_ = 1.0 / h;
		if (h <= 0.0)
		{
			std::cout << "\n FAILURE: The Kernel gets a non-positive smoothing length \""
				<< h << "\"!\n";
			std::cout << __FILE__ << ':' << __LINE__ << std::endl;
			exit(1);
		}

		setBasicParameters();
		setDerivativeParameters();
	}
	//=================================================================================================//
	void Kernel::setDerivativeParameters()
	{
		cutoff_radius_ref_ = KernelSize()*h_; 
		factor_dW_1D_ = inv_h_ * factor_W_1D_;
		factor_dW_2D_ = inv_h_ * factor_W_2D_;
		factor_dW_3D_ = inv_h_ * factor_W_3D_;
		factor_d2W_1D_ = inv_h_ * factor_dW_1D_;
		factor_d2W_2D_ = inv_h_ * factor_dW_2D_;
		factor_d2W_3D_ = inv_h_ * factor_dW_3D_;
	}
	//=================================================================================================//
	Real Kernel::W(const Real& r_ij, const Real& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_W_1D_ * W_1D(q);
	}
	//=================================================================================================//
	Real Kernel::W(const Real& r_ij, const Vec2d& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_W_2D_ * W_2D(q);
	}
	//=================================================================================================//
	Real Kernel::W(const Real& r_ij, const Vec3d& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_W_3D_ * W_3D(q);
	}
	//=================================================================================================//
	Real Kernel::dW(const Real& r_ij, const Real& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_dW_1D_ * dW_1D(q);
	}
	//=================================================================================================//
	Real Kernel::dW(const Real& r_ij, const Vec2d& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_dW_2D_ * dW_2D(q);
	}
	//=================================================================================================//
	Real Kernel::dW(const Real& r_ij, const Vec3d& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_dW_3D_ * dW_3D(q);
	}
	//=================================================================================================//
	Real Kernel::d2W(const Real& r_ij, const Real& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_d2W_1D_ * d2W_1D(q);
	}
	//=================================================================================================//
	Real Kernel::d2W(const Real& r_ij, const Vec2d& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_d2W_2D_ * d2W_2D(q);
	}
	//=================================================================================================//
	Real Kernel::d2W(const Real& r_ij, const Vec3d& displacement) const
	{
		Real q = r_ij * inv_h_;
		return factor_d2W_3D_ * d2W_3D(q);
	}
	//=================================================================================================//
	Real Kernel::W(const Real& h_ratio, const Real& r_ij, const Real& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return factor_W_1D_ * W_1D(q) * SmoothingLengthFactor1D(h_ratio);
	}
	//=================================================================================================//
	Real Kernel::W(const Real& h_ratio, const Real& r_ij, const Vec2d& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return factor_W_2D_ * W_2D(q) * SmoothingLengthFactor2D(h_ratio);
	}
	//=================================================================================================//
	Real Kernel::W(const Real& h_ratio, const Real& r_ij, const Vec3d& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return  factor_W_3D_ * W_3D(q) * SmoothingLengthFactor3D(h_ratio);
	}
	//=================================================================================================//
	Real  Kernel::W0(const Real& h_ratio, const Real& point_i)  const
	{
		return factor_W_1D_ * SmoothingLengthFactor1D(h_ratio);
	};
	//=================================================================================================//
	Real Kernel::W0(const Real& h_ratio, const Vec2d& point_i) const
	{
		return factor_W_2D_ * SmoothingLengthFactor2D(h_ratio);
	};
	//=================================================================================================//
	Real Kernel::W0(const Real& h_ratio, const Vec3d& point_i) const
	{
		return factor_W_3D_ * SmoothingLengthFactor3D(h_ratio);
	};
	//=================================================================================================//
	Real Kernel::dW(const Real& h_ratio, const Real& r_ij, const Real& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return factor_dW_1D_ * dW_1D(q) * SmoothingLengthFactor1D(h_ratio);
	}
	//=================================================================================================//
	Real Kernel::dW(const Real& h_ratio, const Real& r_ij, const Vec2d& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return factor_dW_2D_ * dW_2D(q) * SmoothingLengthFactor2D(h_ratio);
	}
	//=================================================================================================//
	Real Kernel::dW(const Real& h_ratio, const Real& r_ij, const Vec3d& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return factor_dW_3D_ * dW_3D(q) * SmoothingLengthFactor3D(h_ratio);
	}
	//=================================================================================================//
	Real Kernel::d2W(const Real& h_ratio, const Real& r_ij, const Real& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return factor_d2W_1D_ * d2W_1D(q) * SmoothingLengthFactor1D(h_ratio);
	}
	//=================================================================================================//
	Real Kernel::d2W(const Real& h_ratio, const Real& r_ij, const Vec2d& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return factor_d2W_2D_ * d2W_2D(q) * SmoothingLengthFactor2D(h_ratio);
	}
	//=================================================================================================//
	Real Kernel::d2W(const Real& h_ratio, const Real& r_ij, const Vec3d& displacement) const
	{
		Real q = r_ij * inv_h_ * h_ratio;
		return factor_d2W_3D_ * d2W_3D(q) * SmoothingLengthFactor3D(h_ratio);
	}
	//=================================================================================================//
	void  Kernel::reduceOnce()
	{
		factor_W_3D_ = factor_W_2D_;
		factor_W_2D_ = factor_W_1D_;
		factor_W_1D_ = 0.0;
		setDerivativeParameters();
	}
	//=================================================================================================//
	void  Kernel::reduceTwice()
	{
		factor_W_3D_ = factor_W_1D_;
		factor_W_2D_ = 0.0;
		factor_W_1D_ = 0.0;
		setDerivativeParameters();
	}
	//=================================================================================================//
}
