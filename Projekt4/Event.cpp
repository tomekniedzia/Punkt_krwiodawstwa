
#include "Event.h"



Event::Event(double system_time, double generate_time)
{
	//generator czasu pojawienia siê zdarzenia
	event_time_ = generate_time + system_time;
	//std::cout << "event time = " << event_time_ << std::endl;
}

Event::Event(double system_time, TypeBlood type_blood)
{
	switch (type_blood){
	case kDonor:		//Jeœli krew od dawcy (d³u¿szy czas przedatnoœci)
		event_time_ = system_time + donnor_blood_;
		break;
	case kDelivery:		//Jeœli krew z zlecenie/awaryjnego zg³oszenia (krótszy czas przydatnoœci)
		event_time_ = system_time + delivery_blood_;
		break;
	}		
}


double Event::ReturnEventTime() const
{
	return event_time_;
}