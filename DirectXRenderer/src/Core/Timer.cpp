#include "drpch.h"
#include "Timer.h"

using namespace std::chrono;

namespace dr
{
	Timer::Timer() noexcept
	{
		last = steady_clock::now();
	}

	float Timer::Mark() noexcept
	{
		const auto old = last;
		last = steady_clock::now();
		const duration<float> frameTime = last - old;

		m_Time = frameTime.count();

		return frameTime.count();
	}

	float Timer::Peek() const noexcept
	{
		return duration<float>(steady_clock::now() - last).count();
	}


}
