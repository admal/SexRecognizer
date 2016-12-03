#pragma once
#include "IApplicationContext.h"
namespace Common
{
	class IStrategy
	{
	public:
		virtual ~IStrategy(){}

		virtual void Execute(IApplicationContext* context) =0;
	};
}
