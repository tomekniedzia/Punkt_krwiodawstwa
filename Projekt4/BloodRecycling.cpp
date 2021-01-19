#include <iostream>

#include "BloodRecycling.h"
#include "BloodDelivery.h"

void BloodRecycling::Execute() {

	//std::cout << "Zdarzenie usuni�cia krwi " << std::endl << std::endl;
	
	blood_donation_point_->BloodDeleteRecycling();		//usuwa przeterminowan� jednostk� krwi
	
	if (blood_donation_point_->IfSendN())		//sprawdzenie czy trzeba wys�a� zlecenie N
	{
		Event *delivery = new BloodDelivery(blood_donation_point_, kNDelivery, blood_donation_point_->ReturnSystemTime(), gen_->ExponentialDistribution(kZLambda), gen_);	//je�li tak to wysy�a
		blood_donation_point_->PushCalendar(delivery); //dodanie zdarzenia do kalendarza
	}
	

	//std::cout << "Usuni�cie przeterminowanej krwi z listy krwi" << std::endl;

	if (blood_donation_point_->IfBreak())
		return;

	blood_donation_point_->PopCalendar();
	blood_donation_point_->NextSystemTime();

}

BloodRecycling::BloodRecycling(BloodDonationPoint *blood_point, const double time_system, const TypeBlood type_blood, Generators *gen)
	:Event(time_system, type_blood), blood_donation_point_(blood_point), gen_(gen)
{

}

