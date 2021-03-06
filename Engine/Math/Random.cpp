#include "Random.h"
#include <random>
#include <limits>

namespace jc 
{
	std::default_random_engine g_engine;



	void SeedRandom(unsigned int seed)
	{
		g_engine.seed(seed);
	}

	float Random()//0-1
	{
		std::uniform_real_distribution<float> distribution{ 0,1 };
		return distribution(g_engine);
	}

	float RandomRange(float min, float max)
	{
		std::uniform_real_distribution<float> distribution{ min,max };
		return distribution(g_engine);
	}

	int Randomint()
	{
		std::uniform_int_distribution<int> distribution{ 0,std::numeric_limits<int>::max() };
		return distribution(g_engine);
	}

	int Randomint(int max)
	{
		std::uniform_int_distribution<int> distribution{ 0,max -1};
		return distribution(g_engine);
	}

	int RandomRangeInt(int min, int max)
	{
		std::uniform_int_distribution<int> distribution{ min,max};
		return distribution(g_engine);
	}
}