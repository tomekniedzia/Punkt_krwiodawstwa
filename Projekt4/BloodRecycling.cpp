#include <iostream>

#include "BloodRecycling.h"
#include "BloodDelivery.h"

void BloodRecycling::Execute() {

	//std::cout << "Zdarzenie usuniêcia krwi " << std::endl << std::endl;
	
	blood_donation_point_->BloodDeleteRecycling();		//usuwa przeterminowan¹ jednostkê krwi
	
	if (blood_donation_point_->IfSendN())		//sprawdzenie czy trzeba wys³aæ zlecenie N
	{
		Event *delivery = new BloodDelivery(blood_donation_point_, kNDelivery, blood_donation_point_->ReturnSystemTime(), gen_->ExponentialDistribution(kZLambda), gen_);	//jeœli tak to wysy³a
		blood_donation_point_->PushCalendar(delivery); //dodanie zdarzenia do kalendarza
	}
	

	//std::cout << "Usuniêcie przeterminowanej krwi z listy krwi" << std::endl;

	if (blood_donation_point_->IfBreak())
		return;

	blood_donation_point_->PopCalendar();
	blood_donation_point_->NextSystemTime();

}

BloodRecycling::BloodRecycling(BloodDonationPoint *blood_point, const double time_system, const TypeBlood type_blood, Generators *gen)
	:Event(time_system, type_blood), blood_donation_point_(blood_point), gen_(gen)
{

}

