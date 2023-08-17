#include "Logger.h"
#include <iostream>
#include "Core/FileIO.h"

namespace cg
{
	bool Logger::Log(LogLevel logLevel, const std::string& filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case LogLevel::Info:
			*this << "Info: ";
			break;
		case LogLevel::Warning:
			*this << "Warning: ";
			break;
		case LogLevel::Error:
			*this << "Error: ";
			break;
		case LogLevel::Assert:
			*this << "Assert: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << " (" << line << ") ";

		return true;
	}
	
}