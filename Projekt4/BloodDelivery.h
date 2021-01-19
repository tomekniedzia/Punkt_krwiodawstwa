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
	
	TypeDelivery type_delivery_; //zmienna m�wi�ca o typie dostawy je�li 1 to awaryjne, je�li 0 to zlecenie
	Generators *gen_;
	
};

