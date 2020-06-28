#pragma once
#include "Core/Graphics.h"
#include "Job.h"
#include <vector>
namespace dr
{
	class Pass
	{
	public:
		void Accept(Job job) noexcept
		{
			jobs.push_back(job);
		}
		void Execute(Graphics& gfx) const noxnd
		{
			for (const auto& j : jobs)
			{
				j.Execute(gfx);
			}
		}
		void Reset() noexcept
		{
			jobs.clear();
		}
	private:
		std::vector<Job> jobs;
	};
}