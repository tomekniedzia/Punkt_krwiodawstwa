#pragma once
#include "Enum.h"

class Generators
{
public:

	Generators() = default;
	Generators(double source);
	~Generators() = default;

	double UniformDistribution(TypeDistribution type_distribution);
	double UniformDistributionMaxMin(int max, int min);
	double ExponentialDistribution(double lambda);
	int GeometricDistribution();
	double NormalDistribution();
	double CreateSeeds() const;
	

private:

	double x_;
	
	//UNIFORM
	double u_x_;	
	const int two_31_ = 2147483648;
	const int a_ = 16807;
	const double q_ = 127773;
	const int r_ = 2836;

	//EXPONENTIAL

	double e_P_x_;
	double e_L_x_;
	double e_Z_x_;

	//GEOMETRIC

	double g_x_;
	const double w_ = 0.20;

	//NORMAL

	double n_x_;
	const double mean_e_ = 500;
	const double variance_ew_ = 0.1;

};

