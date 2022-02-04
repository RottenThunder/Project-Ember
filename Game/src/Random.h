#pragma once
#include <stdint.h>

class Random
{
public:
	uint8_t GenerateBinaryValue();
	uint8_t GenerateU8BitValue(uint8_t min = 0, uint8_t max = 0);
};