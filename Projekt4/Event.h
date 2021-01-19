#pragma once
#include "Enum.h"

class Event				//klasa reprezentuj¹ca zdarzenia
{
public:

	Event(double system_time, double generate_time);
	Event(double system_time, TypeBlood type_blood);	//konstruktor go wydarzenia BloodRecycling
	virtual ~Event() = default;

	virtual void Execute() = 0;
	double ReturnEventTime() const;

private:

	double event_time_;
	const int delivery_blood_ = 20000;
	const int donnor_blood_ = 35000;
};

