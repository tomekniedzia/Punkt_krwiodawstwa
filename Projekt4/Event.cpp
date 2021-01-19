
#include "Event.h"



Event::Event(double system_time, double generate_time)
{
	//generator czasu pojawienia si� zdarzenia
	event_time_ = generate_time + system_time;
	//std::cout << "event time = " << event_time_ << std::endl;
}

Event::Event(double system_time, TypeBlood type_blood)
{
	switch (type_blood){
	case kDonor:		//Je�li krew od dawcy (d�u�szy czas przedatno�ci)
		event_time_ = system_time + donnor_blood_;
		break;
	case kDelivery:		//Je�li krew z zlecenie/awaryjnego zg�oszenia (kr�tszy czas przydatno�ci)
		event_time_ = system_time + delivery_blood_;
		break;
	}		
}


double Event::ReturnEventTime() const
{
	return event_time_;
}