#include "Patient.h"



void Patient::GenerateCollectedBlood(Generators *gen)
{
	//fukcja generuj�ca ile krwi zu�yje pacjent zgodnie z rozk�adem
	collected_blood_ = gen->GeometricDistribution();
}

int Patient::ReturnCollectedBlood() const 
{
	return collected_blood_;
}