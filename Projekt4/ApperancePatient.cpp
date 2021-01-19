#include <iostream>

#include "ApperancePatient.h"
#include "BloodDonationPoint.h"
#include "Patient.h"
#include "BloodDelivery.h"


void ApperancePatient::Execute() {

	//std::cout << "Zdarzenie pojawienia siê pacjenta " << std::endl << std::endl;

	Patient *patient = new Patient();
	
	patient->GenerateCollectedBlood(gen_);		//generacja liczby jednostek krwi zuzytych przez pacjenta

	blood_donation_point_->PushPatientQueue(patient); //jeœli da siê usun¹æ krew to usuwa i zdejnumje pacjenta, jeœli nie to go zosatwia w kolejce
	if (!blood_donation_point_->BloodDeletePatient()) //jeœli zwróci true to usuniêto, a jeœli false to trzeba wys³aæ awaryjne zamówienie
	{
		Event *delivery = new BloodDelivery(blood_donation_point_, kQDelivery, blood_donation_point_->ReturnSystemTime(),gen_->NormalDistribution() ,gen_);
		blood_donation_point_->PushCalendar(delivery);
	}
	
	if (blood_donation_point_->IfSendN())		//sprawdzenie czy trzeba wys³aæ zlecenie N
	{
		Event *delivery = new BloodDelivery(blood_donation_point_, kNDelivery, blood_donation_point_->ReturnSystemTime(), gen_->ExponentialDistribution(kZLambda), gen_);	//jeœli tak to wysy³a
		blood_donation_point_->PushCalendar(delivery);
	}

	//zaplanuj pojawienie siê kolejnego pacjenta
	Event *apperance_patient = new ApperancePatient(blood_donation_point_, blood_donation_point_->ReturnSystemTime(), gen_);
	//Dodanie zdarzenie do kalendarza zdarzeñ
	blood_donation_point_->PushCalendar(apperance_patient);
	
	//sprawdzenie czy warunek zakoñczenia symulacji (lub krokowo) spe³niony
	if (blood_donation_point_->IfBreak())
		return;

	
	//usuniêcie pierwszego z listy
	blood_donation_point_->PopCalendar();
	//Obs³uga kolejnego zdarzenia
	blood_donation_point_->NextSystemTime();

	
}

ApperancePatient::ApperancePatient(BloodDonationPoint *blood_point, const double time_system, Generators *gen)
	:Event(time_system, gen->ExponentialDistribution(kPLambda)), blood_donation_point_(blood_point), gen_(gen)
{

}

