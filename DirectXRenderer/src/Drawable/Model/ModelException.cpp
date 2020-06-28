#include "drpch.h"
#include "ModelException.h"


namespace dr
{
	ModelException::ModelException(int line, const char* file, std::string note) noexcept
		:
		DrException(line, file),
		note(std::move(note))
	{}
	
	const char* ModelException::what() const noexcept
	{
		std::ostringstream oss;
		oss << DrException::what() << std::endl
			<< "[Note] " << GetNote();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}
	
	const char* ModelException::GetType() const noexcept
	{
		return "Dr Model Exception";
	}
	
	const std::string& ModelException::GetNote() const noexcept
	{
		return note;
	}
}