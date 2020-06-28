#include "drpch.h"
#include "Job.h"
#include "Drawable/Drawable.h"

namespace dr
{
	Job::Job(const Step* pStep, const Drawable* pDrawable)
		:
		pDrawable(pDrawable),
		pStep(pStep)
	{
	}
	void Job::Execute(Graphics& gfx)const noxnd
	{
		pDrawable->Bind(gfx);
		pStep->Bind(gfx);
		gfx.DrawIndexed(pDrawable->GetIndexCount());
	}
}
