#pragma once
#include "Core.h"

namespace Ember
{
	class EMBER_API DeltaTime
	{
	private:
		double Time;
	public:
		DeltaTime(double time = 0.0f)
			: Time(time) {}

		operator double() { return Time; }

		double GetSeconds() const { return Time; }
		double GetMilliseconds() const { return Time * 1000.0f; }
	};
}