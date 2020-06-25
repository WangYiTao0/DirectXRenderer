#include "drpch.h"
#include "DrException.h"


namespace dr
{
	DrException::DrException(int line, const char* file) noexcept
		:
		line(line),
		file(file)
	{
	}

	const char* DrException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< GetOriginString();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}

	const char* DrException::GetType() const noexcept
	{
		return "Dr Exception";
	}

	int DrException::GetLine() const noexcept
	{
		return line;
	}

	const std::string& DrException::GetFile() const noexcept
	{
		return file;
	}

	std::string DrException::GetOriginString() const noexcept
	{
		std::ostringstream oss;
		oss << "[File] " << file << std::endl
			<< "[Line] " << line;
		return oss.str();
	}

}
