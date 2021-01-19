#include "Patient.h"



void Patient::GenerateCollectedBlood(Generators *gen)
{
	//fukcja generuj¹ca ile krwi zu¿yje pacjent zgodnie z rozk³adem
	collected_blood_ = gen->GeometricDistribution();
}

int Patient::ReturnCollectedBlood() const 
{
	return collected_blood_;
}