#include <iostream>

#include "BloodDonationPoint.h"

BloodDonationPoint::BloodDonationPoint(const int n, const int q, const int r, const bool if_step_work, const int type_statistic)
	:N_( n ), Q_( q ), R_( r ), if_step_work_(if_step_work), type_statistic_(type_statistic)
{

}

////  FUNKCJE DOTYCZ¥CE KOLEJKI PACJENTÓW /////

bool BloodDonationPoint::IfEmptyPatientQueue() const
{
	if (patient_queue_.empty())
		return true;
	return false;
	
}

void BloodDonationPoint::PushPatientQueue(Patient *patient)
{
	patient_queue_.push(patient);
	plus_patient_++;	//Dodanie pacjenta do ubs³u¿onych w statystykach
	if (system_time_ > start_time_)
		statistic_patient_++;			//Jeœli po czasie pocz¹tkowym to zbieranie statystyk
}

////  FUNKCJE DOTYCZ¥CE LISTY KRWI /////

bool BloodDonationPoint::IfEmptyBloodList() const
{
	if (blood_list_.empty())
		return true;
	return false;
}

int BloodDonationPoint::SizeBloodList() const
{
	return (int)blood_list_.size();
}

////  FUNKCJE DOTYCZ¥CE KALENDARZA ZDARZEÑ /////

void BloodDonationPoint::PushCalendar(Event *event) //Dodanie zdarzenia
{
	if (calendar_.empty())
		calendar_.push_front(event);
	else
	{
		for (std::list<Event*>::iterator it = calendar_.begin(); it != calendar_.end(); ++it)
		{
			if ((*it)->ReturnEventTime() > event->ReturnEventTime())
			{
				calendar_.insert(it, event);
				return;
			}
		}
		calendar_.push_back(event);
	}
}

void BloodDonationPoint::PopCalendar() //Usuniêcie zdarzenia
{
	calendar_.pop_front();	//usuniêcie zdarzenia obs³u¿onego
}

void BloodDonationPoint::NextCalendar() //kolejne zdarzenie z kalendarza
{
	calendar_.front()->Execute(); //Wywo³anie funkcji;
}

void BloodDonationPoint::NextSystemTime() // Zmiana czasu systemowego
{
	system_time_ = calendar_.front()->ReturnEventTime(); // zmiana czasu systemowego
}

////  FUNKCJE DOTYCZ¥CE USUNIÊCIA/DODANIA PACJENT I KRWI /////

bool BloodDonationPoint::BloodDeletePatient()	//jêsli false to nie uda³o siê usun¹æ i trzeb wys³aæ awaryje zg³oszenie
{
	if (patient_queue_.front()->ReturnCollectedBlood() <= blood_list_.size())			//sprawdzenie czy jest mo¿liwe pobranie krwi (wywo³ane na pierwszym z kolejki funkcje zwrócenia zu¿ytych jednostek krwi)
	{
		while ((patient_queue_.size()!=0) && (patient_queue_.front()->ReturnCollectedBlood() <= blood_list_.size()))
		{
			for (int i = 0; i < patient_queue_.front()->ReturnCollectedBlood(); i++)		//jest mo¿liwe, wiêc pobranie odpowiedniej iloœci krwi
			{
				blood_list_.pop_front();
				//std::cout << "Usunieto krew" << std::endl;
			}
			patient_queue_.pop();						// usuniêcie pacjenta z pocz¹tku kolejki
			//std::cout << "Usunieto pacjenta" << std::endl;
		}
		return true;
	}
	else											//wys³anie zamówienia awaryjnego
	{
		if (system_time_ > start_time_)
			statistic_Q_++;		//Jeœli po czasie pocz¹tkowym to zbieranie statystyk

		if (flag_Q_)
		{
			//std::cout << "Wyslano juz zamowienie" << std::endl;
			return true;
		}
		else
		{
			flag_Q_ = true;
			//std::cout << "Zlozenie awaryjnego zamowienia" << std::endl;
			return false;
		}
	}	
}

void BloodDonationPoint::BloodDeleteRecycling()
{
	//Sprawdzenie na liœcie czy trzeba nadal usun¹æ krew czy nie
	if (!blood_list_.empty()) {
		while (blood_list_.front()->ReturnBloodTime() < system_time_)
		{
			blood_list_.pop_front();
			recycling_blood_++;
			if (blood_list_.empty())
				return;
		}
	}
}

void BloodDonationPoint::AddBlood(int number_blood, TypeBlood type_blood)
{
	for (int i = 0; i < number_blood; i++)
	{
		plus_blood_++;		//dodanie krwi do statystyk
		UnitOfBlood *unit_of_blood = new UnitOfBlood(type_blood, system_time_);
		if (blood_list_.empty())
			blood_list_.push_front(unit_of_blood);
		else
		{
			for (std::list<UnitOfBlood*>::iterator it = blood_list_.begin(); it != blood_list_.end(); ++it)
			{
				if ((*it)->ReturnBloodTime() > unit_of_blood->ReturnBloodTime())
				{
					blood_list_.insert(it, unit_of_blood);
					return;
				}
			}
			blood_list_.push_back(unit_of_blood);
		}
		//std::cout << "Dodano krew" << std::endl;
	}
}

////  FUNKCJE DOTYCZ¥CE ZLECENIA I AWARYJNEGO ZAMÓWIENIA /////

bool BloodDonationPoint::IfSendN()
{
	if ((blood_list_.size() <= R_) && (flag_N_ == false)) {
		flag_N_ = true;
		return true;
	}
	return false;
}

void BloodDonationPoint::SetN()
{
	flag_N_ = false;
}

void BloodDonationPoint::SetQ()
{
	flag_Q_ = false;
}

int BloodDonationPoint::ReturnN() const {
	return N_;
}

int BloodDonationPoint::ReturnQ() const {
	return Q_;
}

double BloodDonationPoint::ReturnSystemTime() const
{
	return system_time_;
}

//// KAMPANIA PROMOCYJNA ////

bool BloodDonationPoint::ReturnPromotionalCampaing() const {
	return if_promotional_campaing_;
}

void BloodDonationPoint::SetFalseCampaing() {
	if_promotional_campaing_ = false;
}

void BloodDonationPoint::SetTrueCampaing() {
	if_promotional_campaing_ = true;
}

/////////////////////////////////////////////////////////
void BloodDonationPoint::wk()
{
	std::cout << "lista krwi ma " << blood_list_.size() << " elementow" <<std::endl;
	std::cout << "lista pacjentow ma " << patient_queue_.size() << " elementow" << std::endl;
	std::cout << "kalendarz ma " << calendar_.size() << " elementow" << std::endl;
	std::cout << "czas sytemowy = " << system_time_ << std::endl;
	std::cout << "czas kolejnego zdarzenia = " << calendar_.front()->ReturnEventTime() << std::endl;
}

bool BloodDonationPoint::IfBreak() const
{
	switch (type_statistic_) {
	case 1:
		if ((system_time_ >= break_time_) || if_step_work_)
			return true;
		return false;
		break;
	case 2:
		if (plus_patient_ >= serve_patient_ || if_step_work_)
			return true;
		return false;
		break;
	case 3:
		if (plus_blood_ >= add_blood_ || if_step_work_)
			return true;
		return false;
		break;
	default:
		break;
	}
	return false;
}

double BloodDonationPoint::ReturnA() {
	A_ = statistic_Q_ / statistic_patient_;
	return A_;
}

double BloodDonationPoint::ReturnPrcentRecyclingBlood() const {
	return recycling_blood_ / plus_blood_;
}

int BloodDonationPoint::ReturnPatientLisy() const {
	return (int)patient_queue_.size();
}

int BloodDonationPoint::ReturnCalendarSize() const {
	return (int)calendar_.size();
}