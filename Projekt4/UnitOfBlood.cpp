#include "UnitOfBlood.h"



UnitOfBlood::UnitOfBlood(TypeBlood type, double system_time)
{
	switch (type) {
	case kDonor:		//Jeœli krew od dawcy (d³u¿szy czas przedatnoœci)
		blood_time_ = system_time + donor_blood_;
		break;
	case kDelivery:		//Jeœli krew z zlecenie/awaryjnego zg³oszenia (krótszy czas przydatnoœci)
		blood_time_ = system_time + delivery_blood_;
		break;
	}	
}

double UnitOfBlood::ReturnBloodTime() const
{
	return blood_time_;
}

