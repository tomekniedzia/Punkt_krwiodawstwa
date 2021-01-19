#pragma once

#include "Event.h"
#include "BloodDonationPoint.h"
#include "Enum.h"
#include "Generators.h"

class BloodRecycling :public Event
{
public:

	virtual void Execute() override;

	BloodRecycling() = default;
	BloodRecycling(BloodDonationPoint *blood_point, double time_system, TypeBlood type_blood, Generators *gen);
	virtual ~BloodRecycling() = default;

private:
	BloodDonationPoint *blood_donation_point_;
	Generators *gen_;
};
