#pragma once

namespace dr
{
	class ModelProbe
	{
	public:
		virtual ~ModelProbe() {}
		virtual bool PushNode(class Node& node) = 0;
		virtual void PopNode(class Node& node) = 0;
	};
}