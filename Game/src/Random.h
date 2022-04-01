#pragma once
#include <stdint.h>

class Random
{
public:
	static uint8_t GenerateBinaryValue();
	static uint8_t GenerateU8BitValue(uint8_t min, uint8_t max);
	static uint16_t GenerateU16BitValue(uint16_t min, uint16_t max);
	static uint32_t GenerateU32BitValue(uint32_t min, uint32_t max);
};