#pragma once
#include <logger.h>

namespace ad
{
	class InvalidLogger : public Logger
	{
	public:
		void log(LogLevel, char const *) const override {}
		void setId(char const *) override {}
		void setPattern(char const *) override {}
		void setPatternParam(char const *, char const *) override {}
		char const* id() const override { return ""; }
		char const* pattern() const override { return ""; }
		char const* param(char const *) const override { return ""; }
		char const** paramList() const override { return nullptr; }
		char const* uuid() const override { return "invalid_logger"; }
	};
}
