#include "PathHelper.h"

std::string Common::Helpers::PathHelper::GetUnixPath(std::string path)
{
	auto retPath = path;
	std::replace(retPath.begin(), retPath.end(), '\\', '/');
	return retPath;
}
