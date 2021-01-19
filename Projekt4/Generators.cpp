#include "Generators.h"
#include <cmath>


Generators::Generators(const double source) {
	double creator_x;
	g_x_ = source;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 1000000; j++) {
			creator_x = UniformDistribution(kGeometric);
		}
		switch (i){
		case 0:
			u_x_ = creator_x;
			break;
		case 1:
			e_P_x_ = creator_x;
			break;
		case 2:
			e_L_x_ = creator_x;
			break;
		case 3:
			e_Z_x_ = creator_x;
			break;
		case 4:
			n_x_ = creator_x;
			break;
		case 5:
			g_x_ = creator_x;
			break;
		default:
			break;
		}
	}
}

double Generators::UniformDistribution(const TypeDistribution type_distribution) {
	switch (type_distribution) {
	case kUniform:
		x_ = u_x_;
		break;
	case kPLambda:
		x_ = e_P_x_;
		break;
	case kLLambda:
		x_ = e_L_x_;
		break;
	case kZLambda:
		x_ = e_Z_x_;
		break;
	case kGeometric:
		x_ = g_x_;
		break;
	case kNormal:
		x_ = n_x_;
		break;
	default:
		break;
	}
	const double h = x_ / q_;
	x_ = a_*fmod(x_, q_) - h*r_;
	if (x_ < 0)
		x_ += (two_31_ - 1);
	switch (type_distribution) {
	case kUniform:
		u_x_ = x_;
		break;
	case kPLambda:
		e_P_x_ = x_;
		break;
	case kLLambda:
		e_L_x_ = x_;
		break;
	case kZLambda:
		e_Z_x_ = x_;
		break;
	case kGeometric:
		g_x_ = x_;
		break;
	case kNormal:
		n_x_ = x_;
		break;
	default:
		break;
	}
	return x_ / (two_31_ - 1);
}

double Generators::UniformDistributionMaxMin(const int max, const int min) {
	return (UniformDistribution(kUniform)*(max-min))+min;
}

double Generators::ExponentialDistribution(const double lambda) {
	return -pow(1 / lambda, -1)*log(UniformDistribution(kExponential));
}

int Generators::GeometricDistribution() {
	int i = 0;
	do {
		i++;
	} while (UniformDistribution(kGeometric) < w_);	
	return i;
}

double Generators::NormalDistribution() {
	double first_draw;
	double second_draw;
	double x;

	do
	{
		first_draw = UniformDistribution(kNormal);
		second_draw = UniformDistribution(kNormal);
		x = -log(first_draw);
	} while (!(second_draw <= exp(-pow(x - 1, 2) / 2)));

	if (UniformDistribution(kNormal) < 0.5)
		x = x * -1.0;

	return x * variance_ew_ + mean_e_;
}

double Generators::CreateSeeds() const{
	return x_ ;
}