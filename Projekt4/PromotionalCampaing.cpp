#include "PromotionalCampaing.h"



void PromotionalCampaing::Execute() {

	if (type_campaing_ == kStartCampaing) {
		blood_donation_point_->SetTrueCampaing();

		//zaplanowanie kolejnego zdarzenia promocyjnej akcji
		Event *promotional_campaing_start = new PromotionalCampaing(blood_donation_point_, kStartCampaing, blood_donation_point_->ReturnSystemTime(), gen_->UniformDistributionMaxMin(kMax22k, kMin20k), gen_);
		blood_donation_point_->PushCalendar(promotional_campaing_start);

		//zaplanowanie zdarzenia zakoñczenia promocyjnej akcji
		Event *promotional_campaing_stop = new PromotionalCampaing(blood_donation_point_, kStopCampaing, blood_donation_point_->ReturnSystemTime(), stop_time_campaing_, gen_);
		blood_donation_point_->PushCalendar(promotional_campaing_stop);
	}
	else
		blood_donation_point_->SetFalseCampaing();
	
	//usuniêcie pierwszego z listy
	blood_donation_point_->PopCalendar();
	//Zmiana czasu systemowego
	blood_donation_point_->NextSystemTime();
}

PromotionalCampaing::PromotionalCampaing(BloodDonationPoint *blood_donation_point, const TypeCampaing type_campaing, const double time_system, const double generate_time, Generators *gen)
	:Event(time_system, generate_time),blood_donation_point_(blood_donation_point), gen_(gen), type_campaing_(type_campaing)
{
}

