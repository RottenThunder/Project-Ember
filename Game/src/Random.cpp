#include "Random.h"
#include <random>

static std::random_device RandomDevice;
static std::mt19937 RandomEngine(RandomDevice());
static std::uniform_int_distribution<uint16_t> UniformDistrubition;

uint8_t Random::GenerateBinaryValue()
{
	return uint8_t(UniformDistrubition(RandomEngine) % 2);
}