#include "Random.h"
#include <random>

static std::random_device RandomDevice;
static std::mt19937 RandomEngine(RandomDevice());
static std::uniform_int_distribution<uint32_t> UniformDistrubition;

uint8_t Random::GenerateBinaryValue()
{
	return (uint8_t)UniformDistrubition(RandomEngine) % 2;
}

uint8_t Random::GenerateU8BitValue(uint8_t min, uint8_t max)
{
	uint8_t range = max - min;
	return (uint8_t)(UniformDistrubition(RandomEngine) % (range + 1)) + min;
}

uint16_t Random::GenerateU16BitValue(uint16_t min, uint16_t max)
{
	uint16_t range = max - min;
	return (uint16_t)(UniformDistrubition(RandomEngine) % (range + 1)) + min;
}

uint32_t Random::GenerateU32BitValue(uint32_t min, uint32_t max)
{
	uint32_t range = max - min;
	return (uint32_t)(UniformDistrubition(RandomEngine) % (range + 1)) + min;
}