#pragma once

#include <queue>
#include <list>

#include "Patient.h"
#include "UnitOfBlood.h"
#include "Event.h"
#include "Enum.h"


class BloodDonationPoint
{
public:

	BloodDonationPoint() = default;
	BloodDonationPoint(int n, int q, int r, bool if_step_work, int type_statistic);
	~BloodDonationPoint() = default;


	bool IfEmptyPatientQueue() const;			//Czy pusta kolejka
	void PushPatientQueue(Patient *patient);

	bool IfEmptyBloodList() const;			//Czy pusta kolejka
	int SizeBloodList() const;

	void PushCalendar(Event *event);	//dodanie do kalendarza
	void PopCalendar();					//usuiniêcie z kalendarza
	void NextCalendar();
	void NextSystemTime();				//zmiana czasu systemowego

	bool BloodDeletePatient();				//Usuniêcie krwi - dorobiæ sprawdzenie czy w ogóle siê da usun¹c krew!!!
	void BloodDeleteRecycling();
	
	//Napisane dodatkowo do pêtli
	void AddBlood(int number_blood, TypeBlood type_blood);

	bool IfSendN();

	void SetN();
	void SetQ();
	int ReturnN() const;
	int ReturnQ() const;

	double ReturnSystemTime() const;

	///// KAMPANIA PROMOCYJNA //////

	bool ReturnPromotionalCampaing() const;
	void SetFalseCampaing();
	void SetTrueCampaing();

	//////DODATKOWE DO ZADANIA I OGL¥DANIA CO SIÊ DZIEJE//////
	void wk();
	bool IfBreak() const;

	double ReturnA();
	double ReturnPrcentRecyclingBlood() const;
	int ReturnPatientLisy() const;
	int ReturnCalendarSize() const;

private:

	const int N_;						//liczba reprezentuj¹ca krew przychodz¹c¹ z zlecenia
	const int Q_;						//liczba reprezentuj¹ca krew przychodz¹c¹ z awaryjnego zamówienia
	const int R_;						//poziom reprezentuj¹cy liczbê jednostek krwi po którym nastêpuje wys³anie zlecenia na N nowych jednostek krwi

	bool flag_N_ = false;				//flagi mówi¹ce o tym czy zosta³o ju¿ z³o¿one zlecenie/awaryjne zamówienie
	bool flag_Q_ = false;

	double system_time_ = 0;
	double break_time_ = 10000000;
	bool if_step_work_;

	bool if_promotional_campaing_ = false;

	////////////////////////////////////////DO ZAD 4 (STATYSTYKI)///////////////////

	int type_statistic_;
	const double start_time_ = 2000000;
	const int serve_patient_ = 20000;	//ob³u¿eni pacjenci do breaka
	int plus_patient_;					//zmienna gdzie bêd¹ zbierani pacjenci
	const int add_blood_ = 1000;		//Dodana krew do break
	int plus_blood_;					// zmienna gdzie bêdzie zbierana krew
	
	//////////////Prawdopodobieñstwo A/////////////
	
	double A_ = 0;							//prawdopodobieñstwo A
	double statistic_patient_ = 0;			//s³u¿¹ca do wyliczenia prawdopodobieñstwa A
	double statistic_Q_ = 0;

	////////////Procent krwi zutylizowanej///////
	
	double recycling_blood_ = 0;

	std::queue<Patient*> patient_queue_;			//kolejka pacjentow
	std::list<UnitOfBlood*> blood_list_;			//lista krwi
	std::list<Event*> calendar_;					//kalendarz zdarzeñ
};
