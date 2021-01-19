#pragma once
#include "Enum.h"
class UnitOfBlood
{
public:

	UnitOfBlood() = default;
	UnitOfBlood(TypeBlood type, double system_time);
	~UnitOfBlood() = default;

	double ReturnBloodTime() const;

private:
		
	double blood_time_;		// czas przydatnoœci krwi
	const double donor_blood_ = 35000.0;
	const double delivery_blood_ = 20000.0;
};

