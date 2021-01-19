#pragma once

enum TypeBlood {
	kDonor = 0,
	kDelivery,
};

enum TypeDelivery
{
	kNDelivery = 0,
	kQDelivery,
};

enum TypeDistribution {
	kUniform = 0,
	kExponential,
	kGeometric,
	kNormal,
	kPLambda = 250,
	kLLambda = 950,
	kZLambda = 1700,
};

enum TypeCampaing {
	kStartCampaing = 0,
	kStopCampaing,
};

enum TypeMaxMin {
	kMin100 = 100,
	kMax200 = 200,
	kMin20k = 20000,
	kMax22k = 22000, 

};