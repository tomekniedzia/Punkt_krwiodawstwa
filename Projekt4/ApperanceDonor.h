#pragma once

#include "Event.h"
#include "BloodDonationPoint.h"
#include "Generators.h"

class ApperanceDonor:public Event
{
public:
	virtual void Execute() override;

	ApperanceDonor() = default;
	ApperanceDonor(BloodDonationPoint *blood_point, double time_system, double generate_time, Generators *gen);
	virtual ~ApperanceDonor() = default;

private:
	BloodDonationPoint *blood_donation_point_;
	Generators *gen_;

	double generate_time_;
};
