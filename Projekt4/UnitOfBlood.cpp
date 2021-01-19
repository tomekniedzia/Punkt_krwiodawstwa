#include "UnitOfBlood.h"



UnitOfBlood::UnitOfBlood(TypeBlood type, double system_time)
{
	switch (type) {
	case kDonor:		//Je�li krew od dawcy (d�u�szy czas przedatno�ci)
		blood_time_ = system_time + donor_blood_;
		break;
	case kDelivery:		//Je�li krew z zlecenie/awaryjnego zg�oszenia (kr�tszy czas przydatno�ci)
		blood_time_ = system_time + delivery_blood_;
		break;
	}	
}

double UnitOfBlood::ReturnBloodTime() const
{
	return blood_time_;
}

