#include <iostream>

#include "ApperanceDonor.h"
#include "BloodRecycling.h"

void ApperanceDonor::Execute() {

	//std::cout << "Zdarzenie pojawienia si� dawcy " << std::endl << std::endl;

	blood_donation_point_->AddBlood(1, kDonor);

	//Dodanie zdarzenia przeterminowania krwi
	Event *blood_recycling = new BloodRecycling(blood_donation_point_, blood_donation_point_->ReturnSystemTime(), kDonor, gen_);
	blood_donation_point_->PushCalendar(blood_recycling);
	

	//utworzenie nowego zdarzenia pojawienia si� dawcy (z zale�no�ci od akcji promocyjnej);
	if (blood_donation_point_->ReturnPromotionalCampaing()) {	//Czy akcja promocyjna
		generate_time_ = gen_->ExponentialDistribution(kLLambda) - gen_->UniformDistributionMaxMin(kMax200, kMin100);
		if (0 > generate_time_)
			generate_time_ = 0.01;	//Je�li generowany czas dla pojawienia si� dawcy <0, to pojawienie si� dawcy nast�puje bardzo szybko

		Event *donor = new ApperanceDonor(blood_donation_point_, blood_donation_point_->ReturnSystemTime(), generate_time_, gen_);
		blood_donation_point_->PushCalendar(donor);
	}
	else {
		Event *donor = new ApperanceDonor(blood_donation_point_, blood_donation_point_->ReturnSystemTime(),gen_->ExponentialDistribution(kLLambda), gen_);
		blood_donation_point_->PushCalendar(donor);
	}
	
	if (blood_donation_point_->IfBreak()) {
		return;
	}

	//usuni�cie pierwszego z listy
	blood_donation_point_->PopCalendar();
	//Obs�uga kolejnego zdarzenia
	blood_donation_point_->NextSystemTime();

}	

ApperanceDonor::ApperanceDonor(BloodDonationPoint *blood_point, const double time_system, const double generate_time, Generators *gen)
	:Event(time_system, generate_time), blood_donation_point_(blood_point), gen_(gen)
{

}