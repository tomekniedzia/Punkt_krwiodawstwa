#include <iostream>

#include "BloodDelivery.h"
#include "BloodRecycling.h"

void BloodDelivery::Execute() {

	//std::cout << "Zdarzenie pojawienia siê krwi " << std::endl << std::endl;
	
	//dodaj do listy krwi odpowiedni¹ liczbê przyby³ych jednostek krwi z czasem ich przydatnoœci i zale¿noœci¹ czy to N cy Q
	if (type_delivery_ == kNDelivery)
		blood_donation_point_->AddBlood(blood_donation_point_->ReturnN(), kDelivery);
	else 
		blood_donation_point_->AddBlood(blood_donation_point_->ReturnQ(), kDelivery);

	Event *blood_recycling = new BloodRecycling(blood_donation_point_, blood_donation_point_->ReturnSystemTime(), kDelivery, gen_);
	blood_donation_point_->PushCalendar(blood_recycling);

	//ustawianie flagi na false (w przypadku zlecenia lub awaryjnego zamówienia)
	if (type_delivery_ == kNDelivery)
		blood_donation_point_->SetN();
	else if (type_delivery_ == kQDelivery)
		blood_donation_point_->SetQ();
	else
		std::cout << "Zly typ dostawy" << std::endl;

	//Jeœli kolejka pacjentów nie jest pusta to po dostawie krwi usuwamy pacjenta
	if (!blood_donation_point_->IfEmptyPatientQueue())
	{
		blood_donation_point_->BloodDeletePatient();
		if (blood_donation_point_->IfSendN())		//sprawdzenie czy trzeba wys³aæ zlecenie N
		{
			Event *delivery = new BloodDelivery(blood_donation_point_, kNDelivery, blood_donation_point_->ReturnSystemTime(), gen_->ExponentialDistribution(kZLambda) ,gen_);	//jeœli tak to wysy³a
			blood_donation_point_->PushCalendar(delivery);
		}
	}

	if (blood_donation_point_->IfBreak())
		return;

	blood_donation_point_->PopCalendar();
	blood_donation_point_->NextSystemTime();
}

BloodDelivery::BloodDelivery(BloodDonationPoint *blood_point, const TypeDelivery type_delivery, const double time_system, const double generate_time, Generators *gen)
	:Event (time_system, generate_time), blood_donation_point_(blood_point), type_delivery_(type_delivery), gen_(gen)
{
}

