#pragma once
#include <logger.h>

namespace ad
{
	using string_t = char const * const &;
	using map_t = char const ** const &;
	class InvalidLogger : public Logger<string_t, map_t>
	{
	public:
		void log(LogLevel, string_t) override {}
		void setId(string_t) override {}
		void setPattern(string_t) override {}
		void setPatternParam(string_t, string_t) override {}
		string_t id() const override { return ""; }
		string_t pattern() const override { return ""; }
		string_t param(string_t) const override { return ""; }
		map_t paramList() const override { return nullptr; }
		string_t uuid() const override { return "invalid_logger"; }
	};
}
