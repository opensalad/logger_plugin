#pragma once
#include <factory.h>
#include <cstdarg>

namespace ad
{
	/**
	 * \brief This class is used to create a logger instance.
	 */
	class LoggerFactory final : public Factory
	{
	public:
		virtual ~LoggerFactory() = default;
		void* getInstance(char const *uuid, va_list &args) const override;
	};
}
