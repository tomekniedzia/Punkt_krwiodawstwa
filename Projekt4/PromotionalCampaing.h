#pragma once

#include "Event.h"
#include "BloodDonationPoint.h"
#include "Enum.h"
#include "Generators.h"

class PromotionalCampaing:public Event
{
public:

	virtual void Execute() override;

	PromotionalCampaing() = default;
	PromotionalCampaing(BloodDonationPoint *blood_donation_point, TypeCampaing type_campaing, double time_system, double generate_time, Generators *gen);
	virtual ~PromotionalCampaing() = default;

private:
	BloodDonationPoint *blood_donation_point_;
	Generators *gen_;

	const int stop_time_campaing_ = 7200;
	TypeCampaing type_campaing_;
};

