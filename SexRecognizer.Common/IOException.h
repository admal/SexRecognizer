
#include <exception>

namespace Common
{
	namespace Exceptions
	{
		class DirectoryExistsException : public std::exception
		{
		public:
			const char* what() const override
			{
				return "[DirectoryExistsException] Such directory already exists";
			};
		};

		class DirectoryCreationFailException : public std::exception
		{
		public:
			const char* what() const override
			{
				return "[DirectoryCreationFailException] Directory could not be created";
			};
		};
	}
}
