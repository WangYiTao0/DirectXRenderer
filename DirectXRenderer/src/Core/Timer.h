#pragma once
#include <chrono>

namespace dr {

	class Timer
	{
	public:
		Timer() noexcept;
		float Mark() noexcept;
		float Peek() const noexcept;

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		std::chrono::steady_clock::time_point last;
		float m_Time;
	};

}