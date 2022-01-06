#include "GrapherXException.h"

namespace Grapher
{

	GrapherXException::GrapherXException(int line, const char* file)
		:
		Line(line),
		File(file)
	{
	}

	const char* GrapherXException::what() const
	{
		std::ostringstream oss;
		oss << GetType() << "\n\t" << GetOriginString();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}

	const wchar_t* GrapherXException::dis() const
	{
		return nullptr;
	}


	const char* GrapherXException::GetType() const
	{
		return "GrapherX Exception";
	}

	int GrapherXException::GetLine() const
	{
		return Line;
	}

	const std::string& GrapherXException::GetFile() const
	{
		return File;
	}

	std::string GrapherXException::GetOriginString() const
	{
		std::ostringstream oss;
		oss << "\t[File] : " << File << "\n\t"
			<< "[Line] : " << Line << "\n\t";
		return oss.str();
	}
}
