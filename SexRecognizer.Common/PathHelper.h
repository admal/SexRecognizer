#pragma once
#include <string>
#include <algorithm>

namespace Common
{
	namespace Helpers
	{
		class PathHelper
		{
		public:
			static std::string GetUnixPath(std::string path);
		};		
	}
}

