#include <iostream>

#include "ApperancePatient.h"
#include "BloodDonationPoint.h"
#include "Patient.h"
#include "BloodDelivery.h"


void ApperancePatient::Execute() {

	//std::cout << "Zdarzenie pojawienia si� pacjenta " << std::endl << std::endl;

	Patient *patient = new Patient();
	
	patient->GenerateCollectedBlood(gen_);		//generacja liczby jednostek krwi zuzytych przez pacjenta

	blood_donation_point_->PushPatientQueue(patient); //je�li da si� usun�� krew to usuwa i zdejnumje pacjenta, je�li nie to go zosatwia w kolejce
	if (!blood_donation_point_->BloodDeletePatient()) //je�li zwr�ci true to usuni�to, a je�li false to trzeba wys�a� awaryjne zam�wienie
	{
		Event *delivery = new BloodDelivery(blood_donation_point_, kQDelivery, blood_donation_point_->ReturnSystemTime(),gen_->NormalDistribution() ,gen_);
		blood_donation_point_->PushCalendar(delivery);
	}
	
	if (blood_donation_point_->IfSendN())		//sprawdzenie czy trzeba wys�a� zlecenie N
	{
		Event *delivery = new BloodDelivery(blood_donation_point_, kNDelivery, blood_donation_point_->ReturnSystemTime(), gen_->ExponentialDistribution(kZLambda), gen_);	//je�li tak to wysy�a
		blood_donation_point_->PushCalendar(delivery);
	}

	//zaplanuj pojawienie si� kolejnego pacjenta
	Event *apperance_patient = new ApperancePatient(blood_donation_point_, blood_donation_point_->ReturnSystemTime(), gen_);
	//Dodanie zdarzenie do kalendarza zdarze�
	blood_donation_point_->PushCalendar(apperance_patient);
	
	//sprawdzenie czy warunek zako�czenia symulacji (lub krokowo) spe�niony
	if (blood_donation_point_->IfBreak())
		return;

	
	//usuni�cie pierwszego z listy
	blood_donation_point_->PopCalendar();
	//Obs�uga kolejnego zdarzenia
	blood_donation_point_->NextSystemTime();

	
}

ApperancePatient::ApperancePatient(BloodDonationPoint *blood_point, const double time_system, Generators *gen)
	:Event(time_system, gen->ExponentialDistribution(kPLambda)), blood_donation_point_(blood_point), gen_(gen)
{

}

