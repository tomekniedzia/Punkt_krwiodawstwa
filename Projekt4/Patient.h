#pragma once
#include "Generators.h"

class Patient
{
public:

	Patient() = default;
	~Patient() = default;

	void GenerateCollectedBlood(Generators *gen);		//Funkcja generuj¹ca krew pobran¹ przez pacjenta
	int ReturnCollectedBlood() const;

private:

	int collected_blood_;		//krew odebrana pacjentowi
};

