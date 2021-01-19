#pragma once

#include "Event.h"
#include "BloodDonationPoint.h"
#include "Generators.h"

class ApperancePatient:public Event		//klasa reprezentuj¹ca dodanie pacjenta
{
public:
	ApperancePatient() = default;
	ApperancePatient(BloodDonationPoint *blood_point, double time_system, Generators *gen);
	virtual ~ApperancePatient() = default;

	virtual void Execute() override;

private:
	BloodDonationPoint *blood_donation_point_;
	Generators *gen_;

};
