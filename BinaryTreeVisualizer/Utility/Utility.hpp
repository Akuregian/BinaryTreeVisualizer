#pragma once

#include <iostream>
#include <chrono>

namespace Utility
{
	class Timer
	{
	public:
		Timer()
		{
			m_StartPoint = std::chrono::high_resolution_clock::now();
		}
		~Timer()
		{
			Stop();
		}

		void Stop()
		{
			auto EndTimePoint = std::chrono::high_resolution_clock::now();
			auto StartTime = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
			auto EndTime = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch().count();
			auto duration = EndTime - StartTime;
			double ms = duration * .001;

			std::cout << duration << "us (" << ms << "ms)\n";
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartPoint;

	};
}