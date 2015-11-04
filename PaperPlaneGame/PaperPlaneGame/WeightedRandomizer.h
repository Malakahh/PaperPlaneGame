#pragma once
#include <vector>
#include <random>

namespace Game
{
	class WeightedRandomizer
	{
	public:
		WeightedRandomizer(const int* w, const int l);
		~WeightedRandomizer();

		int getRandomIndex();

	private:
		const int* weights, length;
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;
	};
}
