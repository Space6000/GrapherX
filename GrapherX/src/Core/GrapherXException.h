#pragma once
#include <exception>
#include <sstream>
#include <string>

namespace Grapher
{
	class GrapherXException : public std::exception
	{
	public:
		GrapherXException(int line, const char* file);
		virtual const char* what() const;
		virtual const wchar_t* dis() const;
		virtual const char* GetType() const;
		int GetLine() const;
		const std::string& GetFile() const;
		std::string GetOriginString() const;
	 
	private:
		int Line;
		std::string File;

	protected:
		mutable std::string whatBuffer;

	};
}

