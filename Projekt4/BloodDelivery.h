#pragma once

#include "Event.h"
#include "BloodDonationPoint.h"
#include "Enum.h"
#include "Generators.h"

class BloodDelivery :public Event
{
public:

	BloodDelivery() = default;
	BloodDelivery(BloodDonationPoint *blood_point, TypeDelivery type_delivery, double time_system, double generate_time, Generators *gen);
	virtual ~BloodDelivery() = default;

	virtual void Execute() override;

private:
	BloodDonationPoint *blood_donation_point_;
	
	TypeDelivery type_delivery_; //zmienna mówi¹ca o typie dostawy jeœli 1 to awaryjne, jeœli 0 to zlecenie
	Generators *gen_;
	
};

