#pragma once
namespace DynabyteSoftware
{
	namespace Testing
	{
		class LoggingTests
		{
		public:
			static void testWithNoLogFiles();
			static void testWithSeparateLogFiles();
			static void testWithCommonLogFile();
			static void allTests();
		private:
			static void logStuff();
		};
	}
}