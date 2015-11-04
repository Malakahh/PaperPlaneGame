#include "WeightedRandomizer.h"


Game::WeightedRandomizer::WeightedRandomizer(const int* w, const int l) : weights(w), length(l)
{
	//Calculate total weight
	int totalWeight = 0;
	for (int i = 0; i < length; i++)
	{
		totalWeight += w[i];
	}

	//Set up distribution for randomization
	distribution = std::uniform_int_distribution<int>(0, totalWeight);
}

Game::WeightedRandomizer::~WeightedRandomizer()
{
}

int Game::WeightedRandomizer::getRandomIndex()
{
	int roll = distribution(generator);
	int weightProgression = 0;

	for (int i = 0; i < length; i++)
	{
		weightProgression += weights[i];
		if (roll <= weightProgression)
		{
			return i;
		}
	}

	return -1;
}
