#include <iostream>
#include <fstream>
#include <string>

#include "BloodDonationPoint.h"
#include "Event.h"
#include "ApperanceDonor.h"
#include "ApperancePatient.h"
#include "Generators.h"
#include "PromotionalCampaing.h"

///// D3 //// A1

int main() {

	int if_continue;
	bool work;
	const bool loop_work = true;
	int type_static;

	//// Wczytywanie kolejnych ziaren z pliku
	std::string t;
	std::ifstream myfile("Seeds.txt");
	double seed[30];
	if (myfile.is_open()) {
		for (int i = 0; i < 30; i++) {
			std::getline(myfile, t);
			seed[i] = strtod(t.c_str(), nullptr);
		}
		myfile.close();
	}

	std::cout << "Czy praca krokowa? Wciscnij 1 jesli praca krokowa, 0 jesli praca ciagla " << std::endl;
	std::cin >> work;

	//Dodane 3 mo¿liwoœci zakoñczenie dzia³ania pêtli
	std::cout << "Warunek zakonczenia? 1 jesli czas, 2 jesli liczba pacjentow, 3 jesli liczba dodanej krwi " << std::endl;
	std::cin >> type_static;

	const int N = 150;
	const int Q = 40;
	const int R = 350;

	double A_result = 0;
	double P_blood = 0;
	for (int source_ = 0; source_ < 10; source_++) {

		//// Symulacja w³aœciwa
		BloodDonationPoint *h = new BloodDonationPoint(N, Q, R, work, type_static);
		Generators *gen = new Generators(seed[source_]);
		
		Event *donor = new  ApperanceDonor(h, h->ReturnSystemTime(), gen->ExponentialDistribution(kLLambda), gen);
		h->PushCalendar(donor);
		Event *apperance_patient = new ApperancePatient(h, h->ReturnSystemTime(), gen);
		h->PushCalendar(apperance_patient);
		Event *promotional_campaing = new PromotionalCampaing(h, kStartCampaing, h->ReturnSystemTime(), gen->UniformDistributionMaxMin(kMax22k, kMin20k), gen);
		h->PushCalendar(promotional_campaing);

		///////// Praca krokowa ///////
		while (work)
			{
				std::cout << "Czy kontynuowac? Wciscnij 1 jesli tak " << std::endl;
				std::cin >> if_continue;
				std::cout << std::endl;
				if (if_continue == 1)
				{
					h->NextSystemTime();
					h->NextCalendar();
					h->PopCalendar();
					h->wk();
				}
			}

			//////// Praca ci¹g³a ////////
		if (!work)
		{
			while (loop_work)
			{
				h->NextCalendar();
				if (h->IfBreak())
						break;
			}
						
			h->wk();
			std::cout << " cz¹tkowy Procent zutylizowanej krwii " << h->ReturnPrcentRecyclingBlood() << std::endl << std::endl;
			P_blood = P_blood + h->ReturnPrcentRecyclingBlood();
				
			A_result = A_result + h->ReturnA();
			std::cout << " Prawdopodobienstwo A_cz¹stkowe " << h->ReturnA() << std::endl;
		}
	}

	A_result = A_result / 10;
	P_blood = P_blood / 10;
	std::cout << " Prawdopodobienstwo A " << A_result << std::endl;
	std::cout << " Prawdopodobienstwo utylizacji krwi " << P_blood << std::endl;
	
	std::cout << "koniec" << std::endl;
	while (getchar() != '\n');
	while (getchar() != '\n');
	return 0;
}